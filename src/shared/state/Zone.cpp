#include "Zone.h"
using namespace state;

Zone :: Zone(int a,int b, Position& position,std::string type){
	this->taille.push_back(a);
	this->taille.push_back(b);
	this->position = position;
	this->type=type;
}


Zone :: ~Zone(){};
