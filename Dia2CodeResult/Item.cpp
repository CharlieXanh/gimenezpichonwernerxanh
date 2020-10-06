#include "Item.h"

Item::Item(String nom, int prix, Caracteristique bonus){
  this->nom = nom;

  this->setPrix(prix);

  this->bonus = bonus;
}

int Item::getPrix() const{
  return this->prix;
}

void Item::setPrix(int prix){
  this->prix = prix;
}

int Item::getNom() const{
  return this->nom;
}

void Item::setNom(String nom){
  this->nom = nom;
}
