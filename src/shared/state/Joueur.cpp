#include "Joueur.h"

using namespace state;

 Joueur :: Joueur (std::string nom, int monnaie)
{
	this->nom = nom;
	this->monnaie = monnaie;
 }

void Joueur :: ajoueMonnaie(int monnaie){
	this->monnaie+=monnaie;
}

Joueur :: ~Joueur(){}
