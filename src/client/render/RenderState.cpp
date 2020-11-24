#include "LayerMap.h"
#include "TileMenu.h"
#include "TilePlayer"

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace render;
RenderState:: RenderState(Position position){

	TilePlayer player((float)position.getX(),(float)position.getY());
	LayerMenu* menu = new LayerMenu(1);
	TileMap map;

	if (!map.load("res/tilemap_packed.png", sf::Vector2u(16,16))) {
        return -1;
    }
	
}

RenderState :: updatePosition(Position position){
	player.update_pos(position);
	menu->updatePosition(player.getPosition());
}