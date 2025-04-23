#ifndef JEU_HPP
#define JEU_HPP

#include "grille.hpp"
#include "population.hpp"
#include "animal.hpp"
#include "ensemble.hpp"
using namespace std;


struct Jeu {
	private:
		Grille g;
		Population pop;
		
	public:
		Jeu();
		Jeu(double probLapins, double probRenard);
		Population getPop() const;
		Grille getGrille() const;
		void ajouteAnimal(Espece e, Coord c);
		bool verifieGrille() const;
		Ensemble voisinsVides(Coord c) const;
		Ensemble voisinsLapins(Coord c) const;
		Ensemble voisinsRenards(Coord c) const;
		void deplaceAnimal(int id);
};


#endif 