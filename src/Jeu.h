#ifndef JEU_H
#define JEU_H
#include "structures.h"


/**
* \file Jeu.h
*
* Ce fichier décrit l'ensemble des fonctions concernant le déroulement d'une partie. Il contient 11 fonctions.
* -\b Jeu_init_fichier permet d'initialiser une partie à partir d'un fichier.
* -\b sauvegarde_deck permet de sauvegarder un Deck dans un fichier texte.
* -\b sauvegarde_dico permet de sauvegarder un dicoTuiles dans un fichier texte.
* -\b appartient_deck permet de vérifier l'appartenance d'une tuile dans un deck.
* -\b test_fin permet de tester si la partie est finie.
* -\b ScoreForet permet de compter le nombre de points obtenu grâce aux forêts.
* -\b ScoreLac permet de compter le nombre de points obtenu grâce aux lacs
* -\b ScoreRess permet de compter le nombre de points obtenu grâce aux usines et ressources.
* -\b ScoreVillage permet de trouver la taille d'un village.
* -\b Score_plus_grand_village permet de trouver le plus grand village d'une grille.
* -\b calculScore permet de trouver le score d'une grille de jeu.
* -\b Honshu_Opt permet de trouver le score maximum de manière brut.
* -\b Solveur_tour permet de trouver la meilleure action pour un tour.
* -\b Solveur_Heuristique permet trouver une estimation du score maximal possible.
* -\b maxTypeTerrain permet le maximum d'occurence d'un type de terrain.
* -\b solveurMaxTypeTerrain est un solveur maximisant le meilleur type de terrain.
* -\b deckRandomDico permet de créer un deck aléatoire à partir d'un Dico

*/


/**
* \brief Lis un fichier pour initialiser une partie
* \details Initialise la taille de la grille et la grille
* \param fichier Le fichier en question
* \param laGrille Une grille de jeu non initilisée
* \return Un type Deck pour commencer une partie
*/
Deck Jeu_init_fichier(char *fichier, grilleDeJeu *laGrille);


/**
* \brief Sauvegarde un Deck dans un fichier
* \details La taille de la grille et la grille doivent être initialisée
* \param fichier Le fichier à générer
* \param D Un Deck de jeu
* \attention g doit être initialisée
* \param g Une grilleDeJeu
*/
void sauvegarde_deck(char* fichier, Deck D, grilleDeJeu g);


/**
* \brief Sauvegarde un dictonnaire de tuiles dans un fichier
* \param fichier Le fichier à générer
* \param D Un dictionnaire de tuile
*/
void sauvegarde_dico(char* fichier, dicoTuiles D);


/**
* \brief Vérifie l'appartenance d'un id de tuile à un deck
* \param id Un entier positif
* \param D Un Deck de tuiles
* \return la position de l'id dans le deck si id est dans le deck de tuiles disponibles, -1 sinon
*/
int appartient_deck(int id, Deck D);


/**
* \brief Vérifie si des tuiles peuvent encore être posées sur la grille
* \details La fonction va vérifier pour toutes tuiles, selon les 4 orientations possibles, s'il existe une tuile encore posable.
* \param D Un deck de tuile
* \attention G doit être initialisée
* \param G Une grilleDeJeu
* \param dico Un dicoTuiles
* \param Historique Un tableau de tuilePosee
* \return 0 si la partie est finie, 1 sinon
*/
int test_fin(Deck D, grilleDeJeu G, dicoTuiles dico, tuilePosee *Historique);



/* Fonctions pour le score */

/**
* \brief Calcule le score atteint d'une grille
* \attention G doit être initialisée
* \param G une grilleDeJeu
* \return Renvoie le score d'une grille de Honshu
*/
int ScoreForet(grilleDeJeu G);


/**
* \brief Calcule le score obtenu avec les lacs
* \attention G doit être initialisée
* \param G une grilleDeJeu
* \return Renvoie le score d'une grille de Honshu
*/
int ScoreLac(grilleDeJeu G);


