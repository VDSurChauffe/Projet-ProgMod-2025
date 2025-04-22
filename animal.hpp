#ifndef ANIMAL_HPP
#define ANIMAL_HPP


using namespace std;

const int FoodReprod; 
const int FoodLapin;
const int foodInit;
const int MaxFood;
const int ProBirthRenard;
const int ProBirthLapin;
const int MinFreeBirthLapin;




enum class  Espece {lapin, renard};

struct Animal {
	private:
		int id;
		Coord coord;
		Espece espece;
		int food;
		
	public:
		Animal();
		Animal(int id, Espece espece, Coord c);
		int getId() const;
		Coord getCoord() const;
		void setCoord(Coord c);
		Espece getEspece() const;
		void affiche(ostream& out) const;
		bool meurt() const;
		bool seReproduit() const;
		void mange();
		void jeune();
};

ostream& operator<<(ostream &out, const Animal animal);


#endif 