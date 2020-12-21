#include "DeplacerCommande.h"
// to use console
#include <iostream>

using namespace engine;
using namespace state;
using namespace std;

DeplacerCommande::DeplacerCommande(state::Joueur &joueurCible,
  state::Position &positionCible) : joueurCible(joueurCible), positionCible(positionCible)
{
    id = DEPLACER;
}

void DeplacerCommande::execute(state::Etat &etat)
{
  cout << "Deplacement d'un joueur" << endl;
  bool allowed = false;
  if (joueurCible.getStatut() == SEL)
  {
      // if the character has moves to do
      cout << "Chances de déplacements restantes : " << joueurCible.getDeplacements() << endl;
      if (joueurCible.getDeplacements() > 0)
      {
          //Check deplacements autorisés
          //cout << "calcul deplacements cibles Possibles" << endl;
          for (auto &pos: joueurCible.deplacementsPossibles(etat))
          {
              if (pos.egale(positionCible))
              {
                  //cout << "position cible autorisé" << endl;
                  allowed = true;
                  break;
              }
          }
          if (allowed)
          {
              // Moving
              joueurCible.getPosition().setX(positionCible.getX());
              joueurCible.getPosition().setY(positionCible.getY());
              joueurCible.setDeplacements(joueurCible.getDeplacements() - 1);
              // TODO refresh to the base move quantity for each character if the are not death.

              cout << "Le joueur " << joueurCible.getNom() << " a été déplacé en [" << positionCible.getX() << ", " << positionCible.getY() << "]" << endl;
              cout << "Chance de déplacement décrémentée, le joueur en a " << joueurCible.getDeplacements() << " restantes" << endl;
          }
          else
              cout << "Le joueur " << joueurCible.getNom() << " ne peut pas se déplacer à cette position" << endl;
      }
      else
          cout << "Plus de déplacement possible" << endl;
  }
  cout << "\n";
}
