all: racquet

run: racquet
	./racquet

racquet: main.cc
	clang++ main.cc -o racquet
