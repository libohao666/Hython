all:
	java -jar ../download/antlr-3.4-complete.jar ./ExprCppTree.g 
	g++ -g -Wall *.cpp *.c ../download/libantlr3c-3.4/.libs/libantlr3c.a -o test -I. -I ../download/libantlr3c-3.4/include/
	./test data
debug:
	java -jar ../download/antlr-3.4-complete.jar ./ExprCppTree.g 
	g++ -DINFOMSG -g -Wall *.cpp *.c ../download/libantlr3c-3.4/.libs/libantlr3c.a -o test -I. -I ../download/libantlr3c-3.4/include/
	./test data
run:
	./test data

