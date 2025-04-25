test: coord.o test.o ensemble.o grille.o animal.o population.o jeu.o
	g++ -o test coord.o test.o ensemble.o grille.o animal.o population.o jeu.o

test.o: test.cpp doctest.h
	g++ -c test.cpp

main: main.o coord.o ensemble.o grille.o animal.o population.o jeu.o
	g++ -o main main.o coord.o ensemble.o grille.o animal.o population.o jeu.o

grille.o: grille.cpp grille.hpp coord.hpp doctest.h
	g++ -c grille.cpp



animal.o: animal.cpp animal.hpp coord.hpp doctest.h ensemble.hpp
	g++ -c animal.cpp

population.o: population.cpp population.hpp animal.hpp doctest.h
	g++ -c population.cpp

coord.o: coord.cpp coord.hpp doctest.h
	g++ -c coord.cpp

ensemble.o: ensemble.cpp ensemble.hpp doctest.h
	g++ -c ensemble.cpp

main.o: main.cpp doctest.h coord.hpp ensemble.hpp grille.hpp
	g++ -c main.cpp 


jeu.o: jeu.cpp jeu.hpp grille.hpp animal.hpp population.hpp ensemble.hpp
	g++ -c jeu.cpp

clean:
	rm -f *.o $(EXEC_FILES)
