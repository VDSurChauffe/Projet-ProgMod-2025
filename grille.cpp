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

TEST_CASE("Grille") {
	Grille g{};
	for (int i = 0; i < TAILLEGRILLE; i++) {
		for (int j = 0; j < TAILLEGRILLE; j++) {
			Coord c{i, j};
			CHECK(g.getCase(c) == -1);
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

TEST_CASE("videCase remet une case à vide") {
    Grille g;
    Coord c(10, 10);
    g.setCase(99, c);
    CHECK_FALSE(g.caseVide(c));
    g.videCase(c);
    CHECK(g.caseVide(c));
    CHECK(g.getCase(c) == -1);
}

void Grille::setCase(int id, Coord c) {
	g[c.getX()][c.getY()] = id;
}

TEST_CASE("setCase") {
    Grille g;
    Coord c(5, 5);
    g.setCase(42, c);
    CHECK_FALSE(g.caseVide(c));
    CHECK(g.getCase(c) == 42);
}


TEST_CASE("Si case déjà occupée") {
    Grille g;
    Coord c(7, 2);
    g.setCase(5, c);
    CHECK(g.getCase(c) == 5);
    g.setCase(8, c);
    CHECK(g.getCase(c) == 8);
}

TEST_CASE("Autres tests : caseVide getCase videCase setCase" ) {
	Grille g{};
	Coord c{12,13};
	CHECK(g.caseVide(c));
	g.setCase(1, c);
	CHECK(g.getCase(c) == 1);
	g.videCase(c);
	CHECK(g.caseVide(c));
	
}