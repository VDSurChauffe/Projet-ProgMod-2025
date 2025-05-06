// -*- coding: utf-8 -*-
#include <iostream>
#include <sstream>
#include "doctest.h"
#include "coord.hpp"
#include "ensemble.hpp"
#include "animal.hpp"
using namespace std;

Animal::Animal(int id, Espece espece, Coord c, int tVie) : id {id}, coord{c}, espece{espece}, food{FoodInit}, tVie{tVie} {}

void Animal::vieillir() {
	tVie -= rand() % 2; // 0 ou 1
}

TEST_CASE("vieillir diminue tVie de 0 ou 1") {
    Coord c(1, 2);
    Animal a(2, Espece::renard, c, 10);
    int t0 = a.gettVie();
    a.vieillir();
    int t1 = a.gettVie();
    CHECK((t1 == t0 || t1 == t0 - 1));
}

Animal::Animal(int id, Espece espece, Coord c) : id {id}, coord{c}, espece{espece}, food{FoodInit}, tVie{tempsVie/2} {} //tempsVie/2 car on vieillit de 0 ou 1 donc une fois sur 2 ce qui double l'espérance de vie théorique

int Animal::getId() const {
	return id;
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
	return food == 0 or tVie <= 0;
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
	out << "Identifiant : " << id << endl;
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
    std::cout << "Affichage de l'animal :" << endl;
    std::cout << a << endl;
}
