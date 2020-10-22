#include "Obstacle.h"

Obstacle :: Obstacle(int a, int b,Position* position){
	this->taille[0] = a;
	this->taille[1] = b;
	this->position = position;
}

int Obstacle::getX() const {
	return this->position->getX();
}

int Obstacle::getY() const {
	return this->position->getY();
}