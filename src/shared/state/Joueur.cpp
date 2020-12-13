#include "Joueur.h"
#include "Etat.h"
#include <vector>

using namespace state;
using namespace std;

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

std::vector<Position> Joueur::deplacementsPossibles(state::Etat& etat){
  std::vector<Position> canGoList;
  std::vector<Position> validNears;

  for (auto &nearPosition : position.getPositionsAlentour())
      // if within map
      if (nearPosition.getY() >= 0 && nearPosition.getX() >= 0
      && (unsigned int)nearPosition.getX() <= etat.getMap()[0].size()
      && (unsigned int)nearPosition.getY() <= etat.getMap().size())
          validNears.push_back(move(nearPosition));

  for (auto &validNear : validNears)
      for (auto &line : etat.getMap())
      {
          // optimize here to continue if its not near
          if (abs(line[0]->getPosition().getX() - validNear.getX()) >= 2)
              continue;
          for (auto &mapcell : line)
          {
              if (abs(mapcell->getPosition().getY() - validNear.getY()) >= 2)
                  continue;
              if (mapcell->getPosition().egale(validNear) && mapcell->isSpace() && mapcell->isOccupied(etat) == -1)
                  canGoList.push_back(move(mapcell->getPosition()));
          }
      }
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
