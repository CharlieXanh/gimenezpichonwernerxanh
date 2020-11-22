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



void TilePlayer::update_pos(float dt,float speed)
{
	sf::Vector2f v1 = sprite.getPosition();
	position = sprite.getPosition();

	float dx = speed * dt;
	float dy = speed * dt;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
	{
		sprite.setPosition(v1.x, v1.y - dy);
		curAnimation = AnimationIndex::WalkingUp;
		animations[int(curAnimation)].Update(dt);
		animations[int(curAnimation)].Applytosprite(sprite);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
	{
		sprite.setPosition(v1.x-dx, v1.y);
		curAnimation = AnimationIndex::WalkingLeft;
		animations[int(curAnimation)].Update(dt);
		animations[int(curAnimation)].Applytosprite(sprite);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		sprite.setPosition(v1.x, v1.y + dy);
		curAnimation = AnimationIndex::WalkingDown;
		animations[int(curAnimation)].Update(dt);
		animations[int(curAnimation)].Applytosprite(sprite);

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		sprite.setPosition(v1.x+dx, v1.y);
		curAnimation = AnimationIndex::WalkingRight;
		animations[int(curAnimation)].Update(dt);
		animations[int(curAnimation)].Applytosprite(sprite);
	}
	else
	{
		curAnimation = AnimationIndex::WalkingDown;
		animations[int(curAnimation)].Update(0);
		animations[int(curAnimation)].Applytosprite(sprite);

	}
}

sf::Vector2f TilePlayer::getPosition()
{
	return position;
}

void TilePlayer::update_tile(float dt,float speed)
{
	{
		update_pos(dt, speed);
	}
}
