#include "Entite.h"

using namespace state;

Entite::Entite(){}

Entite :: Entite(Caracteristiques& caracteristiques, Position& position){
	 this->caracteristiques = caracteristiques;
	 this->position = position;
}

Entite :: ~Entite(){}
