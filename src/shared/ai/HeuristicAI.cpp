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

std::vector<std::vector<int>> HeuristicAI::computePath(std::vector<int> start, std::vector<int> end, std::vector<std::vector<int>> mapp, bool print = false){
    int i,index;
    Noeud* currentNoeud;

    Noeud* endNoeud = new Noeud(end[0],end[1],NULL,NULL);
    Noeud* startNoeud = new Noeud(start[0],start[1],NULL,endNoeud);

     std::vector<std::vector<int>> path;

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

    }while(listeOuverte.size()>0 && !endNoeud->inside(listeOuverte));

    if(print){
        std::cout<<"Start : "<<startNoeud->getX()<< " " << startNoeud->getY()<<std::endl;
        std::cout<<"End : "<<endNoeud->getX()<< " " << endNoeud->getY()<<std::endl;
        std::cout << "Path :" << std::endl;

        //Print map
        bool pass;
        for(int  i = 0;i<mapp.size();i++){
            for(int j=0;j<mapp[i].size();j++){
                pass = true;
                for(auto x : listeFerme){
                    if(x->getX()==i && x->getY()==j){
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
        endNoeud->parent = currentNoeud;
        Noeud* cheminNoeud = endNoeud;
        while(cheminNoeud!=NULL){
            std::vector<int> add = {cheminNoeud->getX(),cheminNoeud->getY()};
            path.insert(path.begin(), add );
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
