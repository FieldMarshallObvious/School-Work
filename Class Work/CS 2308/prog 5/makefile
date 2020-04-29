$CC = g++
DEPS = DynStack.h DynQue.h

.phony: all clean

all: test.out

test.out: main.o
	$(CXX) -o $@ $+

main.o: test.cpp 
	$(CXX) -c -o $@ $<

