#include "client.h"
#include "render.h"
#include "engine.h"
#include "ai.h"
#include "state.h"

using namespace std;
using namespace std::chrono;

bool threadBool = true;

void threadEngine(Engine *ptr){
  while(threadBool){
    usleep(1000);
    ptr->update();
  }
}

client::client(std::string type) : this->ngine(type) 
{

	this->ngine.getEtat().initializeMapCell("res/Map/arene.csv");
  cout << "--- state map initialized ---" << endl;

  this->ngine.getEtat().initJoueurs();
  cout <<"--- joueurs initialisée ---" << endl;

  Position pos1(10,15,"Nord");
  Position pos2(10,4,"Nord");
  this->positions = {pos1,pos2};
  this->ngine.getEtat().getJoueurs()[0]->setPosition(pos1);
  this->ngine.getEtat().getEnnemis()[0]->setPosition(pos2);
    
  this->rai1.setNumeroEnnemi(0);

}

void client::run() {

	StateRender stateRender(positions[0]);
  stateRender.StateRender_combat(positions[0],positions[1]);

  cout << "--- joueur " << this->ngine.getEtat().getJoueurs()[0]->getNom() << " positioné ---" << endl;
  cout << "--- joueur " << this->ngine.getEtat().getEnnemis()[0]->getNom() << " positioné ---" << endl;

	while (stateRender.window->isOpen() )
    {
      std::thread th(threadEngine, &ngine);
      sf::Event event;

      while( stateRender.window->pollEvent(event))
      {
        if(waitkey){
          cout << "Appuyer sur une touche pour lancer un tour" << endl;
          waitkey = false;
        }
        if(event.type ==sf::Event::Closed)
          stateRender.window->close();
        else if (event.type == sf::Event::KeyPressed)
        {
          
          rai1.run(this->ngine);
          this->ngine.update();

          waitkey = true;


          Position nextP1 = this->ngine.getEtat().getJoueurs()[0]->getPosition();
          Position nextP2 = this->ngine.getEtat().getEnnemis()[0]->getPosition();


          stateRender.updatePosition(nextP1);
          stateRender.StateRender_combat(nextP1,nextP2);
          stateRender.update();
        }
      }
    }
    threadBool = false;
    th.join();
}
client::~client() {
}