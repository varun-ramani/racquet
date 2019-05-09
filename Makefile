CC := clang++
DEPS := build/tester.o build/server.o build/request.o build/response.o

# Compiler steps
tester: build ${DEPS}
	${CC} ${DEPS} -o tester

build/tester.o: src/tester.cc
	${CC} -c src/tester.cc -o build/tester.o

build/response.o: src/response.cc src/response.h
	${CC} -c src/response.cc -o build/response.o

build/request.o: src/request.h src/request.cc
	clang++ -c src/request.cc -o build/request.o

build/server.o: src/server.h src/server.cc
	clang++ -c src/server.cc -o build/server.o

# Actions
build:
	mkdir -p build

run: tester
	./tester

clean:
	rm -rf build
	rm -rf tester
