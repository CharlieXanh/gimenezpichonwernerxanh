#include <iostream>
#include <unistd.h>
#include <mutex>
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

std::mutex ngine_mutex;
bool engineUpdate = false;
bool threadBool = true;

Client::Client(sf::RenderWindow* window,Engine* ngine)
{
  this->window = window;
  this->ngine = ngine;

  this->ngine->getEtat().initializeMapCell("res/Map/arene.csv");
  cout << "--- state map initialized ---" << endl;

  this->ngine->getEtat().initJoueurs();
  cout <<"--- joueurs initialisée ---" << endl;
}

void threadEngine(Engine *ptr){
	while(threadBool)
	{
		usleep(1000);
		if(engineUpdate){
      {
      ngine_mutex.lock();
			ptr->update();
      ngine_mutex.unlock();
      }
			engineUpdate = false;
		}
	}
}
void Client::run() {


  // StateLayer layer(this->ngine->getEtat(),*(this->window));
  //
  //
	// layer.initSurfaces(this->ngine->getEtat());
	// cout<<"=== fenetre du jeu initialisée ==="<<endl;

	StateLayer stateLayer(this->ngine->getEtat(),*(this->window));
	cout<<"=== state layer initialisée avec l'état et la fenetre"<<endl;

	stateLayer.initSurfaces(this->ngine->getEtat());
	cout<<"== Surfaces du state layer initialisées ==="<<endl;

	StateLayer *ptr_stateLayer = &stateLayer;
	this->ngine->getEtat().registerObserver(ptr_stateLayer);

	RandomAI ai;
	ai.setNumeroEnnemi(0);

  HeuristicAI hai;
  hai.setNumeroEnnemi(1);


  //cout << "--- joueur " << this->ngine->getEtat().getJoueurs()[0]->getNom() << " positioné ---" << endl;
 	//cout << "--- joueur " << this->ngine->getEtat().getEnnemis()[0]->getNom() << " positioné ---" << endl;
	std::thread th(threadEngine, this->ngine);
  bool once = true;
	while (this->window->isOpen())
  {
    sf::Event event;
	  // usleep(1000);
	  if (once)
    {
      stateLayer.draw(*window);
      once = false;
    }

    while(this->window->pollEvent(event))
    {
        if(event.type ==sf::Event::Closed)
          this->window->close();

        cout << "|||||||||||||||||||||||||||||||||||||||||" << endl;
        cout << "turn number: " << this->ngine->getEtat().getTour() << endl;
        cout << "|||||||||||||||||||||||||||||||||||||||||" << endl
               << endl;


	        if(this->ngine->getEtat().getJouant() == ai.getNumeroEnnemi()){
            ngine_mutex.lock();
            ai.run(*ngine);
            ngine_mutex.unlock();
          }
          else if( this->ngine->getEtat().getJouant() == hai.getNumeroEnnemi()){
            ngine_mutex.lock();
            hai.run(*ngine);
            ngine_mutex.unlock();
          }

          engineUpdate = true;

    }
    threadBool = false;
    if ( th.joinable())
      th.join();
    // if(this->window->isOpen()){
    //  	this->window->close();
    // }

  }
}

Client::~Client() {
}
