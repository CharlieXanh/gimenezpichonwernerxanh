#include "TilePlayer.h"
#include <iostream>
using namespace std;
using namespace render;


TilePlayer::TilePlayer(int x, int y):position(x,y)
{
	this->animations[int(AnimationIndex::WalkingUp)] = Animation(64, 0, 64, 64);
	this->animations[int(AnimationIndex::WalkingDown)] = Animation(64, 128, 64, 64);
	this->animations[int(AnimationIndex::WalkingLeft)] = Animation(64, 64, 64, 64);
	this->animations[int(AnimationIndex::WalkingRight)] = Animation(64, 192, 64, 64);

	initTexture();
	initSprite();
	cout << "ok" << endl;
}

TilePlayer::~TilePlayer(){ cout << "joueur effacee" << endl;}

void TilePlayer::initTexture()
{
	// Load the texture from the file
	if (!texture.loadFromFile("res/prof.png"))
	{
		cout << "Error::player::initTexture could not load texture" << endl;
		exit(1);
	}
}

void TilePlayer::initSprite()
{
	// Set the texture to the Sprite
	sprite.setTexture(texture);
	sprite.setTextureRect({64,64, 64, 64});
	sprite.scale(0.8,0.8);
	sprite.setPosition(position.x, position.y);
}

void TilePlayer::render_tile(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}


void TilePlayer::update_pos (state::Position& position)
{
	this->position = sf::Vector2i(position.getX(),position.getY());
	this->sprite.setPosition(position.getX(),position.getY());
}

sf::Vector2i TilePlayer::getPosition()
{
	return position;
}

void TilePlayer:: Orientation (std::string orientation){
	if (orientation=="NORD"){
		curAnimation=AnimationIndex::WalkingUp;
		cout << "orientation nord" << endl;
	}
	else if (orientation=="OUEST"){
		curAnimation=AnimationIndex::WalkingLeft;
	}
else if(orientation=="EST"){
	curAnimation=AnimationIndex::WalkingRight;
}
else{
	curAnimation=AnimationIndex::WalkingDown;
}
animations[int(curAnimation)].Applytosprite(sprite);
}
