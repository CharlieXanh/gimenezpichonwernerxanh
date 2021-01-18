#include <iostream>
// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>
#include <time.h>
void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include "state.h"
#include <string.h>
#include "render.h"
#include "engine.h"
#include "ai.h"
#include "client.h"
#include <chrono>
#include <unistd.h>

using namespace std;
using namespace state;
using namespace render;
using namespace ai;
using namespace client;
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
        cout << "--- Render ---" << endl;


        Etat state{"render"};
        state.initializeMapCell();
        state.initJoueurs();
        sf::RenderWindow window(sf::VideoMode(state.getMap()[0].size() * 32 + 256, state.getMap().size() * 32 + 32, 32), "Once upon a wei");
        StateLayer layer(state, window);
        layer.initSurfaces(state);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            // render
            layer.draw(window);
        }
        return 0;
  }

  if(argc >= 2 && strcmp(argv[1],"engine") == 0 )
  {

    cout << "--- Engine du jeu ---" << endl;
    engine::Engine ngine;
    cout << "--- objet engine crée ---" << endl;

    ngine.getEtat().initializeMapCell();
    cout << "--- state map initialized ---" << endl;

    ngine.getEtat().initJoueurs();
    cout <<"--- joueurs initialisée ---" << endl;

    //-----------------------------
    sf::RenderWindow window(sf::VideoMode(ngine.getEtat().getMap()[0].size() * 32 + 256, ngine.getEtat().getMap().size() * 32 + 32, 32), "Once upon a wei");
    //sf::RenderWindow window(sf::VideoMode(ngine.getEtat().getMap()[0].size() * 32, ngine.getEtat().getMap().size() * 32 + 32, 32), "map");
    StateLayer layer(ngine.getEtat(), window);

    layer.initSurfaces(ngine.getEtat());
    cout << "--- fenêtre du jeu initialisée ---" << endl;

    StateLayer stateLayer(ngine.getEtat(), window);
    cout << "--- state layer initialisée avec l'état et la fenêtre ---" << endl;

    stateLayer.initSurfaces(ngine.getEtat());
    cout << "--- Surfaces du state layer initialisées ---" << endl;

    // Registering observer
    StateLayer *ptr_stateLayer = &stateLayer;
    ngine.getEtat().registerObserver(ptr_stateLayer);



    cout << "--- joueur " << ngine.getEtat().getJoueurs()[0]->getNom() << " positioné ---" << endl;
    cout << "--- joueur " << ngine.getEtat().getJoueurs()[1]->getNom() << " positioné ---" << endl;

    int turns2go = 4;
    bool waitkey=true;
    bool once = true;
    while (window.isOpen() )
    {
      sf::Event event;
      //state.update();
      if (once)
      {
          stateLayer.draw(window);
          once = false;
      }
      while( window.pollEvent(event))
      {
        if(waitkey){

          cout << "Appuyer sur une touche pour lancer un tour" << endl;
          waitkey = false;
        }
        if(event.type ==sf::Event::Closed)
          window.close();
        else if (event.type == sf::Event::KeyPressed)
        {

          cout << "Key pressed !" << endl;
          cout << endl
               << "|||||||||||||||||||||||||||||||||||||||||" << endl;
          cout << "turn number: " << (5-turns2go) << endl;
          cout << "|||||||||||||||||||||||||||||||||||||||||" << endl
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
            window.close();
          }
          else if( (turns2go%2) == 1){

            cout << "Position inital Joueur 1 : " <<
             ngine.getEtat().getJoueurs()[0]->getPosition().getX() << " " <<
             ngine.getEtat().getJoueurs()[0]->getPosition().getY() << endl;

            Position pos11{initialXP1, ++initialYP1};
            //cout << "trying to move to : "<< pos11.getX() <<" "<< pos11.getY() <<endl;
            unique_ptr<engine::Commande> ptr_dc1(new engine::DeplacerCommande(*ngine.getEtat().getJoueurs()[0],pos11));
            ngine.ajoutCommande(move(ptr_dc1), priority++);

            Position pos12{initialXP1, ++initialYP1};
            unique_ptr<engine::Commande> ptr_dc2(new engine::DeplacerCommande(*ngine.getEtat().getJoueurs()[0],pos12));
            ngine.ajoutCommande(move(ptr_dc2), priority++);

            unique_ptr<engine::Commande> ptr_atqc1(new engine::AttaquerCommande(*ngine.getEtat().getJoueurs()[0],
                                                                              *ngine.getEtat().getJoueurs()[1]));
            ngine.ajoutCommande(move(ptr_atqc1),priority++);

            Position pos13{++initialXP1, initialYP1};
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

            Position pos11{initialXP1, --initialYP1};
            unique_ptr<engine::Commande> ptr_dc1(new engine::DeplacerCommande(*ngine.getEtat().getJoueurs()[0],pos11));
            ngine.ajoutCommande(move(ptr_dc1), priority++);

            Position pos12{initialXP1,  --initialYP1};
            unique_ptr<engine::Commande> ptr_dc2(new engine::DeplacerCommande(*ngine.getEtat().getJoueurs()[0],pos12));
            ngine.ajoutCommande(move(ptr_dc2), priority++);

            unique_ptr<engine::Commande> ptr_atqc1(new engine::AttaquerCommande(*ngine.getEtat().getJoueurs()[1],
                                                                               *ngine.getEtat().getJoueurs()[0]));
            ngine.ajoutCommande(move(ptr_atqc1),priority++);

            Position pos13{--initialXP1 ,  initialYP1};
            unique_ptr<engine::Commande> ptr_dc3(new engine::DeplacerCommande(*ngine.getEtat().getJoueurs()[0],pos13));
            ngine.ajoutCommande(move(ptr_dc3), priority++);


            unique_ptr<engine::Commande> ptr_ttrc(new engine::TerminerTourCommande());
            ngine.ajoutCommande(move(ptr_ttrc),priority++);

            ngine.update();
            turns2go--;
            waitkey = true;
          }
        }
      }
    }
  }//end engine

  if(argc >= 2 && strcmp(argv[1],"random_ai") == 0 )
  {
    cout << "--- random_ai ---" << endl;
    engine::Engine ngine("random_ai");
    cout << "--- objet engine créé ---" << endl;

    ngine.getEtat().initializeMapCell();
    cout << "--- state map initialized ---" << endl;

    ngine.getEtat().initJoueurs();
    cout <<"--- joueurs & ennemis initialisés ---" << endl;

    //-----------------------------
    sf::RenderWindow window(sf::VideoMode(ngine.getEtat().getMap()[0].size() * 32 + 256, ngine.getEtat().getMap().size() * 32 + 32, 32), "Once upon a wei");
    //sf::RenderWindow window(sf::VideoMode(ngine.getEtat().getMap()[0].size() * 32, ngine.getEtat().getMap().size() * 32 + 32, 32), "map");
    StateLayer layer(ngine.getEtat(), window);

    layer.initSurfaces(ngine.getEtat());
    cout << "--- fenêtre du jeu initialisée ---" << endl;

    StateLayer stateLayer(ngine.getEtat(), window);
    cout << "--- state layer initialisée avec l'état et la fenêtre ---" << endl;

    stateLayer.initSurfaces(ngine.getEtat());
    cout << "--- Surfaces du state layer initialisées ---" << endl;

    // Registering observer
    StateLayer *ptr_stateLayer = &stateLayer;
    ngine.getEtat().registerObserver(ptr_stateLayer);

    KeyListener kl{ngine};
    RandomAI rai;
    rai.setNumeroEnnemi(1);

    cout << "--- joueur " << ngine.getEtat().getJoueurs()[0]->getNom() << " positioné ---" << endl;
    cout << "--- joueur " << ngine.getEtat().getJoueurs()[1]->getNom() << " positioné ---" << endl;

    int turns2go = 4;
    bool waitkey=true;
    bool once = true;
    while (window.isOpen() )
    {
      sf::Event event;
      //state.update();
      if (once)
      {
          stateLayer.draw(window);
          once = false;
      }
      while( window.pollEvent(event))
      {
        if(waitkey){

          cout << "Selectionnez une commande" << endl;
          waitkey = false;
        }
        if(event.type ==sf::Event::Closed)
          window.close();
        else if(ngine.getEtat().getJouant() == rai.getNumeroEnnemi()){
     cout<< "RAI turn !\n|||||||||||||||||||||||||||||||||||||||||" << endl;
     cout << "turn number: " << ngine.getEtat().getTour() << endl;
     cout << "|||||||||||||||||||||||||||||||||||||||||" << endl
          << endl;
            rai.run(ngine);
        }

        else if (event.type == sf::Event::KeyPressed || event.type ==  sf::Event::MouseButtonPressed)
        {
          cout << "Key pressed !" << endl;
          cout << endl
               << "|||||||||||||||||||||||||||||||||||||||||" << endl;
          cout << "turn number: " << ngine.getEtat().getTour() << endl;
          cout << "|||||||||||||||||||||||||||||||||||||||||" << endl
               << endl;



            if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
                kl.triggerAction(ngine, MOVE,event.mouseButton.x/32,event.mouseButton.y/32);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                kl.triggerAction(ngine, ATTAQUER,event.mouseButton.x/32,event.mouseButton.y/32);
            else if (event.mouseButton.button == sf::Mouse::Right)
                kl.triggerAction(ngine, SELECT,event.mouseButton.x/32,event.mouseButton.y/32);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)){
             unique_ptr<engine::Commande> finTurnCmd(new engine::TerminerTourCommande());
             ngine.ajoutCommande(move(finTurnCmd));
             ngine.update();
            }
            waitkey = true;
        }
      }
    }


  }//end random_ai */

  if(argc >= 2 && strcmp(argv[1],"heuristic_ai") == 0 )
  {
    cout << "--- Heuristic_ai ---" << endl;
    engine::Engine ngine("random_ai");
    cout << "--- objet engine créé ---" << endl;

    ngine.getEtat().initializeMapCell();
    cout << "--- state map initialized ---" << endl;

    ngine.getEtat().initJoueurs();
    ngine.getEtat().getJoueurs()[0]->setStatut(SEL);
    cout <<"--- joueurs & ennemis initialisés ---" << endl;

    //-----------------------------
    sf::RenderWindow window(sf::VideoMode(ngine.getEtat().getMap()[0].size() * 32 + 256, ngine.getEtat().getMap().size() * 32 + 32, 32), "Once upon a wei");
    //sf::RenderWindow window(sf::VideoMode(ngine.getEtat().getMap()[0].size() * 32, ngine.getEtat().getMap().size() * 32 + 32, 32), "map");
    StateLayer layer(ngine.getEtat(), window);

    layer.initSurfaces(ngine.getEtat());
    cout << "--- fenêtre du jeu initialisée ---" << endl;

    StateLayer stateLayer(ngine.getEtat(), window);
    cout << "--- state layer initialisée avec l'état et la fenêtre ---" << endl;

    stateLayer.initSurfaces(ngine.getEtat());
    cout << "--- Surfaces du state layer initialisées ---" << endl;

    // Registering observer
    StateLayer *ptr_stateLayer = &stateLayer;
    ngine.getEtat().registerObserver(ptr_stateLayer);

    KeyListener kl{ngine};
    HeuristicAI hai;

    hai.setNumeroEnnemi(1);

    cout << "--- joueur " << ngine.getEtat().getJoueurs()[0]->getNom() << " positioné ---" << endl;
    cout << "--- joueur " << ngine.getEtat().getJoueurs()[1]->getNom() << " positioné ---" << endl;

    int turns2go = 4;
    bool waitkey=true;
    bool once = true;
    while (window.isOpen() )
    {
      sf::Event event;
      //state.update();
      if (once)
      {
          stateLayer.draw(window);
          once = false;
      }
      while( window.pollEvent(event))
      {
        if(waitkey){

          cout << "Selectionnez une commande\n"  << endl;
          waitkey = false;
        }
        if(event.type ==sf::Event::Closed)
          window.close();
        else if(ngine.getEtat().getJouant() == hai.getNumeroEnnemi()){
     cout<< "AI turn !\n|||||||||||||||||||||||||||||||||||||||||" << endl;
     cout << "turn number: " << ngine.getEtat().getTour() << endl;
     cout << "|||||||||||||||||||||||||||||||||||||||||" << endl
          << endl;
            hai.run(ngine);
        }

        else if (event.type == sf::Event::KeyPressed || event.type ==  sf::Event::MouseButtonPressed)
        {
          cout << "Key pressed !" << endl;
          cout << endl
               << "|||||||||||||||||||||||||||||||||||||||||" << endl;
          cout << "turn number: " << ngine.getEtat().getTour() << endl;
          cout << "|||||||||||||||||||||||||||||||||||||||||" << endl
               << endl;



            if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
                kl.triggerAction(ngine, MOVE,event.mouseButton.x/32,event.mouseButton.y/32);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                kl.triggerAction(ngine, ATTAQUER,event.mouseButton.x/32,event.mouseButton.y/32);
            else if (event.mouseButton.button == sf::Mouse::Right)
                kl.triggerAction(ngine, SELECT,event.mouseButton.x/32,event.mouseButton.y/32);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)){
             unique_ptr<engine::Commande> finTurnCmd(new engine::TerminerTourCommande());
             ngine.ajoutCommande(move(finTurnCmd));
             ngine.update();
            }
            waitkey = true;
        }
      }
    }


  }//end heuristic_ai
	if(argc >= 2 && strcmp(argv[1],"thread") == 0 ){

		cout << "=== Thread client ==="<<endl;
		engine::Engine ngine("random_ai");
		sf::RenderWindow window(sf::VideoMode(ngine.getEtat().getMap()[0].size() * 32 + 256, ngine.getEtat().getMap().size() * 32 + 32, 32), "Once upon a wei");

		Client client(&window,&ngine);
		cout << "--- Client chargé ---"<<endl;
		client.run();
		while(window.isOpen()){}
		cout<<"=== End thread ==="<<endl;
	}


}
