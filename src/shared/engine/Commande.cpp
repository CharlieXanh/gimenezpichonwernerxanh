#include "Commande.h"
using namespace engine;

CommandeID Commande::getCommandeID(){
	return id;
}

void Commande::setId(CommandeID id)
{
	this->id = id;
}
