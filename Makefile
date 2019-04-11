all: racquet

run: racquet
	./racquet

racquet: main.cc request.o
	clang++ main.cc request.o -o racquet

request.o: request.h request.cc
	clang++ -c request.cc -o request.o
