#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 

#include "Tuiles.h"
#include "Grille.h"
#include "Jeu.h"
#include "Affichage.h"
#include "HonshuSDL.h"


int main(){
    srand (time (NULL)); /* pour random */
	printf("\n");
	printf("\n");
	
	unsigned int choix = 0;

	while(1){
		clrscr();
		printf("       ________________________________________________________\n");
	    printf("      |                                                        |\n");
	    printf("      |            *******************************             |\n");
	    printf("      |            * BIENVENUE SUR LE JEU HONSHU *             |\n");
	    printf("      |            *******************************             |\n");
	    printf("      |                                                        |\n");
	    printf("      |         [1] Lancer une partie (deck aléatoire)         |\n");
	    printf("      |         [2] Lancer une partie (deck préconçu)          |\n");
	    printf("      |         [3] Jeu Graphique                              |\n");
	    printf("      |         [4] Crédits                                    |\n");
	    printf("      |         [5] Quitter                                    |\n");
	    printf("      |________________________________________________________|\n\n");

		choix = getch();
		switch(choix){
			case '1': 
				jeu_fichier_random();
				choix = -1;
				continue;

			case '2':
				jeu_fichier();
				choix = -1;
				continue;

			case '4':
				clrscr();
				printf("       ________________________________________________________\n");
				printf("      |                                                        |\n");
				printf("      |                    ***************                     |\n");
				printf("      |                    *   CRÉDITS   *                     |\n");
				printf("      |                    ***************                     |\n");
				printf("      |                                                        |\n");
				printf("      |                                                        |\n");
				printf("      |               DEVELOPPEURS : StrangerC                 |\n");
				printf("      |                                                        |\n");
				printf("      |                                                        |\n");
				printf("      |                   © StrangerC 2018                     |\n");
	  			printf("      |                                                        |\n");
				printf("      |     Appuyer sur une touche pour retourner au menu      |\n");
				printf("      |________________________________________________________|\n");
				getch();
				continue;

			case '5':
			    clrscr();
				printf("       ________________________________________________________\n");
				printf("      |                                                        |\n");
		        printf("      |                    * AU REVOIR ! *                     |\n"); 
		        printf("      |                                                        |\n");
		        printf("      |                                                        |\n");
		        printf("      |                                                        |\n");
		        printf("      |                                                        |\n");
		        printf("      |                                                        |\n");
		        printf("      |________________________________________________________|\n\n");
		        return 0;
		        break;
			case '3':
				mainSDL();
				break;
			case '6':
				
				break;
			default:
				continue;
		}
	}

	return 0;
}