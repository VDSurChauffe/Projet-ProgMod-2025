EXEC_FILES=test main
COMPIL=g++ -c -Wall

main: main.o coord.o ensemble.o grille.o animal.o population.o jeu.o image.o stats.o
	g++ -o main main.o coord.o ensemble.o grille.o animal.o population.o jeu.o image.o stats.o

test: coord.o test.o ensemble.o grille.o animal.o population.o jeu.o
	g++ -o test coord.o test.o ensemble.o grille.o animal.o population.o jeu.o

test.o: test.cpp doctest.h
	$(COMPIL) test.cpp

image.o: image.cpp image.hpp jeu.hpp grille.hpp animal.hpp population.hpp ensemble.hpp
	$(COMPIL) image.cpp

grille.o: grille.cpp grille.hpp coord.hpp doctest.h
	$(COMPIL) grille.cpp

animal.o: animal.cpp animal.hpp coord.hpp doctest.h ensemble.hpp
	$(COMPIL) animal.cpp

population.o: population.cpp population.hpp animal.hpp doctest.h
	$(COMPIL) population.cpp

coord.o: coord.cpp coord.hpp doctest.h
	$(COMPIL) coord.cpp

ensemble.o: ensemble.cpp ensemble.hpp doctest.h
	$(COMPIL) ensemble.cpp

main.o: main.cpp doctest.h coord.hpp ensemble.hpp grille.hpp
	$(COMPIL) main.cpp 

jeu.o: jeu.cpp jeu.hpp grille.hpp animal.hpp population.hpp ensemble.hpp
	$(COMPIL) jeu.cpp

stats.o: stats.hpp stats.cpp
	$(COMPIL) stats.cpp

anim: 
	convert -scale 600 -delay 20 animation/img*.ppm movie.gif

anim2:
	magick convert -scale 600 -delay 20 animation/img*.ppm movie.gif

graph:
	python3 graphique.py

init:
	mkdir animation statistiques

clean_w:
	del /f *.o $(EXEC_FILES)
	
clean_exec:
	rm -f *.o $(EXEC_FILES)

clean_anim:
	rm -f animation/*.ppm movie.gif

clean_stats:
	rm -f statistiques/*

clean_all:
	make clean_exec; make clean_anim; make clean_stats