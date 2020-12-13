#include "Ordre.h"

using namespace state;

Ordre::    Ordre (std::vector<std::unique_ptr<Joueur>>& joueurs)
: joueurs(joueurs)
{}

Ordre::    ~Ordre (){}

Joueur& Ordre::JoueurSuivant (){
  Joueur def{"Default",0};
  return def;
}

bool Ordre::supprJoueur (Joueur& joueur){
  //this->joueurs.remove(joueur);
  return true;
}

void Ordre::AjoutJoueur (Joueur& joueur){
  //this->joueurs.push_back(joueur);

}

std::vector<std::string> Ordre::getOrdre (){
  std::vector<std::string> order;
  return order;
}
