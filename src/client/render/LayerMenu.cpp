#include "LayerMenu.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace render;
LayerMenu :: LayerMenu(int scene){

	switch (scene){
		case 0:
			break;
		case 1:
			//Rappel des stats:
			this->tileMenu = loadElem("menuDeplacement.txt");
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;

	}
}


std::vector<TileMenu*> LayerMenu :: loadElem(std::string fileName){

	std::ifstream infile(fileName);
	std::vector<TileMenu*> TileVect;

	std::string image;
	std::string text;
	std::string font;
	std::string position_text;
	std::string sum = "";
	int position[2];

    do{
        getline(infile,image);
        getline(infile,text);
        getline(infile,font);
        getline(infile,position_text);
        for(char elem : position_text){
        	if (elem == ','){
                position[0] = std::stoi(sum);
                sum = "";
            }else{
                sum+=elem;
            }
        }
        position[1] = std::stoi(sum);
        sum = "";

        TileVect.push_back(new TileMenu(image,text,font,position));
        getline(infile,image);
    }while(!infile.eof());
    return TileVect;
}

void LayerMenu :: draw(sf::RenderTarget& target, sf::RenderStates states)
{
	for(TileMenu* tm : this->tileMenu){
		target.draw(tm->getSprite(), states);
		target.draw(tm->getText(), states);
	}
}


void LayerMenu :: updatePosition(sf::Vector2f offset){
	for(TileMenu* tMenu : this->tileMenu){
		tMenu->setOffset(offset);
	}
}
