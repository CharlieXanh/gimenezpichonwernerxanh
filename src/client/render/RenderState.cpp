#include "LayerMap.h"
#include "TileMenu.h"
#include "TilePlayer"

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace render;
RenderState:: RenderState(Position position){

	TilePlayer player;
	LayerMenu* menu = new LayerMenu(1);
	TileMap map;

	if (!map.load("res/tilemap_packed.png", sf::Vector2u(16,16))) {
        return -1;
    }
	
}

RenderState :: updatePosition(){

}