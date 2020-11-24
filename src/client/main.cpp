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

	}
  if(argc >= 2 && strcmp(argv[1],"Render") == 0 )
  {
    sf::Window fenetre(sf::VideoMode(800, 600), "My window");
    TilePlayer image(100.f,100.f);
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed){
                window.close();
            }
            else
            {
            //fenetre.clear();

            }
        }
    }
  }
    return 0;
}
