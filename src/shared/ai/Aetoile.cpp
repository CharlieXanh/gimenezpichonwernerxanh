#include "../ai.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

Aetoile :: Aetoile(std::vector<std::vector<int>> mapp,sf::Vector2u start,sf::Vector2u end){

	this->endNoeud = new Noeud(end.x,end.y,NULL,NULL);
	this->startNoeud = new Noeud(start.x,start.y,NULL,endNoeud);

	this->mapp = mapp;

	this->listeOuverte.push_back(startNoeud);
}




void Aetoile :: computePath(bool print = false){

	int i,index;
	Noeud* currentNoeud;
	do{
		//Look for the best noeud in  listOuverte
		i = 0;
		index=0;
		currentNoeud = this->listeOuverte[0];

		for(auto x : this->listeOuverte){
			if(x->getScore()["end"]<currentNoeud->getScore()["end"]){
				currentNoeud = x;
				index = i;
			}
			i++;
		}

		this->listeFerme.push_back(currentNoeud);

		this->listeOuverte = currentNoeud->voisins(this->mapp,this->listeFerme,this->listeOuverte,this->endNoeud);
		this->listeOuverte.erase(this->listeOuverte.begin()+index);

	}while(this->listeOuverte.size()>0 && !this->endNoeud->inside(this->listeOuverte));

	if(print){
		std::cout<<"Start : "<<this->startNoeud->getX()<< " " << this->startNoeud->getY()<<std::endl;
		std::cout<<"End : "<<this->endNoeud->getX()<< " " << this->endNoeud->getY()<<std::endl;
		std::cout << "Path :" << std::endl;
		for(auto x : this->listeFerme){
			std::cout << "\t"<<x->getX()<< " " << x->getY()<< std::endl;
		}

		//Print map
		bool pass;
		for(int  i = 0;i<this->mapp.size();i++){
			for(int j=0;j<this->mapp[i].size();j++){
				pass = true;
				for(auto x : this->listeFerme){
					if(x->getX()==i && x->getY()==j){
						std::cout<< "\033[1;35m" << this->mapp[i][j] << "\033[0m" <<" ";
						pass = false;
					}
				}
				if(pass){
					if((i==this->startNoeud->getX() && j==this->startNoeud->getY())  || (i==this->endNoeud->getX() && j==this->endNoeud->getY()))
						std::cout<< "\033[1;35m" << this->mapp[i][j] << "\033[0m" <<" ";
					else if (this->mapp[i][j]==1)
						std::cout<< "\033[1;31m" << this->mapp[i][j] << "\033[0m" <<" ";
					else if(this->mapp[i][j]==0)
						std::cout<< "\033[1;37m" << this->mapp[i][j] << "\033[0m" <<" ";
				}
			}
			std::cout<<std::endl;
		}
	}
	if(this->endNoeud->inside(this->listeOuverte)){
		this->endNoeud->parent = currentNoeud;
		Noeud* cheminNoeud = this->endNoeud;
		while(cheminNoeud!=NULL){
			this->path.insert(this->path.begin(), sf::Vector2u(cheminNoeud->getX(),cheminNoeud->getY()) );
			cheminNoeud = cheminNoeud->parent;
		}
		return;
	}
	this->path.push_back(sf::Vector2u(this->startNoeud->getX(),this->startNoeud->getY()));
}

std::vector<sf::Vector2u > Aetoile :: getPath(){
	return this->path;
}
