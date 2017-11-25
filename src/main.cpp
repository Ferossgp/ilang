#include <fstream>
#include <iostream>
#include "AST/ast.h"
#include "codegen/codegen_visitor.h"
#include "semantical_analysis/semantic_visitor.h"
#include "lib/argparse.hpp"
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
        cxxopts::Options options(argv[0]);
        options
            .positional_help("input")
            .show_positional_help();
        options.add_options()
            ("h,help", "print help")
            ("o,output", "output file", cxxopts::value<std::string>())
            ("i,input", "input file", cxxopts::value<std::string>());
        options.parse_positional("input");

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
    Var var { std::pair<string, Type*> {"foo", new IntegerType() }, nullptr };

    Variable variable { &var };
    Assignment ass1 { &variable, new Integer(5)};
    Assignment ass2 { &variable, new Real(5.4)};

    TypeCheckingVisitor v;
    ass1.accept(v);
    ass2.accept(v);

    PrintNameVisitor p;
    ass2.accept(p);

    CmdArgsParser args(argc, argv);
    if (args.error || args.printHelp) {
        std::cout << args.helpText << std::endl;
        return 0;
    }

    std::ifstream fs(args.input);
    Lexer lexer(&fs);
    Parser parser(&lexer);
    auto program = parser.parse();
    CodegenVisitor v{args.output};
    v.visit(*program);
    v.generate();
    return 0;
}
