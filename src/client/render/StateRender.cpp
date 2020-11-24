
#include "StateRender.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace render;
StateRender:: StateRender(state::Position& position)
	:player(position.getX(),position.getY()){

	//player((float)position.getX(),(float)position.getY());
	//menu= new LayerMenu(1);

	map->load("res/tilemap_packed.png", sf::Vector2u(16,16));

}


void StateRender :: updatePosition(state::Position& position){
	player.update_pos(position);
	menu->updatePosition(player.getPosition());
}
