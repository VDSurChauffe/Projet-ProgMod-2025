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
    int casesPossibles = voisinesLibres.getCard();
    if (a.getEspece() == Espece::renard) {casesPossibles += voisinsLapins(anciennePos).getCard();}
    if (casesPossibles == 0) return;
    int nouvellePosInt;
    int lapins = casesPossibles - voisinesLibres.getCard();
    if (lapins > 0) {
        nouvellePosInt = voisinsLapins(anciennePos).getT(rand() % lapins);
    }
    else {
        nouvellePosInt = voisinesLibres.getT(rand() % voisinesLibres.getCard());
    }
    Coord nouvelleCoord{nouvellePosInt};
    pop.modifier(id, nouvelleCoord);
    if (lapins > 0) {
        pop.supprime(g.getCase(nouvelleCoord));
        pop.animalMange(id);
    }
    else if (a.getEspece() == Espece::renard) {pop.animalJeune(id);}
    g.videCase(anciennePos);
    g.setCase(id, nouvelleCoord);
}

TEST_CASE("Test de deplaceAnimal avec un animal au hasard") {
    Jeu jeu(0.3, 0.3);  // Initialise une grille avec des animaux

    bool animalTrouve = false;
    int id = -1;
    Coord ancienneCoord(0, 0); // Initialisation valide

    // Cherche un animal au hasard dans la grille
    for (int x = 0; x < TAILLEGRILLE && !animalTrouve; ++x) {
        for (int y = 0; y < TAILLEGRILLE && !animalTrouve; ++y) {
            Coord c(x, y);
            int idCase = jeu.getGrille().getCase(c);
            if (idCase != -1) {
                id = idCase;
                ancienneCoord = c;
                animalTrouve = true;
            }
        }
    }

    CHECK(animalTrouve == true);
    CHECK(id != -1);

    Animal a = jeu.getPop().get(id);
    CHECK(a.getCoord() == ancienneCoord);

    jeu.deplaceAnimal(id);

    Animal aDeplace = jeu.getPop().get(id);
    Coord nouvelleCoord = aDeplace.getCoord();

    CHECK(nouvelleCoord != ancienneCoord);
    CHECK(jeu.getGrille().getCase(nouvelleCoord) == id);
    CHECK(jeu.getGrille().getCase(ancienneCoord) == -1);
    CHECK(jeu.verifieGrille());
}

bool Jeu::seReproduit(int id) const {
    Animal ani = pop.get(id);

    if (ani.getEspece() == Espece::renard) {
		if (ani.getFood() > FoodReprod) {
			double r = rand() % 100;
			r = r/100;
			if (r < ProBirthRenard) {
				return true;
			}
		}
	}

    else {
		Coord c = ani.getCoord();
		Ensemble ev = voisinsVides(c);
		if (ev.getCard() >= MinFreeBirthLapin) {
			double r = rand() % 100;
			r = r/100;
			if (r < ProBirthLapin) {
				return true;
			}
		}
	}
    return false;
}

void Jeu::simulerIteration() {
    Coord spawn{0};
    Animal ani{-1, Espece::lapin, Coord{0}};
    bool reprod;
    vector<int> ids = pop.getIds();
    for (int id: ids) {
        ani = pop.get(id);
        reprod = false;
        if (ani.getEspece() == Espece::lapin) {
            spawn = ani.getCoord();
            if (seReproduit(id)) {reprod = true;}
            deplaceAnimal(id);
            if (reprod) {ajouteAnimal(Espece::lapin, spawn);}
        }
    }
    for (int id: ids) {
        ani = pop.get(id);
        if (ani.getEspece() == Espece::renard) {
            spawn = ani.getCoord();
            deplaceAnimal(id);
            if (seReproduit(id)) {ajouteAnimal(Espece::renard, spawn);}
            
            ani = pop.get(id);
            if (ani.meurt()) {
                g.videCase(ani.getCoord());
                pop.supprime(id);
            }
        }
    }
}