#include <iostream>
#include "doctest.h"
#include "coord.hpp"
#include "ensemble.hpp"
using namespace std;


Coord::Coord(int x, int y) : x{x}, y{y} {
	if (x < 0 || x >= TAILLEGRILLE) {
		throw invalid_argument("x hors des bornes");
	}

	if (y < 0 || y >= TAILLEGRILLE) {
		throw invalid_argument("y hors des bornes");
	}
}

TEST_CASE("constructeur Coord") {
	Coord t = Coord{15, 10};
	CHECK(t.getX() == 15);
	CHECK(t.getY() == 10);
	CHECK_THROWS_AS(Coord(-12, 0), invalid_argument);
	CHECK_THROWS_AS(Coord(0, -12), invalid_argument);
}


int Coord::getX() const{
	return x;
}

int Coord::getY() const {
	return y;
}

ostream& operator<<(ostream &out, const Coord c) {
	out << "(" << c.getX() << "," << c.getY() << ")";
	return out;
}

TEST_CASE("affichage coord") {
	cout<< Coord{20,20} << endl;
	cout<< Coord{12,5} << endl;
	cout<< Coord{34,0} << endl;
	cout<< Coord{0,39} << endl;
}

bool operator==(Coord c1, Coord c2) {
	return (c1.getX() == c2.getX()) && (c1.getY() == c2.getY());
}

bool operator!=(Coord c1, Coord c2) {
	return not(c1 == c2);
}

TEST_CASE("égalité") {
	CHECK(Coord(0,0) == Coord(0,0));
	CHECK(Coord(1,2) == Coord(1,2));
	CHECK_FALSE(Coord(2,5) == Coord(5,2));
	CHECK_FALSE(Coord(39,1) == Coord(12,12));
	CHECK(Coord(0,0) != Coord(0,30));
	CHECK_FALSE(Coord(2,16) != Coord(2,16));
}

Coord::Coord(int n) : x{n/TAILLEGRILLE}, y{n%TAILLEGRILLE} {
	if (n < 0) {
		throw invalid_argument(" entier négatif");
	}
	if (n >= TAILLEGRILLE*TAILLEGRILLE) {
		throw invalid_argument(" entier trop grand");
	}
}

TEST_CASE("constructeur avec un entier") {
	Coord t = Coord{50};
	CHECK(t == Coord(1,10));
	CHECK_THROWS_AS(Coord(-1), invalid_argument);
	CHECK_THROWS_AS(Coord(1601), invalid_argument);
}

int Coord::toInt() const{
	return x*TAILLEGRILLE + y;
}

TEST_CASE("toInt") {
	Coord t1 = Coord{0,0};
	Coord t2 = Coord{39,39};
	Coord t3 = Coord{78};
	CHECK(t1.toInt() == 0);
	CHECK(t2.toInt() == 1599);
	CHECK(t3.toInt() == 78);
}

Ensemble Coord::voisines() const {
	int x = getX();
	int y = getY();
	
	int imin = max(x - 1, 0);
	int imax = min(x + 1, TAILLEGRILLE - 1);
	int jmin = max(y - 1, 0);
	int jmax = min(y + 1, TAILLEGRILLE - 1);
	
	Ensemble ev = Ensemble{};
	for (int i = imin; i <= imax; i++) {
		for (int j = jmin; j <= jmax; j++) {
			Coord temp = Coord{i,j};
			if (temp != Coord{x, y}) {
				ev.ajoute(temp.toInt());
			}
		}
	}
	return ev;
}

TEST_CASE("voisines case au centre") {
    Coord c{2, 2};
    Ensemble v = c.voisines();
    CHECK(v.cardinal() == 8);
    CHECK(v.contient(Coord(1,1).toInt()));
    CHECK(v.contient(Coord(1,2).toInt()));
    CHECK(v.contient(Coord(1,3).toInt()));
    CHECK(v.contient(Coord(2,1).toInt()));
    CHECK(v.contient(Coord(2,3).toInt()));
    CHECK(v.contient(Coord(3,1).toInt()));
    CHECK(v.contient(Coord(3,2).toInt()));
    CHECK(v.contient(Coord(3,3).toInt()));
}

TEST_CASE("voisines en haut à gauche") {
    Coord c{0, 0};
    Ensemble v = c.voisines();
    CHECK(v.cardinal() == 3);
    CHECK(v.contient(Coord(0,1).toInt()));
    CHECK(v.contient(Coord(1,0).toInt()));
    CHECK(v.contient(Coord(1,1).toInt()));
}

TEST_CASE("voisines en bas à droite") {
    Coord c{TAILLEGRILLE - 1, TAILLEGRILLE - 1};
    Ensemble v = c.voisines();
    CHECK(v.cardinal() == 3);
    CHECK(v.contient(Coord(TAILLEGRILLE - 2, TAILLEGRILLE - 2).toInt()));
    CHECK(v.contient(Coord(TAILLEGRILLE - 2, TAILLEGRILLE - 1).toInt()));
    CHECK(v.contient(Coord(TAILLEGRILLE - 1, TAILLEGRILLE - 2).toInt()));
}




