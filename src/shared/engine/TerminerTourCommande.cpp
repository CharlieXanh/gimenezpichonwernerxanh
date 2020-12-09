#include "TerminerTourCommande.h"
// to use console
#include <iostream>

using namespace engine;
using namespace state;
using namespace std;

TerminerTourCommande::TerminerTourCommande (){
    id = TERMINER_TOUR;
}

void TerminerTourCommande::execute (state::Etat& state){
    state.setJouant(0);
    // at this point, the turn's owner has changed.
    state.setActionActuelle(IDLE);
    //state.getCurseur().setTileCode(2);
    bool curseurPositionAssigned = false;
    // other things?
    auto &joueur = state.getJoueurs()[state.getJouant()];
        if(joueur->getStatut() != MORT){

                if (!curseurPositionAssigned)
                {
                    state.getCurseur().setPosition(joueur->getPosition());
                    curseurPositionAssigned = true;
                }
                joueur->setStatut(DISP);
            }
            // if it's not your turn, then your alive characters will wait.
            else
                joueur->setStatut(ATT);

}
