#include "Entite.h"

using namespace state;


Entite :: Entite(Caracteristiques& caracteristiques, Position& position,
	std::string& nom){
	 this->caracteristiques = caracteristiques;
	 this->position = position;
	 this->nom = nom;
}

Entite::Entite()
{
	nom = "";
	position.setX(0);
	position.setY(0);
	Caracteristiques car{0,0,0,0,0};
	caracteristiques = car;
}


Entite :: ~Entite(){}

Caracteristiques& Entite ::  getCaracteristiques() {
	return this->caracteristiques;
}

void Entite ::setCaracteristiques( Caracteristiques caracteristiques){
	this->caracteristiques = caracteristiques;
}

Position& Entite :: getPosition() {
	return this->position;
}

void Entite ::  setPosition(Position position){
	this->position = position;
}

std::string Entite :: getNom() {
	return this->nom;
}

void Entite ::setNom(std::string nom){
	this->nom = nom;
}
