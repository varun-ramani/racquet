CC := clang++

all: racquet

run: racquet
	./racquet

racquet: build/racquet.o build/request.o
	${CC} build/racquet.o build/request.o -o racquet

build/racquet.o: src/racquet.cc
	${CC} -c src/racquet.cc -o build/racquet.o

build/request.o: src/request.h src/request.cc
	clang++ -c src/request.cc -o build/request.o
