#include "Item.h"

using namespace state;

Item::Item(std::string nom, int prix, Caracteristiques & bonus) :
 nom(nom), bonus(bonus),prix(prix)
{}

int Item::getPrix() const{
  return this->prix;
}

void Item::setPrix(int prix){
  this->prix = prix;
}

const std::string& Item::getNom() const{
  return this->nom;
}

void Item::setNom(const std::string& nom){
  this->nom = nom;
}

const Caracteristiques& Item::getBonus() const {
  return this->bonus;
}

void Item::setBonus(const Caracteristiques&  bonus){
  this->bonus = bonus;
}

Item:: ~Item(){}
