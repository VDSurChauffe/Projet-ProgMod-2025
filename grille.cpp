#include <iostream>
#include "doctest.h"
#include "coord.hpp"
#include "grille.hpp"
using namespace std;


Grille::Grille() : g{} {
	for (int i = 0; i < TAILLEGRILLE; i++) {
		for (int j = 0; j < TAILLEGRILLE; j++) {
			g[i][j] = -1;
		}
	}
}


bool Grille::caseVide(Coord c) const {
	return g[c.getX()][c.getY()] == -1;
}

int Grille::getCase(Coord c) const {
	return g[c.getX()][c.getY()];
}

void Grille::videCase(Coord c) {
	g[c.getX()][c.getY()] = -1;
}

void Grille::setCase(int id, Coord c) {
	g[c.getX()][c.getY()] = id;
}


TEST_CASE("Grille") {
	Grille g{};
	for (int i = 0; i < TAILLEGRILLE; i++) {
		for (int j = 0; j < TAILLEGRILLE; j++) {
			Coord c{i, j};
			CHECK(g.getCase(c) == -1);
		}
	}
}


TEST_CASE("caseVide getCase videCase setCase" ) {
	Grille g{};
	Coord c{12,13};
	CHECK(g.caseVide(c));
	g.setCase(1, c);
	CHECK(g.getCase(c) == 1);
	g.videCase(c);
	CHECK(g.caseVide(c));
	
}