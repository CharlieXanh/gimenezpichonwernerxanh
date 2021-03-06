#include "ai.h"
#include "Noeud.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <map>
#include <cmath>
#include <algorithm>
#include <vector>


using namespace ai;
using namespace std;

Noeud :: Noeud (int x,int y,Noeud* parent,Noeud* end){
	this->position.push_back(x);
	this->position.push_back(y);
	this->parent = parent;

	//If the noeud is not the end
	if(end)
		this->computeScore(end);
	else
		this->score["end"] = 0;
}

void Noeud :: computeScore(Noeud* end){
	std::map<std::string,int> score;
	score["end"] = sqrt(pow(end->position[0]-this->position[0] ,2) + pow(end->position[1]-this->position[1],2));
	if(this->parent!=NULL)
		score["sum"] = score["end"] + this->parent->score["sum"];
	else
		score["sum"] = score["end"];
	this->score = score;
}


bool Noeud :: inside(std::vector<Noeud*> liste){
	for(auto x : liste){
		if(this->position[0] == x->getX() && this->position[1]== x->getY()){
			return true;
		}
	}
	return false;
}

std::vector<int> Noeud::getPosition(){
	return this->position;
}

int Noeud :: getX(){
	return this->position[0];
}

int Noeud :: getY(){
	return this->position[1];
}

std::map<std::string , int> Noeud :: getScore(){
	return this->score;
}

std::vector<Noeud*> Noeud :: voisins(std::vector<std::vector<int>> map,std::vector<Noeud*> listeFerme,std::vector<Noeud*> listeOuverte,Noeud* end){

	for(int i = -1;i<2;i++){
		for(int j = -1;j<2;j++){

			Noeud* newNoeud = new Noeud(this->position[0]+i,this->position[1]+j,this,end);

			if((abs(i+j)==1) && (unsigned int) newNoeud->getX()>=0 && (unsigned int)newNoeud->getX()<map[0].size() && newNoeud->getY()>=0
			&& (unsigned int)newNoeud->getY()<map.size() &&  map[newNoeud->getY()][newNoeud->getX()]!=1 && !newNoeud->inside(listeFerme)){

				if(newNoeud->inside(listeOuverte)){
					for(auto x : listeOuverte){
						if(x->getX()==newNoeud->getX() && x->getY()==newNoeud->getY() && x->score["sum"]>newNoeud->score["sum"]){
							x->score = newNoeud->score;
							x->parent = this;
						}
					}
				}
				else
					listeOuverte.push_back(newNoeud);
			}

		}
	}
	return listeOuverte;
}
