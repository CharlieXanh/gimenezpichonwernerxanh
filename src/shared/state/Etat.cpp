#include "Etat.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>

using namespace std;
using namespace state;

Etat::Etat(std::string nMode) : curseur(10, 10), ordre(*this)
{
    this-> mode = nMode;
    cout << "Creation d'un objet ETAT en mode >>>" + mode + "<<<\n";
    actionActuelle = IDLE;
    cout << "Creation d'un objet MAGASIN" << endl;
    Magasin mag;
    this -> magasin = mag;

}

// Etat :: Etat(std::vector<Joueur> joueurs, std::vector<Joueur> ennemis,Joueur jouant,
//             Curseur curseur){
//
//   this->joueurs = joueurs;
//   this->ennemis = ennemis;
//
//
//   this->jouant = jouant;
//
//   this->tour = 0;
//   this->multijoueur = false;
//   this->terminerJeu = false;
//   Curseur curs{0,0};
//   this->curseur = curs;
//
// }

std::string Etat::getMode(){
  return mode;
}

std::vector<std::unique_ptr<Joueur>> &Etat::getJoueurs()
{
    vector<unique_ptr<Joueur>> &refCharacters = joueurs;
    return refCharacters;
}

int Etat::getNbrJoueurs(){
  return this->nbrJoueurs;
}

int Etat::getTour()
{
  return tour;
}

bool Etat::getTerminerJeu(){
  return terminerJeu;
}

EtatActionActuelleID Etat::getActionActuelle()
{
  return actionActuelle;
}

void Etat::setActionActuelle(EtatActionActuelleID newAction)
{
  this->actionActuelle = newAction;
}

Curseur& Etat::getCurseur()
{
  Curseur &refCurseur = curseur;
  return refCurseur;
}

void Etat:: init(){}


void Etat::initJoueurs(){

  if(mode == "engine")
  {
    std::unique_ptr<Joueur> ptrJ1(new Joueur("Raph", 20));
    ptrJ1->getCaracteristiques().setSante(100);
    ptrJ1->getCaracteristiques().setAttaque(10);
    ptrJ1->getCaracteristiques().setDefense(5);
    joueurs.push_back(move(ptrJ1));

    std::unique_ptr<Joueur> ptrJ2(new Joueur("Leo", 17));
    ptrJ2->getCaracteristiques().setSante(100);
    ptrJ2->getCaracteristiques().setAttaque(10);
    ptrJ2->getCaracteristiques().setDefense(5);
    joueurs.push_back(move(ptrJ2));
  }
  else
  {
    cout << "Pas en mode engine" << endl;
  }

curseur.setPosition(joueurs[0]->getPosition());
cout << "Joueurs initialisés" << endl;

}

void Etat::setTour(int tour)
{
  this->tour = tour;
}

void Etat::setTerminerJeu(bool resultat)
{
  this->terminerJeu = resultat;
}

int Etat::getJouant()
{
  return this->jouant;
}

void Etat::setJouant(int joueurSuivant){
  this->jouant = joueurSuivant;
}
std::vector<std::vector<std::unique_ptr<MapCell>>>& Etat::getMap(){
  return this->map;
}
void Etat::transitionEtat(Etat etat){
}

Etat::~Etat(){}
