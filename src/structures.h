#ifndef STRUCTURES_H
#define STRUCTURES_H

/**
* \file structures.h
* 
* Ce fichier décrit l'ensemble des structures utilisées pour la réalisation du jeu de Honshu. Il comprend 6 types.
*/


/**
* \typedef terrain
* Type représentant le type d'une case du plateau ou d'une tuile.
*/
typedef enum {
	Vide = 'E', /**< Empty : case vide */
	Plaine = 'P', /**< Plaine */
	Foret = 'F', /**< Forêt */
	Lac = 'L', /**< Lac */
	Ville = 'V', /**< Ville */
	Ressource = 'R', /**< Ressource */
	Usine = 'U'/**< Usine */
} terrain;


/**
* \typedef tuile
* Type représentant une tuile.
*/
typedef struct {
	int id; /**< ID de la tuile */
    terrain contenu[3][3]; /**< Cases de la tuile */
	int orientation; /**< Orientation de la tuile : 0, 1, 2, 3 */
} tuile;


/**
* \typedef dicoTuile
* Type représentant un dictionnaire de tuiles
*/
typedef struct {
	int taille; /**< Taille du dictionnaire */
    tuile* leDico; /**< Tableau de Tuiles */
} dicoTuiles;


/**
* \typedef laCase
* Type représentant une case de la grille.
*/ 
typedef struct {
    int numeroTuile; /**< Numéro de la tuile posée sur la case, -1 sinon */
	int comptage; /**< Va servir aux algos de comptage de village */
    terrain typeCase; /**< Type de terrain sur la case actuel*/
} laCase;


/**
* \typedef grilleDeJeu
* Type représantant une grille de jeu.
*/
typedef struct {
	int taille; /**< Taille de la grille */
	laCase **Grille; /**< Tableau à 2 dimensions de type laCase représentant la grille de jeu */
	int nbTuilePosees; /**< Nombres de tuiles posées sur la grille. Cela va permetre de faire du rollBack. */
	int *tuilesDejaPosees; /**< Tableau d'entier contenant les IDs des tuiles posées sur la grille */
} grilleDeJeu;


/**
* \typedef Deck
* Type représentant une partie de Honshu
*/
typedef struct {
	int tailleDeck; /**< Entier correspondant au nombre de tuiles restant dans le deck du joueur */
	int *deckTuiles; /**< Tableau d'entier correspodant aux IDs des tuiles que possède le joueur */
	int id_depart; /**< ID de la tuile pré-placée sur le terrain de jeu */
} Deck;


/**
* \typedef tuilePosee
* Type représentant une tuile posée sur la grille
*/
typedef struct {
	int id; /**< id de la tuile */
	int X; /**< Coordonnée */
	int Y; /**< Coordonnée */
	int orientation; /**< Orientation de la tuile posée */
} tuilePosee;

#endif
