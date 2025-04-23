#ifndef COORD_HPP
#define COORD_HPP

#include "ensemble.hpp"
using namespace std;

const int TAILLEGRILLE = 40; 

struct Coord {
	private:
		int x;
		int y;
	public:
		Coord(int x, int y);
		Coord(int n);
		int getX() const;
		int getY() const;
		int toInt() const;
		Ensemble voisines() const;
};

bool operator==(Coord c1, Coord c2);
bool operator!=(Coord c1, Coord c2);
ostream& operator<<(ostream &out, Coord c);

#endif 