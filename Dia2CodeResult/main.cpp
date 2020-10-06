#include "Position.h"
#include "Entite.h"
#include <iostream>

int main(void){

	Position* p = new Position(2,5);
	std::cout << "x : " << p->getX() << " y : " << p->getY() <<"\n"; 
	std::cout << "Orientation : "<< p->getOrientation() <<"\n";

	p->rotate("Sud");
	std::cout << "Orientation : "<< p->getOrientation() <<"\n";
	p->placer(18,54);
	std::cout << "x : " << p->getX() << " y : " << p->getY() <<"\n"; 
	p->deplacer(-18,-5);
	std::cout << "x : " << p->getX() << " y : " << p->getY() <<"\n"; 

	return 0;
}