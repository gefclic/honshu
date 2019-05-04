#ifndef GRILLE_H
#define GRILLE_H
#include "structures.h"

/**
* \file Grille.h
* 
* Ce fichier décrit un ensemble de fonctions liées à l'utilisation de la grille de la jeu. Il contient 11 fonctions.
* - \b grille_create permet de créer une grille de type laCase
* - \b lireCaseType permet de lire le type de terrain d'une case de la grille.
* - \b lireCaseNumeroTuile permet de lire le numéro de la tuile posé sur une case de la grille.
* - \b afficheGrille permet d'afficher la grille sur le terminal.
* - \b PoserTuile permet de poser une tuile sur une grille de jeu.
* - \b verifHorsTerrain permet de vérifier que des coordonnées ne soient pas en dehors du plateau.
* - \b verifLac permet de vérifier qu'aucun lac de la grille n'est recouvert.
* - \b verifRecouvreUneTuile permet de vérifier au moins une case de l'une des tuiles du plateau est recouvert par une tuile.
* - \b neRecouvrePasTotalementUneTuile permet vérifier qu'aucune tuile n'est recouverte.
* - \b PoserTuileAvecTest permet de poser tuile en effectuant tous les tests nécessaires avant.
* - \b RetraitDerniereTuile permet de retirer la dernière tuile posée sur la grille.
*/


/**
* \brief Initialise la grille
* \details Alloue la mémoire nécessaire pour initialiser une matrice de type laCase. 
* On initialise toutes les cases en type 'E' et les numéros de tuiles sont à -1. 
* On initialise le nbTuilePosees à 0. 
* On alloue la mémoire pour tableau tuilesDejaPosees.
* \attention Le champ taille de la grille doit être initialisée.
* \param laGrille Un pointeur vers une grille de jeu
* \param nbDeTuilesDuDeck Un entier qui correspond aux nombres de tuiles du Deck
*/
void grille_create(grilleDeJeu *laGrille, int nbDeTuilesDuDeck);


/**
* \brief Lis le type de terrain sur la case (x,y)
* \attention x et y doivent être inférieur à la taille de la grille
* \param x Un entier positif
* \param y Un entier positif
* \attention laGrille doit être initialisée
* \param laGrille Une grille de Jeu
* \return Le type de terrain de la case (x,y)
*/
terrain lireCaseType (int x, int y, grilleDeJeu laGrille);


/**
* \brief Lis le numero de la tuile sur la case (x,y)
* \attention x et y doivent être inférieur à la taille de la grille
* \param x Un entier positif
* \param y Un entier positif
* \attention laGrille doit être initialisée.
* \param laGrille Une grille de Jeu
* \return Le numéro de la tuile posée sur la case (x,y), -1 si aucune n'est posée dessus
*/
int lireCaseNumeroTuile (int x, int y, grilleDeJeu laGrille);


/**
* \brief Réinitialise l'entier Comptage après un appel à la fonction Score_plus_grand_village 
* \attention laGrille doit être initialisée
* \param laGrille la grille de jeu a réinitialisé
*/
void resetCompteurGrille(grilleDeJeu laGrille);


/**
* \brief Affiche la bonne couleur sur le terminal selon le type de terrain
* \param leTerrain Un terrain
*/
void ChoixCoul(terrain leTerrain);


/**
* \brief Affiche la grille de jeu
* \param laGrille Une grille de jeu initialisée au moins.
*/
void afficheGrille(grilleDeJeu laGrille);


/**
* \brief Insére une tuile dans la grille après avoir réaliser l'ensemble des tests
* \attention laGrille doit être initialisée
* \param laGrille Une grille de jeu
* \param laTuile La tuile à poser
* \param X, Y deux entiers définissant les coordonnées de la tuile
* \return 1 si la tuile a pu être posé, 0 sinon
*/
int PoserTuile(grilleDeJeu laGrille, tuile laTuile, int X, int Y);


/**
* \brief Vérifie si des coordonnées sont en dehors du plateau
* \attention laGrille doit être initialisée
* \param x, y deux entiers définissant les coordonnées de la tuile
* \param laGrille Une grille de jeu
* \return 1 si les coordonnées x et y sont dans la grille de jeu, 0 sinon
*/
int verifHorsTerrain(int x, int y, grilleDeJeu laGrille);


/**
* \brief Test de la règle Aucune case Lac ne peut être recouverte
* \attention laGrille doit être initialisée
* \param laGrille Une grille de jeu
* \param laTuile La tuile à poser
* \param X, Y deux entiers définissant les coordonnées de la tuile
* \return 0 Si un lac va être recouvert, 1 sinon 
*/
int verifLac(grilleDeJeu laGrille, tuile laTuile, int X, int Y);


/**
* \brief Test de la règle doit recouvrir au moins une case de l'une des tuiles du plateau
* \attention laGrille doit être initialisée
* \param laGrille de type grilleDeJeu
* \param laTuile La tuile à poser
* \param X, Y deux entiers définissant les coordonnées de la tuile
* \return 1 Si au moins une case d'une tuile va être recouverte, 0 sinon
*/
int verifRecouvreUneTuile(grilleDeJeu laGrille, tuile laTuile, int X, int Y);


/**
* \brief Test de la règle Une tuile ne peut être totalement recouverte à
aucun moment de la partie
* \attention laGrille doit être initialisée
* \param laGrille de type grilleDeJeu
* \param laTuile La tuile à poser
* \param X, Y deux entiers définissant les coordonnées de la tuile
* \return 0 si une tuile va être recouverte, 1 sinon
*/
int neRecouvrePasTotalementUneTuile(grilleDeJeu laGrille, tuile laTuile, int X, int Y);


/**
* \brief Fonction d'appel poser tuile qui effectue les tests avant
* \attention laGrille doit être initialisée
* \param laGrille Un pointeur vers un type grilleDeJeu
* \param laTuile La tuile à poser
* \param X, Y deux entiers définissant les coordonnées de la tuile
* \param Historique Un tableau de tuilePosee
* \return 1 si la tuile a pu être posée après réalisé tous les tests, 0 sinon
*/
int PoserTuileAvecTest(grilleDeJeu *laGrille, tuile laTuile, int X, int Y, tuilePosee *Historique);


/**
* \brief Retire la dernière tuile posée de la grille 
* \attention laGrille doit être initialisée
* \param G Un pointeur vers une grilleDeJeu
* \param D un Deck de jeu
* \param Dico Un dictionnaire de tuile
* \param Historique Un tableau de tuilePosee
* \return 1 si la tuile a pu être retirer, 0 sinon
*/
int RetraitDerniereTuile(grilleDeJeu *G, Deck D, dicoTuiles Dico, tuilePosee *Historique);


#endif 
