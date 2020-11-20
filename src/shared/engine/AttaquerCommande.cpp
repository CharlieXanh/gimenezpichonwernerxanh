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
    // cout << "ATENTION! " << attaquant.getNom() << " is trying to attack " << cible.getNom() << endl;
    // // check distance
    //
    //     // attacking
    //     cout << "Actual health of " << cible.getNom() << ": " << cible.getEntite().getCaracteristiques().getSante() << endl;
    //
    //     // easier to read.
    //     int baseDamage = attaquant.getEntite().getCaracteristiques().getAttaque();
    //
    //     int cibleHealth = cible.getEntite().getCaracteristiques().getSante();
    //
    //     // we'll work the defense as a coeficient to reduce the final damage
    //     float cibleDefense = cible.getEntite().getCaracteristiques().getDefense() * 0.01;
    //     cout << "Defense coef. of the cible (" << cible.getNom() << ") is: " << cibleDefense << endl;
    //     cout << "Base damage of the attacker (" << attaquant.getNom() << ") is: " << baseDamage << endl;
    //     int finalDamage = (1 - cibleDefense) * baseDamage;
    //     cout << "Final given damage: " << finalDamage <<  endl;
    //
    //     int finalHealth = cibleHealth - finalDamage;
    //
    //     cible.getEntite().getCaracteristiques().setSante(finalHealth);
    //     if (cible.getEntite().getCaracteristiques().getSante() < 1){
    //         //cible.setStatus(DEATH);
    //     }
    //     cout << "After HIT, the health of " << cible.getNom() << " descends to: " << cible.getEntite().getCaracteristiques().getSante() << endl;
}
