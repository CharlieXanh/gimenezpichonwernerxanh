#include "Etat.h"

using namespace state;

Etat :: Etat(std::vector<Joueur> joueurs, std::vector<Joueur> ennemis,Joueur jouant,
            Curseur curseur){

  this->joueurs = joueurs;
  this->ennemis = ennemis;


  this->jouant = jouant;

  this->tour = 0;
  this->multijoueur = false;
  this->terminerJeu = false;
  Curseur curs{0,0};
  this->curseur = curs;

}

void Etat:: init(){

}

int Etat::initJoueur(Joueur joueur){
  this->joueurs.push_back(joueur);
  return 0;

}

int Etat::changeJouant(Joueur joueurSuivant){
  this->jouant = joueurSuivant;
  return 0;
}

int Etat::transitionEtat(Etat etat){
  return 0;

}
