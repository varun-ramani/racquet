CC := clang++
DEPS := build/racquet.o build/server.o build/request.o

# Compiler steps
racquet: build ${DEPS}
	${CC} ${DEPS} -o racquet

build/racquet.o: src/racquet.cc
	${CC} -c src/racquet.cc -o build/racquet.o

build/request.o: src/request.h src/request.cc
	clang++ -c src/request.cc -o build/request.o

build/server.o: src/server.h src/server.cc
	clang++ -c src/server.cc -o build/server.o

# Actions
build:
	mkdir -p build

run: racquet
	./racquet

clean:
	rm -rf build
	rm -rf racquet
