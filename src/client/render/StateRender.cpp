
#include "StateRender.h"
#include <iostream>
#include <fstream>
#include <iomanip>
// #include <SFML/Graphics.hpp>
using namespace std;
using namespace render;
using namespace state;
StateRender:: StateRender (state::Position const& position)
	:player(position.getX(),position.getY())
	{}


void StateRender :: updatePosition(state::Position const& position){
	player.update_pos(position);
	//menu->updatePosition(player.getPosition());
}
