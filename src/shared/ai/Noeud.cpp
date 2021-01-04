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
	this->x = x;
	this->y = y;
	this->parent = parent;
	//If the noeud is not the end
	if(end)
		this->computeScore(end);
	else
		this->score["end"] = 0;
}

void Noeud :: computeScore(Noeud* end){
	std::map<std::string,int> score;
	score["end"] = sqrt(pow(end->x-this->x ,2) + pow(end->y-this->y,2));
	if(this->parent!=NULL)
		score["sum"] = score["end"] + this->parent->score["sum"];
	else
		score["sum"] = score["end"];
	this->score = score;
}


bool Noeud :: inside(std::vector<Noeud*> liste){
	for(auto x : liste){
		if(this->x == x->getX() && this->y== x->getY()){
			return true;
		}
	}
	return false;
}

std::vector<int> Noeud::getPosition(){
	return this->position;
}

int Noeud :: getX(){
	return this->x;
}

int Noeud :: getY(){
	return this->y;
}

std::map<std::string , int> Noeud :: getScore(){
	return this->score;
}

std::vector<Noeud*> Noeud :: voisins(std::vector<std::vector<int>> map,std::vector<Noeud*> listeFerme,std::vector<Noeud*> listeOuverte,Noeud* end){

	for(int i = -1;i<2;i++){
		for(int j = -1;j<2;j++){

			Noeud* newNoeud = new Noeud(this->x+i,this->y+j,this,end);

			if((i!=0 || j!=0) && newNoeud->getX()>=0 && newNoeud->getX()<map.size() && newNoeud->getY()>=0 \
			&& newNoeud->getY()<map[0].size() &&  map[newNoeud->getX()][newNoeud->getY()]!=1 && !newNoeud->inside(listeFerme)){

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
