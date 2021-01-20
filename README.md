# Projet Logiciel Transversal

> Ce projet a pour but de developper un jeu video dans le cadre de la formation "Informatique et systèmes" de l'Ecole Nationale Superieure de l'Electonique et de ses Applications.

[![forthebadge](https://forthebadge.com/images/badges/made-with-c-plus-plus.svg)](https://forthebadge.com)

## Release 3.1

## Get Started

Cloner le repertoire
```sh
$ git clone https://github.com/CharlieXanh/gimenezpichonwernerxanh.git
```
## Installer les dépendances
Pour installer les dépendances du projet, vous pouvez exécuter le fichier install-dep.sh tel que :
```sh
$ cd gimenezpichonwernerxanh
$ ./install-dep.sh
```

## Build le projet
Vous pouvez lancer le fichier .sh prévu à cet effet :
```sh
$ cd gimenezpichonwernerxanh
$ ./reset_build.sh
```
Ce fichier permet de creer le dossier /build et effectue les commandes necessaires pour la compilation du projet.

Ou lancer les commandes une à une :
```sh
$ cd gimenezpichonwernerxanh
$ mkdir build
$ cd build
$ cmake ..
$ make -j
```

Dans le cas où vous apporteriez des modifications dans les fichiers du projet, vous pouvez utiliser le fichier remake.sh prévu :
```sh
$ cd gimenezpichonwernerxanh
$ ./remake.sh
```

## Commandes de jeu

[M](#){.btn .btn-default} - Pour pouvoir se déplacer



## Affichage d'un message

```sh
$ ./bin/client hello
```

## Test unitaire
```sh
$ cd build
$ ./test/shared/test_shared_dummy
```
## Affichage d'une fenêtre
```sh
$ ./bin/client render
```

## Affichage d'une sequence de tours
```sh
$ ./bin/client engine
```
>Pour lancer un tour, appuyez sur une touche.

## Affichage d'un joueur qui est deplace par l'IA simple
```sh
$ ./bin/client random_ai
```

## Affichage d'un joueur qui est deplace par l'IA heuristique
```sh
$ ./bin/client heuristic_ai
```

## Historique des release
* 3.1
    * Création du diagramme de l'IA heuristique
    * Implémentation d'une IA heuristique pour les déplacements, basée sur l'algorithme A*
    * Rapport 3.1
* 2.final
    * Creation du diagramme de l'IA simple
    * Implémentation d'une IA simple basée sur l'aléatoire
    * Rapport 2.final
* 2.2
    * Creation du diagramme du moteur de jeu
    * Implementation du moteur de jeu
    * Rapport 2.2
* 2.1
    * Creation de diagramme de rendu
    * Implementation du rendu
    * Rapport 2.1
* 1.final
    * Creation du diagramme d'etat
    * Implementation des premiers tests unitaires
    * Premiers tests de code coverage
    * Rapport 1.final
* 1.1
    * Implementation d'un message de retour
    * Rapport 1.1
