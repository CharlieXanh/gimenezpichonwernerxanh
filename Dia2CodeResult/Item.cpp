#include "Item.h"

Item::Item(std::string nom, int prix, Caracteristiques* bonus){
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

std::string Item::getNom() const{
  return this->nom;
}

void Item::setNom(std::string nom){
  this->nom = nom;
}

Caracteristiques* Item::getBonus() {
  return this->bonus;
}

void Item::setBonus(Caracteristiques*  bonus){
  this->bonus = bonus;
}
