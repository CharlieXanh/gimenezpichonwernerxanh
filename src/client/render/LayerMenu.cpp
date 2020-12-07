#include "../render.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace render;

LayerMenu :: LayerMenu(int scene){

	switch (scene){
		case 1:
			//Menu deplacement:
			this->tileMenu = loadElem("res/menuDeplacement.txt");
			break;
		case 2:
			this->tileMenu = loadElem("res/menuCombat.txt");
			break;
		case 3:
			this->tileMenu = loadElem("res/menuEchange.txt");
			break;
		default:
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

void LayerMenu :: draw(sf::RenderTarget& target, sf::RenderStates states) const
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

void LayerMenu :: updateCombat(int ennemieLife,int playerLife){
	for(TileMenu* tMenu : this->tileMenu){
		if(tMenu->text.find("vie :") != std::string::npos && tMenu->image=="res/button/r_button01.png"){
			this->tMenu.text = "vie : " + str(ennemieLife);
		}
		else if(tMenu->text.find("vie :") != std::string::npos && tMenu->image=="res/button/b_button01.png"){
			this->tMenu.text = "vie : " + str(playerLife);
		}
	}
}