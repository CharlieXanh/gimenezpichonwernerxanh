#include "DeplacerCommande.h"
// to use console
#include <iostream>

using namespace engine;
using namespace state;
using namespace std;

DeplacerCommande::DeplacerCommandeCommand(state::Joueur &Jouant,
  state::Position &positionTarger) : Jouant(Jouant), positionTarget(positionTarger)
{
    id = DEPLACER;
}

void DeplacerCommande::execute(state::Etat &etat)
{
  //TODO
}
