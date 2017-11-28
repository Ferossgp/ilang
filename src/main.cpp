#include <fstream>
#include <iostream>
#include <string>
#include "AST/ast.h"
#include "codegen/codegen_visitor.h"
#include "semantical_analysis/semantic_visitor.h"
#include "lib/argparse-nortti.hpp"
#include "parsing/Lexer.h"
#include "parsing/Parser.h"

class CmdArgsParser {
public:
    std::string input;
    std::string output;

    bool printHelp;
    std::string helpText;

    bool error;

public:
    CmdArgsParser(int argc, char *argv[]) {
        ArgumentParser parser;
        parser.useExceptions(true);
        parser.appName(argv[0]);
        parser.addArgument("-h", "--help");
        parser.addArgument("-o", "--output", 1);
        parser.addFinalArgument("input");

        this->helpText = parser.usage();

        this->error = true;
        try {
            parser.parse(argc, (const char**)argv);
        }
        catch (std::exception &e) {
            return;
        }

        this->error = false;

        this->printHelp = parser.count("help");
        if (this->printHelp) {
            return;
        }

        if (!parser.count("input")) {
            this->error = true;
            return;
        }
        this->input = parser.retrieve<std::string>("input");

        if (!parser.count("output")) {
            this->error = true;
            return;
        }
        this->output = parser.retrieve<std::string>("output");
    }
};

int main(int argc, char *argv[]) {

    CmdArgsParser args(argc, argv);
    if (args.error || args.printHelp) {
        std::cout << args.helpText << std::endl;
        return 0;
    }

    std::ifstream fs(args.input);
    Lexer lexer(&fs);
    Parser parser(&lexer);
    auto program = parser.parse();


    TypeDeduceVisitor().visit(*program);

    // TypeCheckingVisitor tcv;
    // program->accept(tcv);

    std::cout << "Type checked!\n";

    CodegenVisitor v{args.output};
    v.visit(*program);
    v.generate();
    return 0;
}
