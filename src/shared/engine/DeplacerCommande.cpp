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
      cout << "Move chances left " << joueurCible.getDeplacements() << endl;
      if (joueurCible.getDeplacements() > 0)
      {
          //Check deplacements autorisés
          for (auto &pos: joueurCible.deplacementsPossibles(etat))
          {
              if (pos.egale(positionCible))
              {
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

              cout << "The character " << joueurCible.getNom() << " has been moved to [" << positionCible.getX() << ", " << positionCible.getY() << "]" << endl;
              cout << "Decreasing by 1 moving chances, now the character has " << joueurCible.getDeplacements() << " move chances left" << endl;
          }
          else
              cout << "The character " << joueurCible.getNom() << " can't move to that position" << endl;
      }
      else
          cout << "Can't move anymore" << endl;
  }
  cout << "\n";
}
