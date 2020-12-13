#include "Position.h"

using namespace state;
using namespace std;

Position :: Position(int x,int y,std::string rotation){
	this->x=x;
	this->y=y;
	this->orientation = rotation;
}

void Position::setX(int x){
	this->x = x;
}

void Position::setY(int y){
	this->y=y;
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

std::string Position::getOrientation() {
	return this->orientation;
}

//Inutile (rotate)
void setOrientation(std::string orientation){
}

int Position :: getX() {
	return this->x;
}

int Position :: getY() {
	return this->y;
}

bool Position::egale(Position& autre){
	return (this->x == autre.getX() && this->y == autre.getY());
}

int Position::distance(Position& autre){
    // |x - otherX| + |y - otherY|
	return abs(this->x - autre.getX()) + abs(this->y - autre.getY());
}

std::vector<Position> Position::getPositionsAlentour(){
	// 4 positions, near
	// here we doesnt validate if he is within the map.
	std::vector<Position> result;
	Position north{this->getX(), this->getY() + 1};
	Position south{this->getX(), this->getY() - 1};
	Position west{this->getX() - 1, this->getY()};
	Position east{this->getX() + 1, this->getY()};
	result.push_back(move(north));
	result.push_back(move(south));
	result.push_back(move(west));
	result.push_back(move(east));

	return result;
}

Position::~Position(){
}
