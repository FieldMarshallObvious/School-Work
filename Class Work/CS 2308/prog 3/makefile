a.out: ItemListTests.o ItemListMethods.o
	g++ test.o IntList.o	

main.o: ItemListTests.o IntList.h
	g++ -c ItemListTests.o

ItemListMethdos.o: ItemListMethods.cpp ItemListTest.h
	g++ -c ItemListMethods.cpp
