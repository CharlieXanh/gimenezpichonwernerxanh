#include "Engine.h"
#include "engine.h"
#include <iostream>
#include <unistd.h>

using namespace state;
using namespace engine;
using namespace std;

Engine::Engine() : etatActuel("engine")
{
}

Engine::Engine(std::string stateMode) : etatActuel(stateMode)
{}

Engine::~Engine()
{
}

state::Etat &Engine::getEtat()
{
    state::Etat &refEtat = etatActuel;
    return refEtat;
}

void Engine::addPassiveCommandes()
{
    int priority = 0;
    // if commandesActuelles isnt empty
    if (commandesActuelles.size() > 0)
        // find largest priority
        priority = commandesActuelles.rbegin()->first + 1;

    // passive commands...
    unique_ptr<Commande> ptr_cw(new VictoireCommande());
    ajoutCommande(move(ptr_cw), priority++);
    bool addFinishTurn = false;
    for (size_t i = 0; i < commandesActuelles.size(); i++)
    {
        if (commandesActuelles[i]->getCommandeID() == ATTAQUER)
        {
            addFinishTurn = true;
            break;
        }
    }
    if (addFinishTurn)
    {
        cout << "finishing because you attacked" << endl;
        unique_ptr<Commande> ptr_ft(new TerminerTourCommande());
        ajoutCommande(move(ptr_ft), priority++);
    }
}

void Engine::ajoutCommande(std::unique_ptr<Commande> ptr_cmd, int priorite)
{
    if (priorite == -1)
    {
        // find largest priority
        if (commandesActuelles.size() > 0)
            priorite = commandesActuelles.rbegin()->first + 1;
        else
        {
            priorite = 0;
        }
    }
    commandesActuelles[priorite] = move(ptr_cmd);
}

void Engine::update()
{
    if (!etatActuel.getTerminerJeu())
    {
      //  cout << "Adding passive commands ..." << endl;
        addPassiveCommandes();
      //  cout << "Executing commands from turn " << etatActuel.getTour() << endl;
        //default event
        StateEvent stateEvent(ALLCHANGED);
        bool endTurn = false;
        for (size_t i = 0; i < commandesActuelles.size(); i++)
        {
            stateEvent.setStateEventID(CHARACTERCHANGED);

            if (etatActuel.mode == "engine")
            {
                if (endTurn == false && commandesActuelles[i]->getCommandeID() == TERMINER_TOUR)
                {
                    etatActuel.setTour(etatActuel.getTour() + 1);
                    endTurn = true;
                }
            }
            else
            {
                if ((endTurn == false && (commandesActuelles[i]->getCommandeID() == ATTAQUER)) || (commandesActuelles[i]->getCommandeID() == TERMINER_TOUR))
                {

                    etatActuel.setTour(etatActuel.getTour() + 1);
                    endTurn = true;
                }
            }

            // TODO: Execute only the player active's commands.
            commandesActuelles[i]->execute(etatActuel);
            etatActuel.notifyObservers(stateEvent, etatActuel);
            usleep(150 * 1000);

        }
        // clean using iterator
        map<int, std::unique_ptr<Commande>>::iterator iterator;
        for (iterator = commandesActuelles.begin(); iterator != commandesActuelles.end(); iterator++)
        {
            commandesActuelles.erase(iterator);
        }
    }
    else
    {
        cout << "The game is ended, we have a winner" << endl;
    }
}
