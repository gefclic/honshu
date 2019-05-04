#ifndef HONSHUSDL_H
#define HONSHUSDL_H
#include <SDL/SDL.h>
#include "structures.h"

/**
* \file HonshuSDL.h
*
* Ce fichier décrit l'ensemble des fonctions pour l'interface graphique du Honshu. Il contient 12 fonctions.
* -\b locationSouris permet de savoir sur quelle partie de la fenêtre on a cliqué.
* -\b pause permet de sauvegarder un Deck dans un fichier texte.
* -\b EcranTitre permet d'afficher l'écran d'accueil du jeu.
* -\b quitSDL permet de quitter la partie.
* -\b afficheTuileSDL permet d'afficher une tuile sur l'écran.
* -\b afficheDeckSDL permet d'afficher le deck sur la fenêtre
* -\b afficheTxt permet afficher toute la partie de droite de la fenêtre durant une partie.
* -\b afficheGrilleD permet afficher toute la partie de droite de la fenêtre durant une partie.
* -\b afficheDeckPleinEcran permet d'afficher le deck en plein écran
* -\b FindePartie permet d'afficher l'écran de fin de partie.
* -\b sourisDansGrille permet de vérifier que la souris est bien dans grille et de connaître la case cliquée.
* -\b gereOrientation permet de gérer l'orientation de la tuile dans la grille.
*/


/**
* \brief Détermine la partie de la fenêtre sur laquelle on a cliqué
* \details Initialise la taille de la grille et la grille
* \param pos Un tableau d'entiers contenant les coordonnées du clic
* \return Renvoie un entier correspondant à une partie de la fenêtre
*/
int locationSouris(int pos[]);



int pause(int pos[]);


/**
* \brief Affiche le premier écran correspondant au menu
* \param ecran Un pointeur SDL_Surface
* \return Renvoie un entier correspondant au choix effectué
*/
int EcranTitre(SDL_Surface *ecran);


/**
* \brief Quitte la partie.
*/
void quitSDL();

/**
* \brief Affiche le premier écran correspondant au menu
* \param ecran Un pointeur SDL_Surface
* \return Renvoie un entier correspondant au choix effectué
*/
void menuDebutPartie(SDL_Surface *ecran, int result[]);


/**
* \brief Affiche une tuile sur l'écran.
* \param ecran Un pointeur SDL_Surface
* \param x et y Entiers correspondant aux coordonnées
* \param T la Tuile à afficher
*/
void afficheTuileSDL(SDL_Surface *ecran, int x, int y, tuile T);


/**
* \brief Affiche le deck sur la fenêtre.
* \param ecran Un pointeur SDL_Surface
* \param Dico un dicoTuiles
* \param D un Deck
* \param Historique un talbeau d'entiers
* \param IdTuileEnCour l'id de la tuile qui est affiché
*/
void afficheDeckSDL(SDL_Surface *ecran, dicoTuiles Dico, Deck D, tuilePosee *Historique, int IdTuileEnCour);


/**
* \brief Affiche toute la partie de droite de la fenêtre durant une partie.
* \param ecran Un pointeur SDL_Surface
* \param G une grilleDeJeu
* \param vie un entier
* \param Etat un entier 
*/
void afficheTxt(SDL_Surface *ecran, grilleDeJeu G, int vie, int Etat);


/**
* \brief Affiche la grille de jeu sur la fenêtre.
* \param ecran Un pointeur SDL_Surface
* \param G une grilleDeJeu
*/
void afficheGrilleD(SDL_Surface *ecran, grilleDeJeu G);


/**
* \brief Affiche le deck sur tout l'écran
* \param ecran Un pointeur SDL_Surface
* \param D un Deck
* \param Dico un dicoTuiles
* \param Historique un talbeau d'entiers
*/
void afficheDeckPleinEcran(SDL_Surface *ecran,Deck D, dicoTuiles Dico, tuilePosee *Historique);


/**
* \brief Affiche l'écran de fin de partie
* \param ecran Un pointeur SDL_Surface
* \param score un entier
*/
void FindePartie(SDL_Surface *ecran, int score);


/**
* \brief Vérifie que la position cliquée est bien dans la grille 
* \details stock dans pos la position x et y de la case de la grille
* \param pos un talbeau d'entiers 
* \param G une grilleDeJeu
*/
void sourisDansGrille(int pos[], grilleDeJeu G);


/**
* \brief Cette fonction permet de gérer l'orientation de la tuile lorsqu'on la pose sur la grille
* \param G une grilleDeJeu
* \param T une tuile
* \param Coord un tableau d'entier correspondant aux coordonnées de la grille
*/
void gereOrientation(grilleDeJeu G, tuile T,int Coord[]);


int PremierCarteDeck(Deck D, tuilePosee *Historique, int idTuile);
int DerniereCarteDeck(Deck D, tuilePosee *Historique, int indexTuile);
int premiereCarteAvant(Deck D, tuilePosee *Historique, int idTuile);
int premiereCarteApres(Deck D, tuilePosee *Historique, int idTuile);


int numeroTuileSelectionner(int idIndex, Deck D);
void afficheTraitDelimitation(SDL_Surface *ecran);
void verifSiPossiblePourVoyant(grilleDeJeu G, tuile T, int X, int Y, int TabResult[]);
void AfficheVoyant(SDL_Surface *ecran, grilleDeJeu G,tuile T, int X, int Y, int Etat);

int RentreDansLaGrille(grilleDeJeu G, int X, int Y, tuile T);
int verifSiPossible(grilleDeJeu G, tuile T, int X, int Y);
void afficeSiPossible(SDL_Surface *ecran, grilleDeJeu G, tuile T, int X, int Y);
int VerifieDerniereTuile(Deck D, tuilePosee *Historique);
void mainSDL();




#endif