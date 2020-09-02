all: grammer main.cpp
	g++ -g -Wall main.cpp ./src/*.c ./src/*.cc ./lib/libantlr3c.a -o ./bin/hython -I./include -I./include/antlr -L./lib
	make run
fuck: grammer main.cpp
	g++ -DINFOMSG -g -Wall main.cpp ./src/*.c ./src/*.cc ./lib/libantlr3c.a -o ./bin/hython -I./include -I./include/antlr -L./lib
	./bin/hython ./testdata/input1
debug: grammer main.cpp
	g++ -DINFOMSG -g -Wall main.cpp ./src/*.c ./src/*.cc ./lib/libantlr3c.a -o ./bin/hython -I./include -I./include/antlr -L./lib
run:
	./bin/hython ./testdata/input1
	./bin/hython ./testdata/input2
	./bin/hython ./testdata/input3
grammer: ./thirdpart/hython.g
	java -jar ./thirdpart/antlr-3.4-complete.jar ./thirdpart/hython.g
	mv ./hython.tokens ./thirdpart/
	mv ./thirdpart/*.c src/
	mv ./thirdpart/*.h include/

