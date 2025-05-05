#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "coord.hpp"
#include "ensemble.hpp"
using namespace std;

const int FoodReprod = 8; 
const int FoodLapin = 5;
const int FoodInit = 5;
const int MaxFood = 10;
const double ProBirthRenard = 0.05;
const double ProBirthLapin = 0.30;
const int MinFreeBirthLapin = 4;
const int tempsVie = 40;



enum class  Espece {lapin, renard};

struct Animal {
	private:
		int id;
		Coord coord;
		Espece espece;
		int food;
		int tVie;
		
	public:
		Animal(int id, Espece espece, Coord c);
		Animal(int id, Espece espece, Coord c, int tVie);
		int getId() const;
		int gettVie() const;
		Coord getCoord() const;
		void setCoord(Coord c);
		Espece getEspece() const;
		void affiche(ostream& out) const;
		int getFood() const;
		bool meurt() const;
		void mange();
		void jeune();
		void vieillir();
};

ostream& operator<<(ostream &out, const Animal animal);


#endif 