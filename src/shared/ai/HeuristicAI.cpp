#include "ai.h"
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

void HeuristicAI::run(engine::Engine &engine)
{
    //int randomCharSelected = selectPersonnage(engine.getEtat());
    // always select someone
    Joueur &selectedChar = *engine.getEtat().getEnnemis()[numeroEnnemi];
    //unique_ptr<Commande> selectCommand(new SelectCharacterCommand(selectedChar));
    //engine.ajoutCommande(move(selectCommand));
    selectedChar.setStatut(SEL);

    // can attack?
    if (selectedChar.ciblesPossibles(engine.getEtat()).size() > 0)
    {
        // can attack
        cout << "first if can attack ? true " << endl;
        int moves = selectedChar.getDeplacements();
        while (selectedChar.ciblesPossibles(engine.getEtat()).size() > 0 && moves > 0)
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
                unique_ptr<Commande> finTurnCmd(new TerminerTourCommande());
                engine.ajoutCommande(move(finTurnCmd));
                engine.update();
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


int HeuristicAI::getNumeroEnnemi (){
    return numeroEnnemi;
}

void HeuristicAI::setNumeroEnnemi (int pn){
    numeroEnnemi = pn;
}

//computePath :
