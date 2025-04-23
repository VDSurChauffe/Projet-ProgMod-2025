#include <iostream>
#include "doctest.h"
#include "grille.hpp"
#include "population.hpp"
#include "animal.hpp"
#include "jeu.hpp"
using namespace std;

Jeu::Jeu() : g{}, pop{} {}

Population Jeu::getPop() const {
	return pop;
}

Grille Jeu::getGrille() const {
	return g;
}

TEST_CASE("Test de getPop()") {
    Jeu jeu(0.3, 0.3);
    Population pop = jeu.getPop();
    CHECK(pop.getIds().size() > 0);
}

void Jeu::ajouteAnimal(Espece e, Coord c) {
	int id = pop.set(e, c);
	g.setCase(id, c);
}

TEST_CASE("Test de ajouteAnimal()") {
    Coord c{5, 5};
	Jeu jeu;
    jeu.ajouteAnimal(Espece::lapin, c);
    Population pop = jeu.getPop();
    CHECK(pop.getIds().size() > 0);
    Grille g = jeu.getGrille();
	int id = g.getCase(c);
	Animal a = pop.get(id);
	CHECK(a.getEspece() == Espece::lapin);
	CHECK(a.getCoord() == c);
}

Jeu::Jeu(double probLapins, double probRenard) : g{}, pop{} {
	for (int i = 0; i < TAILLEGRILLE; i++) {
		for (int j = 0; j < TAILLEGRILLE; j++) {
			Coord c{i, j};
			double r = rand() % 100;
			r = r/100;
			if (r < probLapins) {
				ajouteAnimal(Espece::lapin, c);
			} else if (r < probLapins + probRenard) {
				ajouteAnimal(Espece::renard, c);
			} else {
				g.videCase(c);
			}
		}
	}
}

bool Jeu::verifieGrille() const {
	for (int i = 0; i < TAILLEGRILLE; i++) {
		for (int j = 0; j < TAILLEGRILLE; j++) {
			int id = g.getCase(Coord{i, j});
			if (id != -1) {
				Animal a = pop.get(id);
				if (a.getId() != id) { return false; }
				if (a.getCoord() != Coord{i, j}) {return false; }
			}
		}
	}
	return true;
}


TEST_CASE("Test de verifieGrille()") {
    Jeu jeu(0.3, 0.2);
    CHECK(jeu.verifieGrille());
}

Ensemble Jeu::voisinsVides(Coord c) const {
    Ensemble res;
    Ensemble ev = c.voisines();

    for (int i = 0; i < ev.getCard(); i++) {
        Coord voisine(ev.getT(i));
        int id = g.getCase(voisine);
        if (id == -1) {
            res.ajoute(voisine.toInt());
        }
    }
    return res;
}

TEST_CASE("Test de voisinsVides") {
    Jeu jeu;
    Coord c{5, 5};
    jeu.ajouteAnimal(Espece::lapin, c);
    jeu.ajouteAnimal(Espece::lapin, Coord{4, 5});
    jeu.ajouteAnimal(Espece::renard, Coord{6, 5});
    Ensemble voisinesVides = jeu.voisinsVides(c);
    for (int i = 0; i < voisinesVides.getCard(); i++) {
        Coord v(voisinesVides.getT(i));
        CHECK(jeu.getGrille().getCase(v) == -1);
    }
    CHECK(voisinesVides.contient(Coord{4, 5}.toInt()) == false);
    CHECK(voisinesVides.contient(Coord{6, 5}.toInt()) == false);
}

Ensemble Jeu::voisinsLapins(Coord c) const {
	Ensemble res;
	Ensemble ev = c.voisines();
	for (int i = 0; i < ev.getCard(); i++) {
		Coord v(ev.getT(i));
		int id = g.getCase(v);
		if (id != -1) {
			Animal a = pop.get(id);
			if (a.getEspece() == Espece::lapin) {
				res.ajoute(v.toInt());
			}
		}
	}
	return res;
}

Ensemble Jeu::voisinsRenards(Coord c) const {
	Ensemble res;
	Ensemble ev = c.voisines();
	for (int i = 0; i < ev.getCard(); i++) {
		Coord v(ev.getT(i));
		int id = g.getCase(v);
		if (id != -1) {
			Animal a = pop.get(id);
			if (a.getEspece() == Espece::renard) {
				res.ajoute(v.toInt());
			}
		}
	}
	return res;
}

TEST_CASE("Test de voisinsLapins et voisinsRenards") {
    Jeu jeu;
    jeu.ajouteAnimal(Espece::lapin, Coord{5, 4});
    jeu.ajouteAnimal(Espece::lapin, Coord{4, 5});
    jeu.ajouteAnimal(Espece::renard, Coord{6, 5});
    Coord centre{5, 5};
    Ensemble voisinsLapins = jeu.voisinsLapins(centre);
    Ensemble voisinsRenards = jeu.voisinsRenards(centre);
    CHECK(voisinsLapins.contient(Coord{5, 4}.toInt()));
    CHECK(voisinsLapins.contient(Coord{4, 5}.toInt()));
    CHECK(voisinsLapins.getCard() == 2);
    CHECK(voisinsRenards.contient(Coord{6, 5}.toInt()));
    CHECK(voisinsRenards.getCard() == 1);
}

void Jeu::deplaceAnimal(int id) {
    Animal a = pop.get(id);
    Coord anciennePos = a.getCoord();
	
    Ensemble voisinesLibres = voisinsVides(anciennePos);
    if (voisinesLibres.getCard() == 0) return; // Pas de mouvement possible
    int nouvellePosInt = voisinesLibres.getT(rand() % voisinesLibres.getCard());
    Coord nouvelleCoord{nouvellePosInt};
    Animal& refAnimal = pop.getRef(id);
    refAnimal.setCoord(nouvelleCoord);

    g.videCase(anciennePos);
    g.setCase(id, nouvelleCoord);
}

TEST_CASE("Test deplaceAnimal déplace bien l'animal dans une case voisine libre") {
    Jeu jeu;

    Coord c{10, 10};
    jeu.ajouteAnimal(Espece::lapin, c);
    int id = jeu.getGrille().getCase(c);
    CHECK(id != -1);
    Coord caseLibre = Coord{10, 11};
    jeu.getGrille().videCase(caseLibre);
    Animal aAvant = jeu.getPop().get(id);
    Coord ancienneCoord = aAvant.getCoord();
    jeu.deplaceAnimal(id);
    Animal aApres = jeu.getPop().get(id);
    Coord nouvelleCoord = aApres.getCoord();
    CHECK(nouvelleCoord != ancienneCoord);
    CHECK(jeu.getGrille().getCase(ancienneCoord) == -1);
    CHECK(jeu.getGrille().getCase(nouvelleCoord) == id);
    Ensemble voisines = ancienneCoord.voisines();
    CHECK(voisines.contient(nouvelleCoord.toInt()));
}











