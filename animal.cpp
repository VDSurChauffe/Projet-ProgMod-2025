#include <iostream>
#include "doctest.h"
#include "coord.hpp"
#include "ensemble.hpp"
#include "animal.hpp"
using namespace std;



Anmial::Anmial() : 

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

void Animal::setCoord(Coord c) {
	coord = c;
}

Espece Animal::getEspece() const {
	return espece;
}

bool Animal::meurt() const {
	return food == 0;
}

void Animal::mange() {
	food += FoodLapin - 1;
	if (food > MaxFood) {
		food = MaxFood;
	}
}

void Animal::jeune() {
	food--;
}

void Animal::affiche(ostream& out) const {
	out << "Animal : " << id << endl;
	out << "Coord : " << coord << endl;
	out << "Espèce : " << espece << endl;
	out << "Nourriture : " << nourriture << endl;
}

ostream& operator<<(ostream &out, const Animal a) {
	a.affiche(out);
	return out;
}


bool Animal::seReproduit() const {
	if (espece == Espece::renard) {
		if (food > foodRepro) {
			double r = rand() % 100;
			r = r/100;
			if (r < ProbBirthRenard) {
				return true;
			}
		}
	}
	if (espece == Espece::lapin) {
		// to do
}