#ifndef POPULATION_HPP
#define POPULATION_HPP

#include<vector>
#include "animal.hpp"
#include "coord.hpp"
using namespace std;


struct Population {
	private:
		vector<Animal> p;
		vector<int> libres; // pour sauvegarder les identifiants libres
	public:
		Population();
		Animal get(int id) const;
		vector<int> getIds() const;
		void animalMange(int id);
		void animalJeune(int id);
		int reserve();
		int set(Espece espece, Coord c);
		void supprime(int id);
		void modifier(int id, Coord c);
		
};



#endif 