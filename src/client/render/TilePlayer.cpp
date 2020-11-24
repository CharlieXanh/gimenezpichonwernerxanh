#include "TilePlayer.h"
#include <iostream>
using namespace std;
using namespace render;

TilePlayer::TilePlayer(float x, float y):position(x,y)
{
	this->animations[int(AnimationIndex::WalkingUp)] = Animation(64, 0, 64, 64);
	this->animations[int(AnimationIndex::WalkingDown)] = Animation(64, 128, 64, 64);
	this->animations[int(AnimationIndex::WalkingLeft)] = Animation(64, 64, 64, 64);
	this->animations[int(AnimationIndex::WalkingRight)] = Animation(64, 192, 64, 64);
	
	this->initTexture();
	this->initSprite();
}

TilePlayer::~TilePlayer(){}

void TilePlayer::initTexture()
{
	// Load the texture from the file
	if (!texture.loadFromFile("prof.png"))
	{
		cout << "Error::player::initTexture could not load texture" << endl;
		exit(1);
	}
}

void TilePlayer::initSprite()
{
	// Set the texture to the Sprite 
	sprite.setTextureRect({64,64, 64, 64});
	sprite.scale(0.3,0.3);
	sprite.setPosition(position.x, position.y);
}

void TilePlayer::render_tile(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}


void TilePlayer::update_pos(int x, int y)
{
	this->position = sf::Vector2f(x,y);
	this->sprite.setPosition(x,y);
}

sf::Vector2f TilePlayer::getPosition()
{
	return position;
}
