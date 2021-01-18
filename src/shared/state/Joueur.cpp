#include "Joueur.h"
#include "Etat.h"
#include "SpaceMapCell.h"
#include <vector>
#include <iostream> //debug

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

Joueur :: Joueur ()
{
  this->nom = "";
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

void Joueur::setJoueurIndex(int newIndex){
  this->joueurIndex = newIndex;
}

std::vector<Position> Joueur::deplacementsPossibles(state::Etat& etat){
  std::vector<Position> canGoList;
  std::vector<Position> validNears;

  //cout << "Début calcul déplacements possibles" << endl;

  for (auto &nearPosition : position.getPositionsAlentour()){
      // if within map
      //cout << "etat getMap size = " << etat.getMap().size() << endl;

      if (nearPosition.getY() >= 0 && nearPosition.getX() >= 0
      && (unsigned int)nearPosition.getX() <= etat.getMap()[0].size()
      && (unsigned int)nearPosition.getY() <= etat.getMap().size()) {

          validNears.push_back(move(nearPosition));
          //cout << "Position alentour obtenues : " << nearPosition.getX() << " " << nearPosition.getY() << endl;
      }
  }

  for (auto &validNear : validNears)
      for (auto &line : etat.getMap())
      {
          // optimize here to continue if its not near
          // cout << "Lines" << endl;
          if (abs(line[0]->getPosition().getY() - validNear.getY()) >= 2)
              continue;
          for (auto &mapcell : line)
          {
          //  cout << "mapcells at "<< mapcell->getPosition().getX() << " " <<
          //  mapcell->getPosition().getY() <<" isSpace :" << mapcell->isSpace() << endl;
            if (abs(mapcell->getPosition().getX() - validNear.getX()) >= 2)
                  continue;

              if (mapcell->getPosition().egale(validNear) && mapcell->isSpace() && mapcell->isOccupied(etat) == -1){
                  canGoList.push_back(move(mapcell->getPosition()));
                  //cout << "fill cangolist" << endl;
                }
          }
      }
  return canGoList;
}

std::vector<int> Joueur::ciblesPossibles(Etat& etat){
  vector<int> possibleIndexes;
  for(unsigned int i = 0; i < etat.getJoueurs().size(); i++){
      Joueur& charac = *etat.getJoueurs()[i];
      if(charac.getNom() != this->getNom() && charac.getStatut() != MORT){
          // check distances
          int maxDistance = 2; //test value
          if(position.distance(charac.getPosition()) <= maxDistance){
              possibleIndexes.push_back(i);
          }
      }
  }
  return possibleIndexes;
}

int Joueur::getJoueurIndex(){
  return joueurIndex;
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

void Joueur::setMonnaie(int monnaie){
  this->monnaie = monnaie;
}

int Joueur::getDeplacementsBase() const{
  return this->deplacementsBase;
}

void Joueur::setDeplacementsBase(int deplacementsBase){
  this->deplacementsBase = deplacementsBase;
}

Joueur :: ~Joueur(){}
