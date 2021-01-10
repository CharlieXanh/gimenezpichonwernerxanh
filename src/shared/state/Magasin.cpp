#include "Magasin.h"

using namespace state;
Magasin::    Magasin (){

  //TODO generation aléatoire d'une 10aine d'item
  //génération manuelle test en attendant :
  Caracteristiques cara1{0,10,0,0,0};
  Item item1{"Epee en bois ",10,cara1};


  Caracteristiques cara2{10,15,0,0,0};
  Item item2{"Grande epee en bois",20,cara2};

  this->itemListe.push_back(item1);
  this->itemListe.push_back(item2);

}

std::vector<Item>&  Magasin::getItemListe (){
  return this->itemListe;

}

void Magasin::setItemListe (std::vector<Item>& newItemList){
  this->itemListe = newItemList;
}
