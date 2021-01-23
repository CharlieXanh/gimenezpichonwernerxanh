# Projet Logiciel Transversal

> Ce projet a pour but de développer un jeu vidéo dans le cadre de la formation "Informatique et systèmes" de l'Ecole Nationale Supérieure de l'Electronique et de ses Applications.

[![forthebadge](https://forthebadge.com/images/badges/made-with-c-plus-plus.svg)](https://forthebadge.com)

## Release 4.1

## Get Started

Cloner le répertoire
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
Ce fichier permet de créer le dossier /build et effectue les commandes nécessaires pour la compilation du projet.

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

Lors du tour d'un joueur, il est possible d'effectuer différentes actions en appuyant sur la touche correspondante. Après appui, il faut sélectionner la case à l'aide du <kbd>Clic droit</kbd>:

<kbd>M</kbd> - permet de déplacer le joueur dans la zone de déplacement bleue.

<kbd>A</kbd> - permet d'attaquer un personnage dans la zone rouge autour du joueur.

<kbd>F</kbd> - permet de mettre fin au tour du joueur.

## Affichage d'un message

```sh
$ ./bin/client hello
```

## Test unitaire
```sh
$ cd gimenezpichonwernerxanh
$ ./boost.sh
```
## Affichage d'une fenêtre
```sh
$ ./bin/client render
```

## Affichage d'une séquence de tours
```sh
$ ./bin/client engine
```
>Pour lancer un tour, appuyez sur une touche.

## Affichage d'un joueur qui est déplacé par l'IA simple
```sh
$ ./bin/client random_ai
```

## Affichage d'un joueur qui est déplacé par l'IA heuristique
```sh
$ ./bin/client heuristic_ai
```

## Lancement du thread client

```sh
$ ./bin/client thread
```



## Historique des release

- 4.1
  - Implémentation du thread client
  - Simplification des commandes d'installation, commandes de build et commande de tests unitaires à l'aide de fichier script bash
  - Rapport 4.1

* 3.1
    * Création du diagramme de l'IA heuristique
    * Implémentation d'une IA heuristique pour les déplacements, basée sur l'algorithme A*
    * Rapport 3.1
* 2.final
    * Création du diagramme de l'IA simple
    * Implémentation d'une IA simple basée sur l'aléatoire
    * Rapport 2.final
* 2.2
    * Création du diagramme du moteur de jeu
    * Implémentation du moteur de jeu
    * Rapport 2.2
* 2.1
    * Création de diagramme de rendu
    * Implémentation du rendu
    * Rapport 2.1
* 1.final
    * Création du diagramme état
    * Implémentation des premiers tests unitaires
    * Premiers tests de code coverage
    * Rapport 1.final
* 1.1
    * Implémentation d'un message de retour
    * Rapport 1.1
