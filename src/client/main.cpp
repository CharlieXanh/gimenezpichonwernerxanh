#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include <state.h>
#include <string.h>

using namespace std;
using namespace state;

int main(int argc,char* argv[])
{
    Exemple exemple;
    exemple.setX(53);
	
	if(argc >= 2 && strcmp(argv[1],"hello") == 0 )
		cout << "Ca fonctionne !" << endl;

	if(argc >= 2 && strcmp(argv[1],"State") == 0 ){
		cout << "Début des tests états!" << endl;
		//tests todo
	}
    return 0;
}
