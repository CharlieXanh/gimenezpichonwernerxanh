# Projet Logiciel Transversal

> Ce projet a pour but de developper un jeu video dans le cadre de la formation "Informatique et systèmes" de l'Ecole Nationale Superieure de l'Electonique et de ses Applications.

[![forthebadge](https://forthebadge.com/images/badges/made-with-c-plus-plus.svg)](https://forthebadge.com)

## Release 1.final

## Get Started

Cloner le repertoire
```sh
$ git clone https://github.com/CharlieXanh/gimenezpichonwernerxanh.git
```

## Build le projet

```sh
$ cd gimenezpichonwernerxanh
$ mkdir build
$ cd build
$ cmake ..
$ make -j
```

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

## Affichage d'un joueur qui est deplace par l'IA
```sh
$ ./bin/client random_ai
```

## Historique des release
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
