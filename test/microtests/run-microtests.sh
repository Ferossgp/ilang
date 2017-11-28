cd ../../build
cmake ../src
make
./voc -o ../test/microtests/test_out.o ../test/microtests/microtests.vo
cd ../test/microtests
clang -o main.out main.c
./main.out