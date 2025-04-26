#define DOCTEST_CONFIG_IMPLEMENT
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

#include "doctest.h"
#include "coord.hpp"
#include "ensemble.hpp"
#include "grille.hpp"
#include "animal.hpp"
#include "population.hpp"
#include "jeu.hpp"
#include "image.hpp"
using namespace std;

const double ProbLapinDefaut = 0.20;
const double ProbRenardDefaut = 0.07;

int main() {
	Jeu monde{ProbLapinDefaut, ProbRenardDefaut};
	for (int i = 0; i < 100; i++) {
		// TODO: simulation
		cree_image(monde, i);
	}
	return 0;
}