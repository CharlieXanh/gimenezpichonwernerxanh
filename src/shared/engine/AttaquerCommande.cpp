#include "AttaquerCommande.h"
// to use console
#include <iostream>

using namespace engine;
using namespace state;
using namespace std;


AttaquerCommande::AttaquerCommande (state::Joueur &attaquant,
    state::Joueur &cible) : attaquant(attaquant), cible(cible)
{
    id = ATTAQUER;
}

void AttaquerCommande::execute(state::Etat &etat){
    cout << "ATTENTION! " << attaquant.getNom() << " essaye d'attaquer " << cible.getNom() << endl;
    //todo : check distance


        cout << "Sante actuel de " << cible.getNom() << ": " << cible.getCaracteristiques().getSante() << endl;


        int baseDamage = attaquant.getCaracteristiques().getAttaque();

        int cibleHealth = cible.getCaracteristiques().getSante();

        // On utilise la defense et un coef pour reduire les dégats
        float cibleDefense = cible.getCaracteristiques().getDefense() * 0.01;
        cout << "Coef de defense de la cible (" << cible.getNom() << ") : " << cibleDefense << endl;
        cout << "Dégats de base de l'attaquant (" << attaquant.getNom() << ") : " << baseDamage << endl;
        int finalDamage = (1 - cibleDefense) * baseDamage;
        cout << "Dégats infligés finaux : " << finalDamage <<  endl;

        int finalHealth = cibleHealth - finalDamage;

        cible.getCaracteristiques().setSante(finalHealth);
        if (cible.getCaracteristiques().getSante() < 1){
            cible.setStatut(MORT);
        }
        cout << "La santé de " << cible.getNom() << " descend à : " << cible.getCaracteristiques().getSante() << endl;
}
