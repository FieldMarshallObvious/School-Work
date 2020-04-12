a.out: test.o IntList.o
	g++ test.o IntList.o

main.o: test.o IntList.h
	g++ -c test.cpp

IntList.o: IntList.cpp InstList.h
	g++ -c IntList.cpp

