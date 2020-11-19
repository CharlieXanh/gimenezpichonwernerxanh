#include "Position.h"

using namespace state;

void Position::setX(int x){
	this->x = x;
}

void Position::setY(int y){
	this->y=y;
}

Position :: Position(int x,int y,std::string rotation){
	setX(x);
	setY(y);
	rotate(rotation);
}

Position::~Position(){
}

void Position::deplacer(int x,int y){
	this->x +=x;
	this->y +=y;
}

void Position::rotate(std::string rotation){
	this->orientation = rotation;
}

void Position :: placer(int x, int y){
	setX(x);
	setY(y);
}

const std::string& Position::getOrientation() const{
	return this->orientation;
}

void setOrientation(const std::string& orientation){

}

int Position :: getX() const{
	return this->x;
}

int Position :: getY() const{
	return this->y;
}
