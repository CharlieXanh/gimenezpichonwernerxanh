#include "../render.h"
using namespace render;
#include <iostream>
#define IMG_NUMBER_POSITION 9
#define TEXT_OFFSET 5

TileMenu :: TileMenu(std::string images,std::string text_str,std::string fontStr,int* position)
{

    this->position[0] = position[0];
    this->position[1] = position[1];

    this->imgFile = images;

    if (!this->font.loadFromFile(fontStr))
    {
        std::cout << "Error loading font menu"<<std::endl;
        exit(-1);
    }

    if (!this->texture.loadFromFile(this->imgFile))
    {
        std::cout << "Error loading image menu\n"<<std::endl;
        exit(-1);
    }

    this->sprite.setTexture(this->texture);

    this->sprite.setPosition(sf::Vector2f(this->position[0],this->position[1]));

    this->text.setFont(font);
    this->text.setString(text_str);
    this->text.setCharacterSize(24);
    this->text.setFillColor(sf::Color::White);

    this->text.setPosition(sf::Vector2f(this->position[0]+TEXT_OFFSET,this->position[1]+TEXT_OFFSET));

}

sf::Sprite TileMenu :: getSprite(){
    return this->sprite;
}
sf::Text TileMenu :: getText(){
    return this->text;
}

void TileMenu :: changeSprite(){
    int currentNumber = (int)this->imgFile[IMG_NUMBER_POSITION]-'0';

    if(currentNumber&1){
        currentNumber+=-1;
    }
    else{
        currentNumber+=1;
    }
    this->imgFile[IMG_NUMBER_POSITION] =  '0' + currentNumber;
    if (!this->texture.loadFromFile(this->imgFile))
    {
        std::cout << "Error loading image menu\n";
        exit(-1);
    }
    this->sprite.setTexture(this->texture);;
}

sf::Vector2f TileMenu :: getOffset(){
    return this->sprite.getPosition();
}

void TileMenu :: setOffset(sf::Vector2f offset){
    this->sprite.setPosition(sf::Vector2f(this->position[0]+offset.x,this->position[1]+offset.y));
    this->text.setPosition(sf::Vector2f(this->position[0]+offset.x+TEXT_OFFSET,this->position[1]+offset.y+TEXT_OFFSET));
}
