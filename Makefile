test: coord.o test.o ensemble.o
	g++ -o test coord.o test.o ensemble.o

test.o: test.cpp doctest.h
	g++ -c test.cpp

main: main.o coord.o
	g++ -o main main.o coord.o

coord.o: coord.cpp coord.hpp doctest.h
	g++ -c coord.cpp

ensemble.o: ensemble.cpp ensemble.hpp doctest.h
	g++ -c ensemble.cpp

main.o: main.cpp doctest.h coord.hpp ensemble.cpp
	g++ -c main.cpp 

clean:
	rm -f *.o $(EXEC_FILES)
