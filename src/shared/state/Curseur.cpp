#include "Curseur.h"


using namespace std;
using namespace state;

Curseur:: Curseur(int x, int y){
  this->lastPosition.setX(x);
  this->lastPosition.setY(y);
  this->position.setX(x);
  this->position.setY(y);
  visible = false;
}

state::Position& Curseur::getLastPosition(){
  return this->lastPosition;
}

void Curseur::deplacer(Position &destination){
  this->lastPosition = position;
  this->position = destination;
}

bool Curseur::getVisible(){
  return visible;
}

void Curseur::setVisible(bool visibilite){
  this->visible = visibilite;
}
