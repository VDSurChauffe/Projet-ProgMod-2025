#include <iostream>
#include "animal.hpp"
#include "population.hpp"
#include "doctest.h"
using namespace std;


Population::Population() : p(), libres() {}


TEST_CASE("Constructeur vide") {
    Population pop;
    CHECK(pop.getIds().empty());
}

int Population::reserve() {
    if (!libres.empty()) {
        int id = libres.back();
        libres.pop_back();
		return id;
    } else {
        int id = p.size();
		return id;
    }
}


void Population::set(Animal a) {
	int id = reserve();
	if (id >= p.size()) {
		p.push_back(a);
	}
    p[id] = a;
}


Animal Population::get(int id) const {
    if (id >= 0 && id < p.size()) {
        return p[id];
    } else {
        throw out_of_range("Identifiant invalide");
    }
}

TEST_CASE("Population::set, reserve et get") {
    Population pop;
    int id = pop.reserve();
    Animal a(id, Espece::lapin, Coord(1, 2));
    pop.set(a);
    Animal recupere = pop.get(id);
    CHECK(recupere.getId() == id);
    CHECK(recupere.getEspece() == Espece::lapin);
    CHECK(recupere.getCoord().getX() == 1);
    CHECK(recupere.getCoord().getY() == 2);
}

TEST_CASE("Population::getIds après ajout et suppression") {
    Population pop;
    for (int i = 0; i < 3; ++i) {
        Animal a(i, Espece::lapin, Coord(i, i + 1));
        pop.set(a);
    }
    pop.supprime(1);

    vector<int> ids = pop.getIds();
    CHECK(ids.size() == 2);
    CHECK(ids[0] == 0);
    CHECK(ids[1] == 2);
}

vector<int> Population::getIds() const {
    vector<bool> estLibre(p.size(), false);
    for (int id : libres) {
        estLibre[id] = true;
    }

    vector<int> ids;
    for (int i = 0; i < static_cast<int>(p.size()); ++i) {
        if (!estLibre[i]) {
            ids.push_back(i);
        }
    }

    return ids;
}

TEST_CASE("Population::getIds sur une population vide") {
    Population pop;
    vector<int> ids = pop.getIds();
    CHECK(ids.empty());
}

void Population::supprime(int id) {
    libres.push_back(id);
}

TEST_CASE("Population::reserve réutilise un id libre") {
    Population pop;

    Animal a1(0, Espece::renard, Coord(0, 0));
    Animal a2(1, Espece::lapin, Coord(1, 1));
    pop.set(a1);
    pop.set(a2);

    pop.supprime(0);
    int id = pop.reserve();

    CHECK(id == 0);  // Doit réutiliser l'id supprimé
}




