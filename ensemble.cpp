#include <iostream>
#include "doctest.h"
#include "ensemble.hpp"
using namespace std;

void Ensemble::affiche(ostream& out) const {
	out << "{ ";
	for (int i = 0; i < card; i++) {
		out << t[i] << " ";
	}
	out << " }" << endl;
}

ostream& operator<<(ostream &out, const Ensemble e) {
	e.affiche(out);
	return out;
}

bool Ensemble::estVide() const {
	return not(card);
}

TEST_CASE("estVide") {
	Ensemble e;
	CHECK(e.cardinal() == 0);
}

int Ensemble::cardinal() const {
	return card;
}

void Ensemble::ajoute(int o) {
	if (card >= MAXCARD) {
		throw runtime_error("Ensemble complet");
	}
	t[card] = o;
	card++;
}

TEST_CASE("ajoute") {
	Ensemble e = Ensemble{};
	e.ajoute(3);
	CHECK(e.getCard() == 1);
	CHECK(e.getT(0) == 3);
	for (int i = 1; i < MAXCARD; i++) {
		e.ajoute(rand());
	}
	CHECK_THROWS_AS(e.ajoute(rand()), runtime_error);
}

int Ensemble::tire() {
	if (card <= 0) {
		throw runtime_error("Ensemble vide");	
	}
	int r = rand() % card;
	int o = t[r];
	t[r] = t[card-1];
	card--;
	return o;
}

TEST_CASE("tire") {
	Ensemble e = Ensemble{};
	CHECK_THROWS_AS(e.tire(), runtime_error);
	e.ajoute(5);
	CHECK(e.tire() == 5);
	CHECK(e.getCard() == 0);
}

int Ensemble::getT(int i) const {
	return t[i];
}

TEST_CASE("getT") {
    Ensemble e;
    e.ajoute(7);
    e.ajoute(14);
    e.ajoute(21);
    CHECK(e.getT(0) == 7);
    CHECK(e.getT(1) == 14);
    CHECK(e.getT(2) == 21);
}

int Ensemble::getCard() const {
	return card;
}


bool Ensemble::contient(int o) const {
	for (int i = 0; i < card; ++i) {
		if (t[i] == o) {
			return true;
		}
	}
	return false;
}

TEST_CASE("contient") {
    Ensemble v;
    v.ajoute(99);
    v.ajoute(42);
    CHECK(v.contient(99));
    CHECK(v.contient(42));
    Ensemble e;
    e.ajoute(5);
    e.ajoute(10);
    CHECK_FALSE(e.contient(999));
    CHECK_FALSE(e.contient(0));
}