/**
* \brief Calcule le score obtenu avec les ressources et les usines
* \attention G doit être initialisée
* \param G une grilleDeJeu
* \return Renvoie le score d'une grille de Honshu
*/
int ScoreRess(grilleDeJeu G);


/**
* \brief Renvoie le score d'une ville associé à un village
* \details Utilise l'algorithme seed fill
* \attention G doit être initialisée
* \param laGrille Une grille de jeu
* \param X, Y deux entiers
* \return Renvoie le score d'un village (1 ou plusieurs villes)
*/
int ScoreVillage(grilleDeJeu laGrille ,int X ,int  Y, int parent);


/**
* \brief Renvoie le score du plus grand village
* \details Utilise la fonction ScoreVillage 
* \param laGrille Une grille de jeu
* \return Renvoie le score du plus grand village 
*/
int Score_plus_grand_village(grilleDeJeu laGrille);


/**
* \brief Calcule le score atteint d'une grille
* \attention G doit être initialisée
* \param G une grilleDeJeu
* \return Renvoie le score d'une grille de Honshu
*/
int calculScore(grilleDeJeu G);


/**
* \brief Solveur brut du Honshu 
* \attention G doit être initialisée
* \param G une grilleDeJeu
* \param D Un Deck de tuiles
* \param Dico Un dicoTuiles
* \param Historique Un tableau de tuilePosee
* \return Renvoie le score obtenu par le solveur
*/
int Honshu_Opt(grilleDeJeu G, Deck D, dicoTuiles Dico, tuilePosee *Historique);


/**
* \brief Solveur permettant de trouver la meilleur tuile à placer
* \attention G doit être initialisée
* \param G une grilleDeJeu
* \param D Un Deck de tuiles
* \param Dico Un dicoTuiles
* \param Historique Un tableau de tuilePosee
* \param (*Calcul)(grilleDeJeu) est un pointeur vers une fonction de calcul de points
* \return Renvoie un type tuilePosee de la meilleur tuile possible
*/
tuilePosee Solveur_tour(grilleDeJeu G, Deck D, dicoTuiles Dico, tuilePosee *Historique, int (*Calcul)(grilleDeJeu));


/**
* \brief Solveur global utisant solveur_tour
* \attention G doit être initialisée
* \param G une grilleDeJeu
* \param D Un Deck de tuiles
* \param Dico Un dicoTuiles
* \param Historique Un tableau de tuilePosee
* \param (*Calcul)(grilleDeJeu) est un pointeur vers une fonction de calcul de points
* \param afficher Un entier (si afficher est égal à 1, la grille solution est affiché)
* \return Renvoie l'estimation du meilleure score
*/
int Solveur_Heuristique(grilleDeJeu G, Deck D, dicoTuiles Dico, tuilePosee *Historique, int (*Calcul)(grilleDeJeu), int afficher);


/**
* \brief Fonction permettant de compter les occurences de chaque type de terrains sur la grille et dans le deck
* \param D Un Deck de tuiles
* \param Dico Un dicoTuiles
* \param Historique Un tableau de tuilePosee
* \return Renvoie le type de terrain dont le nombre d'occurence est maximum.
*/
terrain maxTypeTerrain(Deck D, dicoTuiles Dico, tuilePosee *Historique);


/**
* \brief Solveur maximant un type de terrain
* \attention G doit être initialisée
* \param G une grilleDeJeu
* \param D Un Deck de tuiles
* \param Dico Un dicoTuiles
* \param Historique Un tableau de tuilePosee
* \return Renvoie 1 si un maximum de type de terrain a été trouvé, 0 sinon
*/
int solveurMaxTypeTerrain(grilleDeJeu *G, Deck D, dicoTuiles Dico, tuilePosee *Historique);


/**
* \brief Génére un deck aléatoire à partir d'un dico
* \param Dico Un dicoTuiles
* \param tailleDeck Un entier correspondant à la taille du deck voulu
* \return Renvoie le deck généré
*/
Deck deckRandomDico(dicoTuiles Dico, int tailleDeck);

#endif


























