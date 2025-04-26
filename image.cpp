#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

#include "doctest.h"
#include "grille.hpp"
#include "population.hpp"
#include "animal.hpp"
#include "jeu.hpp"
#include "image.hpp"
using namespace std;

void cree_image(Jeu j, int numero) {
    ostringstream filename;
    filename << "animation/img" << setfill('0') << setw(3) << numero << ".ppm";
    ofstream img(filename.str());
    img << "P3" << endl
        << TAILLEGRILLE << " " << TAILLEGRILLE << " " << endl
        << 255 << " ";
    
    int index;
    for (int xy = 0; xy < TAILLEGRILLE * TAILLEGRILLE; xy++) {
        if (xy % 7 == 0) {img << endl;}
        index = j.getGrille().getCase(Coord{xy});
        if (index == -1) {img << "0 0 0  ";}
        else {
            Animal ani = j.getPop().get(index);
            if (ani.getEspece() == Espece::lapin) {img << "0 0 255  ";}
            else {img << "255 0 0  ";}
        }
    }
    img.close();
}