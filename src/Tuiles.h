#ifndef TUILES_H
#define TUILES_H
#include "structures.h"

/**
* \file Tuiles.h
* 
* Ce fichier décrit l'ensemble des fonctions qui manipulent les tuiles. Il contient 5 fonctions.
* - \b tuile_print permet d'afficher à l'écran une tuile.
* - \b tuile_init permet d'initialiser une tuile.
* - \b tuile_init_random permet d'initialiser une tuile de manière aléatoire.
* - \b tuile_init_fichier permet de créer un dictionnaire de tuiles à partir d'un fichier
* - \b tuile_rotation permet de tourner une tuile vers la droite de 90°.
*/


/**
* \brief Affiche la tuile dans le terminal.
* \param T Une tuile non NULL.
*/
void tuile_print(tuile *T);


/**
* \brief Initialise une tuile
* \details Initialise l'orientation de la tuile à 0
* \param T Un pointeur vers une tuile.
* \param id Un entier correspondant à l'id de la tuile
* \param t1, t2, t3, t4, t5, t6 Six caractères correspondants aux types des terrains de la tuile
*/
void tuile_init(tuile *T, int id, char t1, char t2, char t3, char t4, char t5, char t6);


/**
* \brief Initialise une tuile de manière aléatoire.
* \param T Un pointeur vers une tuile.
* \param id Un entier correspondant à l'id de la tuile
*/
void tuile_init_random(tuile *T, int id);


/**
* \brief Retourne un dictionnaire de tuile contenu dans un fichier
* \param fichier Le fichier contenant les tuiles
* \return Un type dicoTuiles correspondant aux tuiles contenues dans le fichier.
*/
dicoTuiles tuile_init_fichier(char *fichier);


/**
* \brief Tourne la tuile dans le sens d'une horloge de 90°.
* \details Incrémente le champ orientation de la tuile de 1 et 
* modifie les cases de la tuile selon le cas correspondant
* \attention T doit être initialisé avec la fonction tuile_init
* \param T Un pointeur vers une tuile.
*/
void tuile_rotation(tuile *T);


#endif
