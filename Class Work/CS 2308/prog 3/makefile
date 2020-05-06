a.out: ItemListMethods.o ItemListTests.o 
	g++ ItemListMethods.o ItemListTests.o

main.o: ItemListMethods.cpp ItemListClass.h
	g++ -c ItemListMethods.cpp

ItemListTests.o: ItemListTests.cpp ItemListTests.h
	g++ -c ItemListTests.cpp ItemListTests.h
