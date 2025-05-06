// -*- coding: utf-8 -*-
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


int Population::set(Espece e, Coord c) {
	int id = reserve();
	Animal a{id, e, c};
	if (id >= int(p.size())) {
		p.push_back(a);
	} else {
        p[id] = a;
    }
	return id;
}


Animal Population::get(int id) const {
    if (id >= 0 && id < int(p.size())) {
        return p[id];
    } else {
        throw out_of_range("Identifiant invalide");
    }
}


TEST_CASE("set, reserve et get") {
    Population pop;
    pop.set(Espece::lapin, Coord(1, 2));
    Animal recupere = pop.get(0);
    CHECK(recupere.getId() == 0);
    CHECK(recupere.getEspece() == Espece::lapin);
    CHECK(recupere.getCoord().getX() == 1);
    CHECK(recupere.getCoord().getY() == 2);
}


vector<int> Population::getIds() const {
    vector<bool> estLibre(p.size(), false);
    for (int id : libres) {
        estLibre[id] = true;
    }
    vector<int> ids;
    for (int i = 0; i < int(p.size()); i++) {
        if (!estLibre[i]) {
            ids.push_back(i);
        }
    }
    return ids;
}


TEST_CASE("getIds après ajout et suppression") {
    Population pop;
    pop.set(Espece::lapin, Coord(0, 1));
    pop.set(Espece::lapin, Coord(1, 2));
    pop.set(Espece::lapin, Coord(2, 3));

    pop.supprime(1);

    vector<int> ids = pop.getIds();
    CHECK(ids.size() == 2);
    CHECK(ids[0] == 0);
    CHECK(ids[1] == 2);
}

void Population::supprime(int id) {
    if (id >= 0 && id < int(p.size())) {
        libres.push_back(id);
    }
}


TEST_CASE("reserve réutilise un id libre") {
    Population pop;
    pop.set(Espece::renard, Coord(0, 0));
    pop.set(Espece::lapin, Coord(1, 1));

    pop.supprime(0);
    int id = pop.reserve();

    CHECK(id == 0);  // doit réutiliser l'id 0
}

void Population::modifier(int id, Coord c) {
    if (id >= 0 && id < int(p.size())) {
        p[id].setCoord(c); 
    } else {
        throw out_of_range("Identifiant invalide pour modification");
    }
}

void Population::animalMange(int id) {
    p[id].mange();
}


void Population::animalJeune(int id) {
    p[id].jeune();
}

void Population::animalVieillit(int id) {
    p[id].vieillir();
}

TEST_CASE("animalMange et animalJeune") {
    Population pop;
    int id = pop.set(Espece::renard, Coord(3, 3));
    Animal a = pop.get(id);
    int foodAvant = a.getFood();
    pop.animalJeune(id);
    int foodApres = pop.get(id).getFood();
    CHECK(foodApres == foodAvant - 1);
    foodAvant = pop.get(id).getFood();
    pop.animalMange(id);
    foodApres = pop.get(id).getFood();
    CHECK(foodApres == foodAvant + FoodLapin - 1);
}

TEST_CASE("AnimalVieillit") {
    Population pop;
    int id = pop.set(Espece::renard, Coord(3, 3));
    Animal a = pop.get(id);
    int vieAvant = a.gettVie();
    int vieApres = pop.get(id).gettVie();
    bool b1 = vieApres == vieAvant - 1;
    bool b2 = vieApres == vieAvant;
    bool b3 = b1 || b2;
    CHECK(b3);

    int id2 = pop.set(Espece::lapin, Coord(10, 3));
    Animal a2 = pop.get(id2);
    int vieAvant2 = a2.gettVie();
    pop.animalVieillit(id2);
    int vieApres2 = pop.get(id2).gettVie();
    bool c1 = vieApres2 == vieAvant2 - 1;
    bool c2 = vieApres2 == vieAvant2;
    bool c3 = c1 || c2;
    CHECK(c3);
}
