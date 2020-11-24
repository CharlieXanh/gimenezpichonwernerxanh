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
        sf::RenderWindow window(sf::VideoMode(720,720), "One Upon A Wei",sf::Style::Close);

        sf::Event ev;

        window.setVerticalSyncEnabled(true);
        sf::View view(sf::Vector2f(0.f, 10.f), sf::Vector2f(360.f, 360.f));

        auto tp = std::chrono::steady_clock::now();
        float dt;
        sf::Event event;

        Position position(100,100,"Ouest");
        StateRender state(position);

        while (window.isOpen())
        {
            const auto new_tp = std::chrono::steady_clock::now();
            dt = std::chrono::duration<float>(new_tp - tp).count();
            tp = new_tp;

            while (window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                    window.close();
            }

            state.updatePosition()

            window.clear();
            view.setCenter(player.getPosition());
            window.setView(view);

            window.draw(map);
            window.draw(*menu);

            player.render_tile(window);

            window.display();
  }
    return 0;
}
