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
    int jouantid = state.getJouant();
    int nbrJoueurs = state.getNbrJoueurs();

    //joueur précendent n'est plus selectionné
    auto &joueurprec = state.getJoueurs()[jouantid];
    joueurprec->setStatut(ATT);
    joueurprec->setDeplacements(3);

    //Changer le joueur jouant
    state.setJouant((jouantid +1 )% nbrJoueurs);


    state.setActionActuelle(IDLE);
    state.getCurseur().setTileCode(2);
    bool curseurPositionAssigned = false;

    // other things?
    auto &joueur = state.getJoueurs()[state.getJouant()];
        if(joueur->getStatut() != MORT){

                if (!curseurPositionAssigned)
                {
                    state.getCurseur().setPosition(joueur->getPosition());
                    curseurPositionAssigned = true;
                }
                joueur->setStatut(SEL);
            }
            // if it's not your turn, then your alive characters will wait.
            else
                joueur->setStatut(MORT);

}
