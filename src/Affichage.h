#ifndef AFFICHAGE_H
#define AFFICHAGE_H
#include "structures.h"

/**
* \file Affichage.h
* 
* Ce fichier décrit l'ensemble des fonctions d'affichage terminal du Jeu. Il contient 6 fonctions.
* - \b Affiche_Deck permet d'afficher le dictionnaire de tuiles.
* - \b Affiche_Grille_Score_Regle permet d'afficher la grille de jeu avec le score et les règles.
* - \b boucle_principale permet d'afficher l'interface d'une partie de Honshu et permet de jouer.
* - \b getch permet de lire une entrée sans avoir à appuyer sur la touche Entrée pour valider.
* - \b jeu_fichier_random permet de lancer une partie de Honshu avec un deck généré aléatoirement.
* - \b jeu_fichier permet de lancer une partie de Honshu avec un deck préconçu.
* - \b mode_solveur permet de lancer une partie de Honshu qui n'utilise que les solveurs.
*/


#define clrscr() printf("\033[H\033[2J") /**< Fonction permettant d'effacer l'écran du terminal */
#define couleur(param) printf("\033[%sm",param) /**< Fonction permettant de modifier les couleurs de la console */


/**
* \brief Affiche un dictionnaire sur le terminal
* \param Dico Un dictionnaire de tuiles
* \param D Un deck de jeu
* \param Historique Un tableau de tuilePosee
*/
void Affiche_Deck(dicoTuiles Dico, Deck D, tuilePosee *Historique);


/**
* \brief Affiche la grille de jeu, le score et les règles
* \attention G doit être initialisée.
* \param laGrille  Une grilleDeJeu
* \param score le score actuel du plateau
* \param h Un entier (Si h=1, les règles vont s'afficher)
*/
void Affiche_Grille_Score_Regle(grilleDeJeu laGrille, int score, int h);


/**
* \brief Affichage d'une partie jouable de Honshu 
* \attention G doit être initialisée.
* \param G Une grilleDeJeu
* \param D Un deck de jeu
* \param Dico un dictionnaire de tuiles
*/
void boucle_principale(grilleDeJeu G, Deck D, dicoTuiles Dico);


/**
* \brief Permet de récupérer un caractère du flux d'entrée sans avoir à appuyer sur Entrée
* \return le char lu sur la console
*/
char getch();


/**
* \brief Affichage du jeu pour une partie avec un deck aleatoire
*/
void jeu_fichier_random();


/**
* \brief Affichage du jeu pour une partie avec un deck préconçu
*/
void jeu_fichier();


/**
* \brief Mode solveur : test des différents solveurs 
* \attention G doit être initialisée.
* \param G Une grilleDeJeu
* \param D Un deck de jeu
* \param Dico un dictionnaire de tuiles
*/
void mode_solveur(grilleDeJeu G, Deck D, dicoTuiles Dico);


#endif














