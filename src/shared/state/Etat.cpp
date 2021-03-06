#include "Etat.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <algorithm>
#include <vector>
#include "SpaceMapCell.h"
#include "ObstacleMapCell.h"
#include <map>

#include "SpaceMapCell.h"
#include "ObstacleMapCell.h"
#include <map>
using namespace std;
using namespace state;

Etat::Etat(std::string nMode) : curseur(10, 10), ordre(*this)
{
    this-> mode = nMode;
    cout << "Creation d'un objet ETAT en mode >>>" + mode + "<<<\n";
    actionActuelle = IDLE;
    cout << "Creation d'un objet MAGASIN" << endl;
    Magasin mag;
    this -> magasin = mag;
    this-> jouant = 0;
    initializeMapCell("res/Map/arene.csv");
}

std::vector<std::vector <int > > load_map(std::string fileName){

    std::ifstream infile(fileName);

    std::vector<std::vector <int> > map;
    std::vector<int> lineVector;
    std::string sum="";

    for(std::string line; getline( infile, line );){
        for(char elem : line){
            if (elem == ',' or elem == ' '){
                lineVector.push_back(std::stoi (sum));
                sum = "";
            }else{
                sum+=elem;
            }
        }
        sum = "";
        map.push_back(lineVector);
        lineVector.clear();
    }
    return map;
}

void Etat::initializeMapCell(std::string mapResource)
{

    // mapping (this will be dependent on the choosed resource)
    // dictionary to signalize the type of each tileset by his id
    // (tile id defined by the position of the tile in de resource, we dont define it)

    std::vector<std::vector <int > > map_tile = load_map(mapResource);
    cout << "--- Loading and building map_tile array succesfully ---" << endl;

    std::vector<int> const mapp_obstacles {35,36,37,38,48,49,50,55,56,57,58,64,66,71,72,74,80,81,82,86,87,88,89,90};

    std::vector<unique_ptr<MapCell>> primitive;

    for (unsigned int i = 0;i<map_tile.size();i++)
    {
        std::vector<std::unique_ptr<MapCell>> newline;
        for (unsigned int j = 0; j < map_tile[i].size(); j++)
        {
            if (map_tile[i][j])
            {
                if (std::find(mapp_obstacles .begin(),mapp_obstacles .end(),map_tile[i][j]) != mapp_obstacles .end())
                {
                  std::unique_ptr<ObstacleMapCell> obs(new ObstacleMapCell(WALL, j, i, map_tile[i][j]));
                  newline.push_back(move(obs));

                }
                else
                {
                  std::unique_ptr<SpaceMapCell> spc(new SpaceMapCell(FLOOR, j, i, map_tile[i][j]));
                  newline.push_back(move(spc));
                }
            }
        }
        map.push_back(move(newline));
    }

    cout << "--- Map created succesfully ---" << endl;

    return;
}

std::vector<std::vector<int>> Etat::loadMapCell(){

    std::vector<int> wall={35,36,37,38,48,49,50,55,56,57,58,64,66,71,72,74,80,81,82,86,87,88,89,90};
    std::vector<std::vector<int>> mapWall;
    std::vector<std::vector<int>> mapp = load_map("res/Map/arene.csv");
    for(unsigned int j=0;j<mapp.size();j++){
        std::vector<int> line;
        for(unsigned int i=0;i<mapp[j].size(); i++){
            if(std::find(wall.begin(),wall.end(),mapp[j][i])!=wall.end()){
                line.push_back((int)1);
            }else{line.push_back(0);}
        }
        mapWall.push_back(line);
    }
    return mapWall;
}

// Etat :: Etat(std::vector<Joueur> joueurs, std::vector<Joueur> ennemis,Joueur jouant,
//             Curseur curseur){
//
//   this->joueurs = joueurs;
//   this->ennemis = ennemis;
//
//
//   this->jouant = jouant;
//
//   this->tour = 0;
//   this->multijoueur = false;
//   this->terminerJeu = false;
//   Curseur curs{0,0};
//   this->curseur = curs;
//
// }

std::string Etat::getMode(){
  return mode;
}

std::vector<std::unique_ptr<Joueur>> &Etat::getJoueurs()
{
    vector<unique_ptr<Joueur>> &refCharacters = joueurs;
    return refCharacters;
}

std::vector<std::unique_ptr<Joueur>> &Etat::getEnnemis()
{
    vector<unique_ptr<Joueur>> &ref = ennemis;
    return ref;
}

