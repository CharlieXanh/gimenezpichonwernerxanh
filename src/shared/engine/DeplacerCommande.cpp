#include "DeplacerCommande.h"
// to use console
#include <iostream>

using namespace engine;
using namespace state;
using namespace std;

DeplacerCommande::DeplacerCommande(state::Joueur &Jouant,
  state::Position &positionCible) : Jouant(Jouant), positionCible(positionCible)
{
    id = DEPLACER;
}

void DeplacerCommande::execute(state::Etat &etat)
{
  //TODO
}
