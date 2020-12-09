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

## Historique des release
* 1.final
    * Creation du diagramme d'etat
    * Implementation des premiers tests unitaires
* 1.1
    * Implementation d'un message de retour
