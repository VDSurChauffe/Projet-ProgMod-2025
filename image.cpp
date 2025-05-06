// -*- coding: utf-8 -*-
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
    // setup de l'image ppm (taille, couleur, format, nom)
    ostringstream filename;
    filename << "animation/img" << setfill('0') << setw(3) << numero << ".ppm";
    ofstream img(filename.str());
    img << "P3" << endl
        << TAILLEGRILLE << " " << TAILLEGRILLE << " " << endl
        << 255 << " ";
    
    int index;
    int sante;
    int sante_food;
    for (int xy = 0; xy < TAILLEGRILLE * TAILLEGRILLE; xy++) {
        if (xy % 7 == 0) {img << endl;} // pour ne pas dépasser 70 caractères par ligne
        index = j.getGrille().getCase(Coord{xy});
        if (index == -1) {img << "0 63 0  ";} // vert pour case vide
        else {
            Animal ani = j.getPop().get(index);
            if (ani.getEspece() == Espece::lapin) { // bleu pour lapin
                sante = (192. * ani.gettVie()) / (tempsVie/2);
                img << "0 0 " << 63 + sante << "  ";
            }
            else { // rouge pour renard
                sante = (192. * ani.gettVie()) / (tempsVie/2);
                sante_food = (192. * ani.getFood()) / MaxFood;
                if (sante > sante_food) {sante = sante_food;}
                img << 63 + sante << " 0 0  ";
            }
        }
    }
    img.close();
}
