
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
	{
		this->map.load("res/tilemap_packed.png",sf::Vector2u(16,16));
		this->window = new sf::RenderWindow(sf::VideoMode(500,500), "One Upon A Wei",sf::Style::Close);
		this->view = new  sf::View(sf::Vector2f(0.f, 10.f), sf::Vector2f(360.f, 360.f));
		this->menu = new LayerMenu(1);
	}


void StateRender :: updatePosition(state::Position const& position){
	this->player.update_pos(position);
	this->menu->updatePosition(sf::Vector2f(position.x,position.y));
}

void StateRender :: update(){
	this->window->clear();
	this->window->draw(map);
	this->player.render_tile(*window);
	this->window->display();
}

void StateRender :: end(){
	this->window->close();
}

void StateRender::InitMap(){

}
