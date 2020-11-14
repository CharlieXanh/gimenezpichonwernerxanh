#include "Obstacle.h"

using namespace state;

Obstacle :: Obstacle(int a, int b,Position& position){
	this->taille[0] = a;
	this->taille[1] = b;
	this->position = position;
}

const Position& Obstacle::getPosition() const {
	return this->position;
}
void setPosition(const Position& position){
//	this->position = position;
}

const std::vector<int>& Obstacle::getTaille() const {
	return this->taille;
}

void setTaille(const std::vector<int>& taille){
//	this->taille = taille;
}

Obstacle :: ~Obstacle(){}
