#include "Joueur.h"

using namespace state;

 Joueur :: Joueur (std::string nom, Entite& entite, int monnaie)
{
	this->nom = nom;
	this->monnaie = monnaie;
	this->entite =  entite;
 }

void Joueur :: ajoueMonnaie(int monnaie){
	this->monnaie+=monnaie;
}

Joueur :: ~Joueur(){}
