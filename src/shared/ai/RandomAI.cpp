#include "../ai.h"
#include "engine.h"
#include "state.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

using namespace ai;
using namespace engine;
using namespace state;
using namespace std;

void RandomAI::run(engine::Engine &engine)
{
    //int randomCharSelected = selectPersonnage(engine.getEtat());
    // always select someone
    Joueur &selectedChar = *engine.getEtat().getJoueurs()[numeroEnnemi];
    //unique_ptr<Commande> selectCommand(new SelectCharacterCommand(selectedChar));
    //engine.ajoutCommande(move(selectCommand));
    //selectedChar.setStatut(SEL);
    selectedChar.setDeplacements(3);

    // can attack?
    if (selectedChar.ciblesPossibles(engine.getEtat()).size() > 0)
    {
        // can attack
        cout << "first if can attack ? true " << endl;
        int moves = selectedChar.getDeplacements();
        while (selectedChar.ciblesPossibles(engine.getEtat()).size() > 0)
        {
            int random = selectedChar.ciblesPossibles(engine.getEtat())[(rand() % (selectedChar.ciblesPossibles(engine.getEtat()).size()))];
            Joueur &targetToAttack = *engine.getEtat().getJoueurs()[random];
            // choose to attack or to move (0 move, 1 attack)
            if ((rand() % 2))
            {
                // attack
                unique_ptr<Commande> atkCmd(new AttaquerCommande(selectedChar, targetToAttack));
                engine.ajoutCommande(move(atkCmd));
                engine.update();
                // unique_ptr<Commande> finTurnCmd(new TerminerTourCommande());
                // engine.ajoutCommande(move(finTurnCmd));
                // engine.update();
                return;
            }
            else
            {
                // move
                int randomMove = (rand() % selectedChar.deplacementsPossibles(engine.getEtat()).size());
                Position &p = selectedChar.deplacementsPossibles(engine.getEtat())[randomMove];
                unique_ptr<Commande> mvCmd(new DeplacerCommande(selectedChar, p));
                engine.ajoutCommande(move(mvCmd));
                engine.update();
                moves--;
            }
        }
        unique_ptr<Commande> finTurnCmd(new TerminerTourCommande());
        engine.ajoutCommande(move(finTurnCmd));
        engine.update();

    }
    else
    {
        int moves = selectedChar.getDeplacements();
        while ( moves > 0)
        {
            // can NOT attack, JUST MOVE.
            int randomMove = (rand() % selectedChar.deplacementsPossibles(engine.getEtat()).size());
            Position p{selectedChar.deplacementsPossibles(engine.getEtat())[randomMove].getX(), selectedChar.deplacementsPossibles(engine.getEtat())[randomMove].getY()};
            unique_ptr<Commande> mvCmd(new DeplacerCommande(selectedChar, p));
            engine.ajoutCommande(move(mvCmd));
            engine.update();
            moves--;
            cout << " move executed " << endl;

            // now i was deplaced, can attack?
            if (selectedChar.ciblesPossibles(engine.getEtat()).size())
            {
                // just attack
                int random = selectedChar.ciblesPossibles(engine.getEtat())[(rand() % (selectedChar.ciblesPossibles(engine.getEtat()).size()))];
                Joueur &targetToAttack = *engine.getEtat().getJoueurs()[random];
                unique_ptr<Commande> atkCmd(new AttaquerCommande(selectedChar, targetToAttack));
                engine.ajoutCommande(move(atkCmd));
                engine.update();

                unique_ptr<Commande> finTurnCmd(new TerminerTourCommande());
                engine.ajoutCommande(move(finTurnCmd));
                engine.update();
                return;
            }
        }
        unique_ptr<Commande> finTurnCmd(new TerminerTourCommande());
        engine.ajoutCommande(move(finTurnCmd));
        engine.update();
        return;
    }
}

// int RandomAI::selectPersonnage (state::Etat& etat){
//     std::vector<int> posibleIndex;
//
//     for(unsigned int i = 0; i < etat.getJoueurs().size(); i++){
//         Joueur &charac = *etat.getJoueurs()[i];
//         if(charac.getJoueurIndex() == numeroJoueur && charac.getStatut() != MORT)
//             posibleIndex.push_back(i);
//     }
//
//     int randomNumber = rand() % posibleIndex.size();
//     cout << "[";
//     for(auto &index : posibleIndex){
//         cout << index << ", ";
//     }
//     cout << "]" << endl;
//     return posibleIndex[randomNumber];
// }

int RandomAI::getNumeroEnnemi (){
    return numeroEnnemi;
}

void RandomAI::setNumeroEnnemi (int pn){
    numeroEnnemi = pn;
}
