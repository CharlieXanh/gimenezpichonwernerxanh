#include "Etat.h"

using namespace state;

 // Etat::Etat (){
 // }

void Etat::init(){

}

int  Etat::initJoueur(Joueur joueur){
  // joueur.e->caracteristiques->setAttaque(20);
  // joueur->entite->position->placer(0,0);

  this->joueurs.push_back(joueur);
return 0;
}

int Etat::changeJouant(Joueur joueurSuivant){
return 0;
}

int Etat::transitionEtat(Etat etat){
return 0;
}
