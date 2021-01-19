
#include "VictoireCommande.h"
// to use console
#include <iostream>

using namespace engine;
using namespace state;
using namespace std;

VictoireCommande::VictoireCommande()
{
    id = VICTOIRE;
}

void VictoireCommande::execute(state::Etat &state)
{
    int groupeVainqueur = 0;
    bool groupeJoueursVivant = false;
    bool groupeEnnemisVivant = false;


    for (auto &personnage : state.getJoueurs())
    {
        // equipe joueur
        if (personnage->getEstEnnemi() == false )
        {
            if (personnage->getStatut() != MORT)
            {
                cout << "un joueur est en vie" << endl;
                groupeJoueursVivant = true;
                break;
            }
            else groupeJoueursVivant = false;
        }
    }

    for (auto &personnage : state.getJoueurs())
    {
        // ennemis
        if (personnage->getEstEnnemi() == true)
        {
            if (personnage->getStatut() != MORT)
            {
                cout << "un ennemi est en vie" << endl;
                groupeEnnemisVivant = true;
                break;
            }
            else groupeEnnemisVivant = false;
        }
    }

    if(!groupeEnnemisVivant)
    {
        groupeVainqueur = 1;
    } else if (!groupeJoueursVivant) {
        groupeVainqueur = 2;
    }

    switch(groupeVainqueur) {
        case 0 :
            //pas de gagnant ce tour
            cout << "pas de gagnant" << endl;
            break;
        case 1 :
            //Joueurs gagnent
            cout << endl << "ATENTION!!! LES JOUEURS ONT GAGNE " << endl;
            state.setTerminerJeu(true);
            break;
        case 2 :
            //Ennemis gagnent
            cout << endl << "ATENTION!!! LES ENNEMIS ONT GAGNE " << endl;
            state.setTerminerJeu(true);
            break;
    }
    // both in game? 0. p1 in game? then he's the winner. if not, p2.
    /*
    winner = (p1StillInGame && p2StillInGame) ? 0 : (p1StillInGame) ? 1 : 2;
    if(winner){
        state.setEnd(true);
        state.setWinner(winner);
        EtatEvent se{EtatEventID::WINNER};
        state.notifyObservers(se, state);
        cout << endl << "ATENTION!!! THE WINNER IS THE PLAYER " << winner << endl;
        cout << endl << "All the opponent's personnageters are dead" << endl;
    }
    */
}
