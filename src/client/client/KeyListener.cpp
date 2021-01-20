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
using namespace ai;
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
                    for (auto &allowPos : charac->deplacementsMaxPossibles(engine.getEtat()))
                    {
                        if (allowPos.egale(engine.getEtat().getCurseur().getPosition()))
                        {
                            allowed = true;
                            break;
                        }
                    }
                    if (allowed)
                    {
                        Position ptarget{engine.getEtat().getCurseur().getPosition().getX(), engine.getEtat().getCurseur().getPosition().getY(), "NORD"};
                        if (charac->getPosition().distance(ptarget) > 1){
                          std::vector<Position> path;

                          path = computePath(charac->getPosition(), ptarget, engine.getEtat().loadMapCell(), false);
                          int maxMoves = charac->getDeplacements();
                          for(int moves = 0 ; moves < maxMoves ; moves++){
                            unique_ptr<engine::Commande> ptr_mc1(new engine::DeplacerCommande(*charac, path[moves+1]));
                            engine.ajoutCommande(move(ptr_mc1));
                            engine.getEtat().setActionActuelle(IDLE);
                            engine.update();
                          }
                        }
                        else{
                          unique_ptr<engine::Commande> ptr_mc1(new engine::DeplacerCommande(*charac, ptarget));
                          engine.ajoutCommande(move(ptr_mc1));
                          engine.getEtat().setActionActuelle(IDLE);
                          engine.update();
                        }
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

std::vector<state::Position> KeyListener::computePath (state::Position &start, state::Position &end, std::vector<std::vector<int>> mapp, bool print){

    int i,index;
    Noeud* currentNoeud;
    cout << end.getX() << " " << end.getY() << endl;
    Noeud* endNoeud = new Noeud(end.getX(),end.getY(),NULL,NULL);
    Noeud* startNoeud = new Noeud(start.getX(),start.getY(),NULL,endNoeud);

    std::vector<state::Position> path;

    std::vector<Noeud*> listeFerme;
    std::vector<Noeud*> listeOuverte;
    listeOuverte.push_back(startNoeud);

    do{
        //Look for the best noeud in listOuverte
        i = 0;
        index=0;
        currentNoeud = listeOuverte[0];

        for(auto x : listeOuverte){
            if(x->getScore()["end"]<currentNoeud->getScore()["end"]){
                currentNoeud = x;
                index = i;
            }
            i++;
        }

        listeFerme.push_back(currentNoeud);

        listeOuverte = currentNoeud->voisins(mapp,listeFerme,listeOuverte,endNoeud);
        listeOuverte.erase(listeOuverte.begin()+index);

    }while( listeOuverte.size() > 0 && !endNoeud->inside(listeOuverte) );


    if(print){
        cout << "Dimension X,Y Map : [" << mapp[0].size() <<"," << mapp.size() <<"]" << endl;
        std::cout<<"Start : "<<startNoeud->getX()<< " " << startNoeud->getY()<<std::endl;
        std::cout<<"End : "<<endNoeud->getX()<< " " << endNoeud->getY()<<std::endl;
        std::cout << "Path :" << std::endl;

        //Print map  mapp[y][x]
        bool pass;
        for(unsigned int  i = 0;i<mapp.size();i++){
            for(unsigned int j=0;j<mapp[i].size();j++){
                pass = true;
                for(auto x : listeFerme){
                    if(x->getX()==(int)j && x->getY()==(int)i){
                        std::cout<< "\033[1;35m" << mapp[i][j] << "\033[0m" <<" ";
                        pass = false;
                    }
                }
                if(pass){
                    if(((int)i==startNoeud->getX() && (int)j==startNoeud->getY())  || ((int)i==endNoeud->getX() && (int)j==endNoeud->getY()))
                        std::cout<< "\033[1;35m" << mapp[i][j] << "\033[0m" <<" ";
                    else if (mapp[i][j]==1)
                        std::cout<< "\033[1;31m" << mapp[i][j] << "\033[0m" <<" ";
                    else if(mapp[i][j]==0)
                        std::cout<< "\033[1;37m" << mapp[i][j] << "\033[0m" <<" ";
                }
            }
            std::cout<<std::endl;
        }
    }
    if(endNoeud->inside(listeOuverte)){
        //cout << "end noeud est dans liste ouverte" << endl;
        endNoeud->parent = currentNoeud;
        Noeud* cheminNoeud = endNoeud;
        while(cheminNoeud!=NULL){
            //cout << "cheminnoeud xy :"<< cheminNoeud->getX() << " "<< cheminNoeud->getY()<<endl;
            state::Position add{cheminNoeud->getX(),cheminNoeud->getY(),"NORD"};
            path.insert(path.begin(),add);
            cheminNoeud = cheminNoeud->parent;
        }
        return path;
    }
    path.push_back(start);
    return path;
}
