#define DOCTEST_CONFIG_IMPLEMENT
#include <iostream>
#include "doctest.h"
#include "coord.hpp"

using namespace std;



int main() {
	Coord t = Coord{15,10};
	cout << t.getX() << endl;
	cout << t << endl;
	cout << "--------" << endl;
	Ensemble e = Ensemble{};
	cout << e << endl;
}