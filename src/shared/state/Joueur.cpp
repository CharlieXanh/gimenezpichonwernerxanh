#include "Joueur.h"

using namespace state;

 Joueur :: Joueur (std::string nom, int monnaie)
{
	this->nom = nom;
	this->monnaie = monnaie;
  this->position.setX(200);
  this->position.setY(200);
  this->statut = ATT;
  this-> deplacementsBase = 3;

  this->caracteristiques.setSante(100);
 }

void Joueur :: ajoueMonnaie(int monnaie){
	this->monnaie+=monnaie;
}

int Joueur::getDeplacements(){
  return this->deplacements;
}

void Joueur::setDeplacements(int restant){
  this->deplacements = restant;
}

std::vector<Position> Joueur::deplacementsPossibles(Etat& etat){
  std::vector<Position> canGoList;
  std::vector<Position> validNears;
  //
  // for (auto &nearPosition : position.getAlentour())
  //     // if within map
  //     if (nearPosition.getX() >= 0 && nearPosition.getY() >= 0 && nearPosition.getX() <= 255 - 1 && nearPosition.getY() <= state.getMap().size() - 1)
  //         validNears.push_back(move(nearPosition));
  //
  // for (auto &validNear : validNears)
  //     for (auto &line : state.getMap())
  //     {
  //         // optimize here to continue if its not near
  //         if (abs(line[0]->getPosition().getX() - validNear.getX()) >= 2)
  //             continue;
  //         for (auto &mapcell : line)
  //         {
  //             if (abs(mapcell->getPosition().getY() - validNear.getY()) >= 2)
  //                 continue;
  //             if (mapcell->getPosition().equals(validNear) && mapcell->isSpace() && mapcell->isOccupied(state) == -1)
  //                 canGoList.push_back(move(mapcell->getPosition()));
  //         }
  //     }
  return canGoList;
}

JoueurStatutID Joueur::getStatut() const{
  return this->statut;
}

void Joueur::setStatut(JoueurStatutID statut){
  this->statut = statut;
}

int Joueur::getMonnaie() const{
  return this->monnaie;
}

Joueur :: ~Joueur(){}
