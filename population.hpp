#ifndef POPULATION_HPP
#define POPULATION_HPP

#include<vector>
#include "animal.hpp"
using namespace std;


struct Population {
	private:
		vector<Animal> p;
		vector<int> libres; // pour sauvegarder les identifiants libres
	public:
		Population();
		Animal get(int id) const;
		vector<int> getIds() const;
		int reserve();
		void set(Animal a);
		void supprime(int id);
		
};



#endif 