int Etat::getNbrJoueurs(){
  return this->nbrJoueurs;
}

int Etat::getTour()
{
  return tour;
}

bool Etat::getTerminerJeu(){
  return terminerJeu;
}

EtatActionActuelleID Etat::getActionActuelle()
{
  return actionActuelle;
}

void Etat::setActionActuelle(EtatActionActuelleID newAction)
{
  this->actionActuelle = newAction;
}

Curseur& Etat::getCurseur()
{
  Curseur &refCurseur = curseur;
  return refCurseur;
}

void Etat:: init(){}


void Etat::initJoueurs(){

  if(mode == "engine")
  {
    std::unique_ptr<Joueur> ptrJ1(new Joueur("Raph", 20));
    ptrJ1->setJoueurIndex(0);
    ptrJ1->getCaracteristiques().setSante(40);
    ptrJ1->getCaracteristiques().setAttaque(10);
    ptrJ1->getCaracteristiques().setDefense(5);
    ptrJ1->setDeplacements(3);
    ptrJ1->getPosition().placer(5,10);
    joueurs.push_back(move(ptrJ1));

    std::unique_ptr<Joueur> ptrJ2(new Joueur("Leo", 17));
    ptrJ2->setJoueurIndex(0);
    ptrJ2->getCaracteristiques().setSante(40);
    ptrJ2->getCaracteristiques().setAttaque(10);
    ptrJ2->getCaracteristiques().setDefense(5);
    ptrJ2->setDeplacements(3);
    ptrJ2->getPosition().placer(5,5);
    joueurs.push_back(move(ptrJ2));
  }
  else if(mode == "random_ai")
  {
    std::unique_ptr<Joueur> ptrJ1(new Joueur("Raph_joueur", 20));
    ptrJ1->setJoueurIndex(0);
    ptrJ1->getCaracteristiques().setSante(40);
    ptrJ1->getCaracteristiques().setAttaque(10);
    ptrJ1->getCaracteristiques().setDefense(5);
    ptrJ1->setDeplacements(3);
    ptrJ1->getPosition().placer(16,17);
    ptrJ1->getCaracteristiques().setVitesse(8);
    ptrJ1->setEstEnnemi(false);
    joueurs.push_back(move(ptrJ1));

    std::unique_ptr<Joueur> ptrJ2(new Joueur("Leo_ai", 17));
    ptrJ2->setJoueurIndex(1);
    ptrJ2->getCaracteristiques().setSante(40);
    ptrJ2->getCaracteristiques().setAttaque(10);
    ptrJ2->getCaracteristiques().setDefense(5);
    ptrJ2->setDeplacements(3);
    ptrJ2->getPosition().placer(4,3);
    ptrJ2->getCaracteristiques().setVitesse(5);
    ptrJ2->setEstEnnemi(true);
    joueurs.push_back(move(ptrJ2));
  }
  else
  {
    std::unique_ptr<Joueur> ptrJ1(new Joueur("Raph", 20));
    ptrJ1->setJoueurIndex(0);
    ptrJ1->getCaracteristiques().setSante(40);
    ptrJ1->getCaracteristiques().setAttaque(10);
    ptrJ1->getCaracteristiques().setDefense(5);
    ptrJ1->setDeplacements(3);
    ptrJ1->getPosition().placer(5,10);
    joueurs.push_back(move(ptrJ1));

    std::unique_ptr<Joueur> ptrJ2(new Joueur("Leo", 17));
    ptrJ2->setJoueurIndex(0);
    ptrJ2->getCaracteristiques().setSante(40);
    ptrJ2->getCaracteristiques().setAttaque(10);
    ptrJ2->getCaracteristiques().setDefense(5);
    ptrJ2->setDeplacements(3);
    ptrJ2->getPosition().placer(5,5);
    joueurs.push_back(move(ptrJ2));
  }

  curseur.setPosition(joueurs[0]->getPosition());
  cout << "Joueurs initialisés" << endl;

}

void Etat::setTour(int tour)
{
  this->tour = tour;
}

void Etat::setTerminerJeu(bool resultat)
{
  this->terminerJeu = resultat;
}

int Etat::getJouant()
{
  return this->jouant;
}

void Etat::setJouant(int joueurSuivant){
  this->jouant = joueurSuivant;
}
std::vector<std::vector<std::unique_ptr<MapCell>>>& Etat::getMap(){
  return this->map;
}
void Etat::transitionEtat(Etat etat){
}

Etat::~Etat(){}
