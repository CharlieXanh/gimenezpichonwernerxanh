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
    // always select someone
    Joueur &selectedChar = *engine.getEtat().getJoueurs()[numeroEnnemi];
    int maxMoves = selectedChar.getDeplacements();

    //selectedChar.setStatut(SEL);

    // can attack?
    if (selectedChar.ciblesPossibles(engine.getEtat()).size() > 0)
    {
        // can attack
        cout << "[IA heu] peut attaquer" << endl;

          //todo select player with lowest def or health
            int random = selectedChar.ciblesPossibles(engine.getEtat())[(rand() % (selectedChar.ciblesPossibles(engine.getEtat()).size()))];
            Joueur &targetToAttack = *engine.getEtat().getJoueurs()[random];

                // attack
                unique_ptr<Commande> atkCmd(new AttaquerCommande(selectedChar, targetToAttack));
                engine.ajoutCommande(move(atkCmd));

                engine.update();
                return;
    }
    else
    {

        cout << "[IA heu] se déplace vers un joueur" << endl;
        int moves = selectedChar.getDeplacements();
        while ( moves > 0)
        {
            //start, end, mapp, print(bool)
            int distance= 1000;
            Position ptarget = selectedChar.getPosition();
            for(auto& cible : engine.getEtat().getJoueurs()){
              if(cible->getJoueurIndex() != selectedChar.getJoueurIndex()){
                cout << "distance :" << selectedChar.getPosition().distance(cible->getPosition()) << endl;
                if( distance > selectedChar.getPosition().distance(cible->getPosition())){
                  distance = selectedChar.getPosition().distance(cible->getPosition());
                  ptarget = cible->getPosition();
                }
              }

            }

            cout << "[IA heu] calcul de la trajectoire" << endl;
            cout << " --- Depart : " << selectedChar.getPosition().getX()<< " " <<
                                        selectedChar.getPosition().getY()<< endl;
            cout << " --- Cible : " << ptarget.getX()<< " " <<
                                             ptarget.getY()<< endl;
            std::vector<Position> path = computePath(selectedChar.getPosition(), ptarget, engine.getEtat().loadMapCell(), true);


            cout << " --- Destination : " << path[1].getX()<< " " <<
                                             path[1].getY()<< endl;


            unique_ptr<Commande> mvCmd(new DeplacerCommande(selectedChar, path[1]));
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

std::vector<state::Position> HeuristicAI::computePath (state::Position &start, state::Position &end, std::vector<std::vector<int>> mapp, bool print){

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
        for(int  i = 0;i<mapp.size();i++){
            for(int j=0;j<mapp[i].size();j++){
                pass = true;
                for(auto x : listeFerme){
                    if(x->getX()==j && x->getY()==i){
                        std::cout<< "\033[1;35m" << mapp[i][j] << "\033[0m" <<" ";
                        pass = false;
                    }
                }
                if(pass){
                    if((i==startNoeud->getX() && j==startNoeud->getY())  || (i==endNoeud->getX() && j==endNoeud->getY()))
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
        cout << "end noeud est dans liste ouverte" << endl;
        endNoeud->parent = currentNoeud;
        Noeud* cheminNoeud = endNoeud;
        while(cheminNoeud!=NULL){
            cout << "cheminnoeud xy :"<< cheminNoeud->getX() << " "<< cheminNoeud->getY()<<endl;
            state::Position add{cheminNoeud->getX(),cheminNoeud->getY(),"NORD"};
            path.insert(path.begin(),add);
            cheminNoeud = cheminNoeud->parent;
        }
        return path;
    }
    path.push_back(start);
    return path;
}


int HeuristicAI::getNumeroEnnemi (){
    return numeroEnnemi;
}

void HeuristicAI::setNumeroEnnemi (int pn){
    numeroEnnemi = pn;
}
