#define DOCTEST_CONFIG_IMPLEMENT
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>

#include "doctest.h"
#include "coord.hpp"
#include "ensemble.hpp"
#include "grille.hpp"
#include "animal.hpp"
#include "population.hpp"
#include "jeu.hpp"
#include "image.hpp"
#include "stats.hpp"
using namespace std;

const double ProbLapinDefaut = 0.20;
const double ProbRenardDefaut = 0.07;

const int nbrTours = 200;

int main() {
	srand(time(NULL)); // time(NULL) donne nbr secodnes depuis une date (donc c'est l'heure actuelle) et srand initialise la seed de rand()

	int lapins = 0;
	int renards = 0;
    vector<int> nbLapins(nbrTours);
    vector<int> nbRenards(nbrTours);
	Jeu monde{ProbLapinDefaut, ProbRenardDefaut};
	for (int i = 0; i < nbrTours; i++) {
		monde.simulerIteration(lapins, renards);
		nbLapins[i] = lapins;
        nbRenards[i] = renards;
		cree_image(monde, i);
	}
    sauvegarderStatsCSV(nbLapins, nbRenards, nbrTours);
	return 0;
}