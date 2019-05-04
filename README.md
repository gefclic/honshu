# HONSHU by StrangerC

## L'Équipe StrangerC
+ Benoit SCHOLL
+ Heykel RAJHI
+ Kevin XU
+ Jiahui XU

## État du projet
DONE 

## Description
Développement d'une application ludique du jeu de plateau Honshu avec son solveur associé

## Contenus

+ obj : contient les fichiers objets.
+ src : contient les headers et les sources du jeu.
+ bin : contient les exécutables.
+ doc : contient la documentation du code.
+ tests : contient les tests unitaires des fonctions dans src.
+ sauvegardes : contient les fichiers pour initialisation d'une partie de Honshu, il contient entres autres les fichiers générés par le jeu.

## Langage
+ C

## Instructions d'installation 

+ Pour lancer le jeu, dans lot_A, entrez la commande suivante : make && ./bin/Honshu
		
+ Pour lancer les tests unitaires : 
		make test && ./tests/test

+ Pour générer la documentation avec Doxygen dans doc : 
		make doc

## Debug
+ Pour vérifier l'absence de fuite mémoire :
		valgrind ./bin/Honshu
+ Pour avoir plus de détails sur les fuites mémoires :
		valgrind --leak-check=full ./bin/Honshu


## Notes







