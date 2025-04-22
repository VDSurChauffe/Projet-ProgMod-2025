#ifndef POPULATION_HPP
#define POPULATION_HPP

#include<vector>

using namespace std;


struct Population {
	private:
		vector<Animal> p;
		
	public:
		Population();
		get(int id) const;
		getIds() const;
		
		
};



#endif 