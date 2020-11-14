#include "Zone.h"
using namespace state;

Zone :: Zone(int a,int b, Position& position,std::string type){
	this->taille[0] = a;
	this->taille[1] = b;
	this->position = position;
	this->type=type;
}


Zone :: ~Zone(){};
