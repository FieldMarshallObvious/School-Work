a.out: test.o DynStack.o
	g++ test.o DynStack.o

main.o: test.o DynStack.h
	g++ -c test.cpp

DynStack.o: DynStack.cpp DynStack.h
	g++ -c DynStack.cpp

