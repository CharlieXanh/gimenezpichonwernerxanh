
#include "StateRender.h"
#include <iostream>
#include <fstream>
#include <iomanip>
// #include <SFML/Graphics.hpp>
using namespace std;
using namespace render;
using namespace state;


StateRender:: StateRender (state::Position& position)
	:player(position.getX(),position.getY())
	{
		this->map.load("res/tilemap_packed.png",sf::Vector2u(16,16));
		this->window = new sf::RenderWindow(sf::VideoMode(720,720), "One Upon A Wei",sf::Style::Close);
		this->view = new  sf::View(sf::Vector2f(0.f, 10.f), sf::Vector2f(360.f, 360.f));
		this->menu = new LayerMenu(1);
		this->menuCombat=new LayerMenu(2);
	}


void StateRender :: updatePosition(state::Position & position){
	this->player.update_pos(position);
	this->menu->updatePosition(sf::Vector2f(position.getX(),position.getY()));
	this->menuCombat->updatePosition(sf::Vector2f(position.getX(),position.getY()));
}

void StateRender :: update(){
	this->window->clear();
	view->setCenter(player.getPosition().x,player.getPosition().y);
	window->setView(*view);

	this->window->draw(map);
	//this->window->draw(*menu);
	this->window->draw(*menuCombat);
	this->player.render_tile(*window);
	this->ennemy.render_tile(*window);
	this->window->display();

}

void StateRender :: end(){
	this->window->close();
}

void StateRender::InitMap(){

}

void StateRender::StateRender_combat (state::Position& position_j, state::Position & position_ad)
{
	this->player.Orientation("EST");
	this->ennemy.Orientation("OUEST");
	this->player.update_pos(position_j);
	this->ennemy.update_pos(position_ad);
	this->menuCombat->updateCombat(20,20);

}
