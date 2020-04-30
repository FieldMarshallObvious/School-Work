$CC = g++
DEPS = DynStack.h DynQue.h

.phony: all clean

all: test.out

test.out: main.o
	$(CXX) -o $@ $+

main.o: file_filter.cpp 
	$(CXX) -c -o $@ $<

