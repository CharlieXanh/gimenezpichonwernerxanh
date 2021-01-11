#include <iostream>
#include <unistd.h>
#include "Client.h"
#include "render.h"
#include "engine.h"
#include "ai.h"
#include "state.h"

using namespace std;
using namespace std::chrono;
using namespace state;
using namespace engine;
using namespace ai;
using namespace render;
using namespace client;

Client::Client(Engine* ngine)
{

  this->ngine = ngine;

  this->ngine->getEtat().initializeMapCell("res/Map/arene.csv");
  cout << "--- state map initialized ---" << endl;

  this->ngine->getEtat().initJoueurs();
  cout <<"--- joueurs initialisée ---" << endl;
	this->threadBool = true;
  Position pos1(10,15,"Nord");
  Position pos2(10,4,"Nord");
  this->positions = {pos1,pos2};
  this->ngine->getEtat().getJoueurs()[0]->setPosition(pos1);
  this->ngine->getEtat().getEnnemis()[0]->setPosition(pos2);
}

void threadEngine(Engine *ptr,bool threadBool){
	while(threadBool)
	{
		usleep(1000);
		ptr->update();
	}
}
void Client::run() {

	sf::RenderWindow window(sf::VideoMode(ngine->getEtat().getMap()[0].size() * 32 + 256, ngine->getEtat().getMap().size() * 32 + 32, 32), "Once upon a wei");
    	//sf::RenderWindow window(sf::VideoMode(ngine.getEtat().getMap()[0].size() * 32, ngine.getEtat().getMap().size() * 32 + 32, 32), "map");
    	StateLayer layer(this->ngine->getEtat(), window);


	layer.initSurfaces(this->ngine->getEtat());
	cout<<"=== fenetre du jeu initialisée ==="<<endl;

	StateLayer stateLayer(this->ngine->getEtat(),window);
	cout<<"=== state layer initialisée avec l'état et la fenetre"<<endl;

	stateLayer.initSurfaces(this->ngine->getEtat());
	cout<<"== Surfaces du state layer initialisées ==="<<endl;

	StateLayer *ptr_stateLayer = &stateLayer;
	this->ngine->getEtat().registerObserver(ptr_stateLayer);

	RandomAI rai;

	rai.setNumeroEnnemi(1);


  	cout << "--- joueur " << this->ngine->getEtat().getJoueurs()[0]->getNom() << " positioné ---" << endl;
 	cout << "--- joueur " << this->ngine->getEtat().getEnnemis()[0]->getNom() << " positioné ---" << endl;
	std::thread th(threadEngine, this->ngine,this->threadBool);
	int turns2go = 4;
    	bool waitkey=true;
    	bool once = true;
	while (window.isOpen() && threadBool)
    {
      sf::Event event;

	if (once)
      	{
          stateLayer.draw(window);
          once = false;
      	}

      while(window.pollEvent(event))
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
          cout << "turn number: " << this->ngine->getEtat().getTour() << endl;
          cout << "|||||||||||||||||||||||||||||||||||||||||" << endl
               << endl;

          rai.run(*ngine);
          //ngine.update();
          waitkey = true;
        }
      }
    }
    threadBool = false;
    th.join();
}
Client::~Client() {
}
