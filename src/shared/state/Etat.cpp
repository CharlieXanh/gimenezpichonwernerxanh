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
    initializeMapCell("res/arene.csv");
}

std::vector<std::vector <int > > Etat:: load_map(std::string fileName){

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


void Etat::initializeMapCell(std::string mapRessource)
{
    // Iteration helpers
    unsigned int k = 0;

    // mapping (this will be dependent on the choosed resource)
    // dictionary to signalize the type of each tileset by his id
    // (tile id defined by the position of the tile in de resource, we dont define it)

    std::vector<std::vector <int > > map_tile = load_map(mapRessource);
    cout << "--- Loading and building map_tile array succesfully ---" << endl;

    std::vector<int> const mapp_spaces { 0, 2, 3, 5, 7 };

    std::vector<unique_ptr<MapCell>> primitive;

    for (unsigned int i = 0;i<map_tile.size();i++)
    {
        std::vector<std::unique_ptr<MapCell>> newline;
        for (unsigned int j = 0; j < map_tile[i].size(); j++)
        {
            if (map_tile[i][j])
            {
                if (std::find(mapp_spaces.begin(),mapp_spaces.end(),map_tile[i][j]) != mapp_spaces.end())
                {
                    std::unique_ptr<SpaceMapCell> spc(new SpaceMapCell(FLOOR, j, i, map_tile[i][j]));
                    newline.push_back(move(spc));
                }
                else
                {
                    std::unique_ptr<ObstacleMapCell> obs(new ObstacleMapCell(WALL, j, i, map_tile[i][j]));
                    newline.push_back(move(obs));
                }
            }
            k++;
        }
        cout << endl;
        map.push_back(move(newline));
    }

    cout << "--- Map created succesfully ---" << endl;

    return;
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
    ptrJ1->getCaracteristiques().setSante(100);
    ptrJ1->getCaracteristiques().setAttaque(10);
    ptrJ1->getCaracteristiques().setDefense(5);
    joueurs.push_back(move(ptrJ1));

    std::unique_ptr<Joueur> ptrJ2(new Joueur("Leo", 17));
    ptrJ2->getCaracteristiques().setSante(100);
    ptrJ2->getCaracteristiques().setAttaque(10);
    ptrJ2->getCaracteristiques().setDefense(5);
    joueurs.push_back(move(ptrJ2));
  }
  else
  {
    cout << "Pas en mode engine" << endl;
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
