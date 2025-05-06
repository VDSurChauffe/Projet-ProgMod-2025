#include "stats.hpp"
#include <fstream>
#include <iostream>

void sauvegarderStatsCSV(const vector<int> nbLapins, const vector<int> nbRenards, int nbrTours) {
    ofstream csv("statistiques/evolution.csv");
    if (!csv.is_open()) {
        cerr << "Erreur lors de l'ouverture du fichier CSV." << endl;
        return;
    }

    csv << "temps;lapins;renards\n";
    for (int i = 0; i < nbrTours; ++i) {
        csv << i << ";" << nbLapins[i] << ";" << nbRenards[i] << "\n";
    }
    csv.close();
}
