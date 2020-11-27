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

	}
  if(argc >= 2 && strcmp(argv[1],"render") == 0 )
  {
        sf::RenderWindow window(sf::VideoMode(500,500), "One Upon A Wei",sf::Style::Close);
        //sf::Event ev;
        TileMap map;
        map.load("res/tilemap_packed.png",sf::Vector2u(16,16));
        //sf::View view(sf::Vector2f(0.f, 10.f), sf::Vector2f(360.f, 360.f));
        Position pos(100,100,"Ouest");
        StateRender state(pos);
     auto tp = std::chrono::steady_clock::now();
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

              float dt;
            const auto new_tp = std::chrono::steady_clock::now();
            dt = std::chrono::duration<float>(new_tp - tp).count();
            tp = new_tp;

            while (window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
              {
                    window.close();
            }

            window.clear();
            window.draw(map);
            state.player.render_tile(window);
            window.display();


          }
  }
    return 0;
}
}
