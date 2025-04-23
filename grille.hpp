#ifndef GRILLE_HPP
#define GRILLE_HPP
#include<array>

#include "coord.hpp"
using namespace std;

struct Grille {
	private:
		array<array<int, TAILLEGRILLE>, TAILLEGRILLE> g;
		
	public:
		Grille();
		bool caseVide(Coord c) const;
		int getCase(Coord c) const;
		void videCase(Coord c);
		void setCase(int id, Coord c);
};



#endif 