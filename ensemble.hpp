#ifndef ENSEMBLE_HPP
#define ENSEMBLE_HPP


#include<array>
using namespace std;


const int MAXCARD = 1000;

struct Ensemble {
	private:
		array<int, MAXCARD> t;
		int card;
	public:
		Ensemble() : card{0} {}
		int getT(int i) const;
		int getCard() const;
		void affiche(ostream& out) const;
		bool estVide() const;
		int cardinal() const;
		void ajoute(int o);
		int tire();
		bool contient(int o) const;
};

ostream& operator<<(ostream &out, const Ensemble e);


#endif 