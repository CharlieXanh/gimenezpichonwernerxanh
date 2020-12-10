#include <iostream>
// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include "state.h"
#include <string.h>
#include "render.h"
#include "engine.h"
#include <chrono>
#include <unistd.h>

using namespace std;
using namespace state;
using namespace render;
int main(int argc,char* argv[])
{
    //Exemple exemple;
    //exemple.setX(53);

	if(argc >= 2 && strcmp(argv[1],"hello") == 0 )
		cout << "Ca fonctionne !" << endl;

	if(argc >= 2 && strcmp(argv[1],"State") == 0 ){
		cout << "State" << endl;
    Curseur curs{0,0};

	}
  if(argc >= 2 && strcmp(argv[1],"render") == 0 )
  {

        Position pos_ennemy(400,240,"Nord");
        Position pos(10,240,"Nord");

        StateRender state(pos);

    while (state.window->isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;



            while (state.window->pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
              {
                    state.end();
            }
            //state.updatePosition(pos);

          state.StateRender_combat(pos,pos_ennemy);

          }
    }
    return 0;
  }

  if(argc >= 2 && strcmp(argv[1],"engine") == 0 )
  {
    cout << "--- Engine du jeu ---" << endl;
    engine::Engine ngine;
    cout << "--- objet engine crée ---" << endl;

    ngine.getEtat().initJoueurs();
    cout <<"--- joueurs initialisée ---" << endl;

    Position pos1(10,240,"Nord");
    Position pos2(400,240,"Nord");
    ngine.getEtat().getJoueurs()[0]->setPosition(pos1);
    ngine.getEtat().getJoueurs()[1]->setPosition(pos2);

    StateRender state(pos1);
    state.StateRender_combat(pos1,pos2);

    cout << "--- joueur " << ngine.getEtat().getJoueurs()[0]->getNom() << " positioné ---" << endl;
    cout << "--- joueur " << ngine.getEtat().getJoueurs()[1]->getNom() << " positioné ---" << endl;

    int turns2go = 4;
    bool waitkey=true;
    while (state.window->isOpen() )
    {
      sf::Event event;
      //state.update();

      while( state.window->pollEvent(event))
      {
        if(waitkey){
          cout << "Appuyer sur une touche pour lancer un tour" << endl;
          waitkey = false;
        }
        if(event.type ==sf::Event::Closed)
          state.window->close();
        else if (event.type == sf::Event::KeyPressed)
        {

          cout << "Key pressed !" << endl;
          cout << endl
               << "#########################################" << endl;
          cout << "turn number: " << (5-turns2go) << endl;
          cout << "#########################################" << endl
               << endl;

          ngine.getEtat().getJoueurs()[0]->setDeplacements(3);
          ngine.getEtat().getJoueurs()[1]->setDeplacements(3);

          ngine.getEtat().getJoueurs()[0]->setStatut(SEL);

          int initialXP1 = ngine.getEtat().getJoueurs()[0]->getPosition().getX();
          int initialYP1 = ngine.getEtat().getJoueurs()[0]->getPosition().getY();

          int initialXP2 = ngine.getEtat().getJoueurs()[1]->getPosition().getX();
          int initialYP2 = ngine.getEtat().getJoueurs()[1]->getPosition().getY();

          int priority = 0;


          if (turns2go == 0)
          {
            sleep(2);
            cout << "No more turns left" << endl;
            cout << "ENGINE SHOW finished, closing window" << endl;
            state.window->close();
          }
          else if( (turns2go%2) == 1){

            cout << "Position inital Joueur 1 : " <<
             ngine.getEtat().getJoueurs()[0]->getPosition().getX() << " " <<
             ngine.getEtat().getJoueurs()[0]->getPosition().getY() << endl;

            Position pos11{initialXP1, 25+initialYP1};
            unique_ptr<engine::Commande> ptr_dc1(new engine::DeplacerCommande(*ngine.getEtat().getJoueurs()[0],pos11));
            ngine.ajoutCommande(move(ptr_dc1), priority++);

            Position pos12{initialXP1, 25+pos11.getY()};
            unique_ptr<engine::Commande> ptr_dc2(new engine::DeplacerCommande(*ngine.getEtat().getJoueurs()[0],pos12));
            ngine.ajoutCommande(move(ptr_dc2), priority++);

            Position pos13{50+initialXP1, pos12.getY()};
            unique_ptr<engine::Commande> ptr_dc3(new engine::DeplacerCommande(*ngine.getEtat().getJoueurs()[0],pos13));
            ngine.ajoutCommande(move(ptr_dc3), priority++);

            unique_ptr<engine::Commande> ptr_ttrc(new engine::TerminerTourCommande());
            ngine.ajoutCommande(move(ptr_ttrc),priority++);

            ngine.update();
            turns2go--;
          }
          else if (turns2go%2 == 0){
            cout << "Position inital Joueur 1 : " <<
             ngine.getEtat().getJoueurs()[0]->getPosition().getX() << " " <<
             ngine.getEtat().getJoueurs()[0]->getPosition().getY() << endl;

            Position pos11{initialXP1, initialYP1 - 25};
            unique_ptr<engine::Commande> ptr_dc1(new engine::DeplacerCommande(*ngine.getEtat().getJoueurs()[0],pos11));
            ngine.ajoutCommande(move(ptr_dc1), priority++);

            Position pos12{initialXP1,  pos11.getY() - 25};
            unique_ptr<engine::Commande> ptr_dc2(new engine::DeplacerCommande(*ngine.getEtat().getJoueurs()[0],pos12));
            ngine.ajoutCommande(move(ptr_dc2), priority++);

            Position pos13{initialXP1-50 ,  pos12.getY()};
            unique_ptr<engine::Commande> ptr_dc3(new engine::DeplacerCommande(*ngine.getEtat().getJoueurs()[0],pos13));
            ngine.ajoutCommande(move(ptr_dc3), priority++);


            unique_ptr<engine::Commande> ptr_ttrc(new engine::TerminerTourCommande());
            ngine.ajoutCommande(move(ptr_ttrc),priority++);

            ngine.update();
            turns2go--;
            waitkey = true;
          }

          Position nextP1 = ngine.getEtat().getJoueurs()[0]->getPosition();
          Position nextP2 = ngine.getEtat().getJoueurs()[1]->getPosition();


          state.updatePosition(nextP1);
          state.StateRender_combat(nextP1,nextP2);
          state.update();
        }
      }
    }
  }
}
