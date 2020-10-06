#include "Joueur.h" 

Joueur :: Joueur(std::string nom){
	this->nom = nom;
	this->monnaie = monnaie;
	this->entite = new Entite();
}

void Joueur :: ajoueMonnaie(int monnaie){
	this->monnaie+=monnaie;
}