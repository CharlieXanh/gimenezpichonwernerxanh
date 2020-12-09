#include "Echange.h"
#include "Item.h"
// #include <time.h>
// #include <stdlib.h>
// #include <string>
// #include <iostream>
// #include "Caracteristiques.h"
//
// #define NB_ITEM_WORDS 10
//
// using namespace state;
// using namespace std;
//
// Echange :: Echange(){
// 	/* initialize random seed: */
//  	srand (time(NULL));
//  	int prix;
//  	int i=0;
//
//  	std::vector<string> wordList(NB_ITEM_WORDS);
//
//  	string file_name = "items_words.txt";
//
//  	std :: ifstream fin(file_name);
//
//  	if (!fin.good()) {
// 		throw runtime_error("Cannot open file ");
// 	}
// 	while(true){
// 		char tmp[0x1000];
// 		fin.getline (tmp,0x1000);
// 		if (fin.eof()) {
// 			break;
// 		}
// 		if (!fin.good()){
// 			throw runtime_error("Cannot read file");
// 		}
// 		wordList[i] = tmp;
// 		i++;
// 	}
//
// 	while(wordList.size()!=NB_ITEM){
// 		wordList.erase(wordList.begin() + rand()%wordList.size()-1);
// 	}
//
// 	for(int i=0;i<NB_ITEM;i++){
// 		Caracteristiques* elem = new Caracteristiques(rand() % 10 + 1,rand() % 10 + 1,
// 			rand() % 10 + 1,rand() % 10 + 1,rand() % 10 + 1);
// 		prix = rand() % 10 + 1 /* Nombre aléatoire entre 1 et 10 */
// 		this->item[i] = new Item(wordList[i],prix,elem);
// 		delete elem;
// 	}
// }
//
// std::vector<item> Echange::getItems(){
// 	return this->item;
// }
//
// bool Echange::acheter(Item item){
// 	if (this->jouant->getMonnaie()<item->getPrix()){
// 		return FALSE;
// 	}
// 	else{
// 		this->jouant->soustraireMonnaie(item->getPrix());
// 		Caracteristiques* bonus = item->getBonus();
// 		this->jouant->entite->caracteristiques->addBonus(bonus->getSante(),
// 			bonus->getAttaque(),bonus->getDefense(),bonus->getInitiative(),bonus->getVitesse());
// 	}
// }
