#include "MapCell.h"
#include "Joueur.h"
#include "Etat.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>

using namespace std;
using namespace state;

bool MapCell::isMapCell(){
    return true;
}

// Returns the position of a character in the characters list
// if is in this position. Else it returns -1
int MapCell::isOccupied(Etat& etat){
    int res = -1;

    // iterate the character lists to check if one is in this mapcell
	vector<std::unique_ptr<Joueur>> & joueursList = etat.getJoueurs();
    for (size_t i = 0; i < joueursList.size(); i++)
    {
        if(position.egale(joueursList[i]->getPosition()) && joueursList[i]->getStatut() != MORT)
            res =  i;
        else
            res = -1;

        if (res != -1) break;
    }
    return res;
}


// Setters and Getters
