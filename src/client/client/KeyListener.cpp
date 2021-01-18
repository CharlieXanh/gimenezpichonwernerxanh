#include <string>
#include "../client.h"
#include "../shared/state.h"
#include "../shared/engine.h"
#include <iostream>
#include <unistd.h>
#include <queue>
using namespace client;
using namespace state;
using namespace engine;
using namespace std;

KeyListener::KeyListener(engine::Engine &engine)
{
    engine.getEtat(); // ?
}


void KeyListener::cursorAction(state::Etat &state, int playerNum)
{
    if (state.getActionActuelle() == IDLE)
    {
        // infiniteSelecting(state, playerNum);
    }
    else if (state.getActionActuelle() == DEPLACEMENT)
    {
        // infiniteSelectMoving(state, playerNum);
    }
    else if (state.getActionActuelle() == COMBAT)
    {
        // int enemy = (playerNum == 1) ? 2 : 1;
        // infiniteSelecting(state, enemy);
    }
}

void KeyListener::triggerAction(engine::Engine& engine, KeyID key, int mouseX, int mouseY)
{
    int actualPlayer = engine.getEtat().getJouant();
    //verifyDead(engine.getEtat());
    switch (key)
    {
    case MOVE: // press M
    {
        bool selected = false;
        Position destination;
        for (auto &charac : engine.getEtat().getJoueurs())
        {
            if (charac->getStatut() == SEL && charac->getJoueurIndex() == actualPlayer)
            {
                selected = true;

                //
                //cout<< "Mouse X = " << mouseX << "  Y = " << mouseY <<endl;
                destination = engine.getEtat().getCurseur().getPosition();

                break;
            }
        }
        if (selected)
        {
            engine.getEtat().setActionActuelle(DEPLACEMENT);
            engine.getEtat().getCurseur().setVisible(true);
            engine.getEtat().getCurseur().setTileCode(2);
            StateEvent se{StateEventID::CURSOR_CHANGED};
            engine.getEtat().notifyObservers(se, engine.getEtat());
            engine.update();
            // faire le deplacement jusqu'a Destination
        }
        else if (!selected)
        {
            unique_ptr<engine::Commande> finTurnCmd(new engine::TerminerTourCommande());
            engine.ajoutCommande(move(finTurnCmd));
            engine.update();
            // StateEvent se{StateEventID::ALERT};
            // se.text = "First you have to select a character with ENTER";
            // engine.getEtat().notifyObservers(se, engine.getEtat());
        }
        break;
    }
    case ATTAQUER: // press A
    {
            engine.getEtat().setActionActuelle(COMBAT);
            engine.getEtat().getCurseur().setVisible(true);
            engine.getEtat().getCurseur().setTileCode(1);
            StateEvent se{StateEventID::CURSOR_CHANGED};
            engine.getEtat().notifyObservers(se, engine.getEtat());
        break;
    }
    // case PASS_TURN:
    // {
    //     std::unique_ptr<engine::Commande> ptr_fc(new engine::TerminerTourCommande());
    //     engine.ajoutCommande(move(ptr_fc));
    //     engine.update();
    //     break;
    // }
    case SELECT:
    {

        switch (engine.getEtat().getActionActuelle())
        {
        case IDLE:
        {
            cout << "Selecting a mapcell " << endl;
            cout<< "Mouse X = " << mouseX << "  Y = " << mouseY <<endl;

            Position pcurseur{mouseX,mouseY,"NORD"};
            engine.getEtat().getCurseur().deplacer(pcurseur);
            engine.getEtat().getCurseur().setVisible(true);
            engine.getEtat().getCurseur().setTileCode(3);
            engine.update();
            break;
        }
        case DEPLACEMENT:
        {
            //while(!toVisitQueue.empty()) toVisitQueue.pop();
            cout << "trying to move a character " << endl;
            cout<< "Mouse X = " << mouseX << "  Y = " << mouseY <<endl;
            Position pcurseur{mouseX,mouseY,"NORD"};
            engine.getEtat().getCurseur().deplacer(pcurseur);
            engine.getEtat().getCurseur().setVisible(true);
            engine.getEtat().getCurseur().setTileCode(3);

            for (auto &charac : engine.getEtat().getJoueurs())
            {
                if (charac->getJoueurIndex() == actualPlayer && charac->getStatut() == SEL)
                {
                    bool allowed = false;
                    for (auto &allowPos : charac->deplacementsPossibles(engine.getEtat()))
                    {
                        if (allowPos.egale(engine.getEtat().getCurseur().getPosition()))
                        {
                            allowed = true;
                            break;
                        }
                    }
                    if (allowed)
                    {
                        Position pos1{engine.getEtat().getCurseur().getPosition().getX(), engine.getEtat().getCurseur().getPosition().getY(), "NORD"};
                        unique_ptr<engine::Commande> ptr_mc1(new engine::DeplacerCommande(*charac, pos1));
                        engine.ajoutCommande(move(ptr_mc1));
                        engine.getEtat().setActionActuelle(IDLE);
                        engine.update();
                    }
                    else
                    {
                        cout << " not allowed to move here" << endl;
                    }
                }
            }
            engine.getEtat().setActionActuelle(IDLE);
            break;
        }
        case COMBAT:
        {

            cout << "trying to attack a target " << endl;
            cout<< "Mouse X = " << mouseX << "  Y = " << mouseY <<endl;
            Position pcurseur{mouseX,mouseY,"NORD"};
            engine.getEtat().getCurseur().deplacer(pcurseur);
            engine.getEtat().getCurseur().setVisible(true);
            engine.getEtat().getCurseur().setTileCode(1);

            for (auto &target : engine.getEtat().getJoueurs())
            {
                // finding the target
                if (target->getJoueurIndex() != actualPlayer)
                {
                    // if the cursor is placed in one enemy position.
                    if (target->getPosition().egale(engine.getEtat().getCurseur().getPosition()))
                    {
                        for (auto &attacker : engine.getEtat().getJoueurs())
                        {
                            if (attacker->getJoueurIndex() == actualPlayer && attacker->getStatut() == SEL)
                            {
                                int maxDistance = 1;
                                // if the target is within the max distance of the attacker
                                cout << attacker->getPosition().distance(target->getPosition()) << " <= " << maxDistance << endl;
                                if (attacker->getPosition().distance(target->getPosition()) <= maxDistance)
                                {
                                    unique_ptr<engine::Commande> ptr_ac1(new engine::AttaquerCommande(*attacker, *target));
                                    engine.ajoutCommande(move(ptr_ac1));
                                    engine.update();
                                    break;
                                }
                            }
                            else
                            {
                                engine.update();
                                cout << "trop loin de la cible" << endl;
                            }
                        }
                    }
                    else
                    {
                        engine.update();
                        cout << "Il n'y a pas de cible sur cette position" << endl;
                    }
                }
            }
            engine.getEtat().setActionActuelle(IDLE);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
    //return true;
}
