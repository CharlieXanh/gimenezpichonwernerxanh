#include "Ordre.h"
#include "Etat.h"
#include <iostream>
#include <unistd.h>

using namespace state;
using namespace std;

Ordre::    Ordre (state::Etat& etat)
: joueurs(etat.getJoueurs())
{}

Ordre::    ~Ordre (){}

int Ordre::JoueurSuivant (state::Etat& etat){
  int index = etat.getTour() % etat.getNbrJoueurs();
  return index+1;
}

bool Ordre::supprJoueur (Joueur& joueur){
//  this->joueurs.remove(joueur);
  return true;
}

void Ordre::AjoutJoueur (Joueur& joueur){
//  this->joueurs.push_back(joueur);
}

void Ordre::printOrdre (state::Etat& etat){
  cout << " Joueur "<< etat.getTour() % etat.getNbrJoueurs() << endl;
  for(int i = 0; i < etat.getNbrJoueurs() ; i++){
    cout << " -> Joueur "<< etat.getTour() % etat.getNbrJoueurs()+i << endl;
  }
}
