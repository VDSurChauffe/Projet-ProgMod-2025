#include <iostream>
#include <sstream>
#include "doctest.h"
#include "coord.hpp"
#include "ensemble.hpp"
#include "animal.hpp"
using namespace std;

Animal::Animal(int id, Espece espece, Coord c, int tVie) : id {id}, coord{c}, espece{espece}, food{FoodInit}, tVie{tVie} {}

void Animal::vieillir(int n) {
	tVie -= n;
}

Animal::Animal(int id, Espece espece, Coord c) : id {id}, coord{c}, espece{espece}, food{FoodInit}, tVie{tempsVie} {}

int Animal::getId() const {
	return id;
}

TEST_CASE("getId") {
	cout<< Coord{20,20} << endl;
	cout<< Coord{12,5} << endl;
	cout<< Coord{34,0} << endl;
	cout<< Coord{0,39} << endl;
}

Coord Animal::getCoord() const {
	return coord;
}

Espece Animal::getEspece() const {
	return espece;
}

int Animal::getFood() const {
	return food;
}

TEST_CASE("Animal constructeur and getters") {
    Coord c(5, 10);
    Animal a(42, Espece::lapin, c);

    CHECK(a.getId() == 42);
    CHECK(a.getEspece() == Espece::lapin);
    CHECK(a.getCoord().getX() == 5);
    CHECK(a.getCoord().getY() == 10);
}

void Animal::setCoord(Coord c) {
	coord = c;
}

TEST_CASE("Animal setCoord") {
    Animal a(1, Espece::renard, Coord(0, 0));
    a.setCoord(Coord(3, 4));
    CHECK(a.getCoord() == Coord(3, 4));
}

bool Animal::meurt() const {
	return food == 0 || tVie <= 0;
}

TEST_CASE("Animal meurt") {
    Animal a(2, Espece::lapin, Coord(0, 0));
    for (int i = 0; i < FoodInit; ++i) a.jeune();
    CHECK(a.meurt() == true);
}

void Animal::mange() {
	food += FoodLapin - 1;
	if (food > MaxFood) {
		food = MaxFood;
	}
}

TEST_CASE("Animal mange") {
    Animal a(3, Espece::lapin, Coord(0, 0));
    a.mange(); 
    CHECK_FALSE(a.meurt());
}

void Animal::jeune() {
	food--;
}

TEST_CASE("Animal jeune diminue food") {
    Animal a(4, Espece::lapin, Coord(0, 0));
    a.jeune();
    CHECK(a.meurt() == false);
}

void Animal::affiche(ostream& out) const {
	out << "Animal : " << id << endl;
	out << "Coord : " << coord << endl;
	out << "Espèce : ";
	switch (getEspece()) {
		case Espece::lapin : out << "lapin" << endl; break;
		case Espece::renard : out << "renard" << endl; break;
	}
	out << "Nourriture : " << food << endl;
	out << "Temps de vie : " << tVie << endl;
}

ostream& operator<<(ostream &out, const Animal a) {
	a.affiche(out);
	return out;
}

int Animal::gettVie() const {
	return tVie;
}


/* test compliqué sous windows à cause de endl qui génère \r\n en trop
TEST_CASE("Affichage d'un animal avec operator<<") {
    Animal a(5, Espece::renard, Coord(1, 1));
    stringstream ss;
    ss << a;
    string sortie = ss.str();
	stringstream verif;
    verif << "Animal : 5" << endl
          << "Coord : (1,1)" << endl
          << "Espèce : renard" << endl
          << "Nourriture : " << a.getFood() << endl
          << "Temps de vie : " << a.gettVie();
	string test = verif.str();
    CHECK(sortie == test);
}
*/

TEST_CASE("Affichage d'un animal") {
    Animal a(5, Espece::renard, Coord(1, 1));
    std::cout << "Affichage de l'animal :" << std::endl;
    std::cout << a << std::endl;
}
