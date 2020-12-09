#include <iostream>
// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include <state.h>
#include <string.h>
#include <render.h>
#include <chrono>
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

        Position pos_ennemy(100,160,"Nord");
        Position pos(30,160,"Nord");




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
            state.updatePosition(pos);
            state.StateRender_combat(pos,pos_ennemy);
          cout <<   state.map.mapSize().x << " " << state.map.mapSize().y << endl;

            state.update(1);

          }
  }
    return 0;
}
}
