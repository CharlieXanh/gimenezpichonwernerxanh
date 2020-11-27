#include "Animation.h"
using namespace render;

Animation :: Animation(int x, int y, int width, int height)
{

	texture.loadFromFile("res/prof.png");
	for (int i = 0; i < nFrames; i++)
	{
		frames[i] = { x + i * width,y,width,height };
	}
}

void Animation :: Applytosprite(sf::Sprite& s)
{
	s.setTexture(texture);
	s.setTextureRect(frames[iFrame]);
}

void Animation :: Applytosprite_arret(sf::Sprite& s,int numero)
{
	s.setTexture(texture);
	s.setTextureRect(frames[numero]);
}

void Animation :: Update(float dt)
{
	time += dt;
	while (time >= holdTime)
	{
		time =time- holdTime;
		Advance();
	}
}

void Animation :: Advance()
{
	if (++iFrame >= nFrames)
	{
		iFrame = 0;
	}
}
