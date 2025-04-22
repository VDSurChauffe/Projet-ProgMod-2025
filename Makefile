test: coord.o test.o ensemble.o grille.o
	g++ -o test coord.o test.o ensemble.o grille.o

test.o: test.cpp doctest.h
	g++ -c test.cpp

main: main.o coord.o
	g++ -o main main.o coord.o

grille.o: grille.cpp grille.hpp coord.hpp doctest.h
	g++ -c grille.cpp

coord.o: coord.cpp coord.hpp doctest.h
	g++ -c coord.cpp

ensemble.o: ensemble.cpp ensemble.hpp doctest.h
	g++ -c ensemble.cpp

main.o: main.cpp doctest.h coord.hpp ensemble.hpp grille.hpp
	g++ -c main.cpp 

clean:
	rm -f *.o $(EXEC_FILES)
