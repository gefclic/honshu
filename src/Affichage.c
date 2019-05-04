#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 
#include <string.h> 
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#include "Affichage.h"
#include "Jeu.h"
#include "Tuiles.h"
#include "Grille.h"


void Affiche_Deck(dicoTuiles Dico, Deck D, tuilePosee *Historique){
	printf("\n");
	int i,j,k;
	int max, maxi_j;

	if (D.tailleDeck%8 != 0) max = D.tailleDeck%8;

	for(k=0; k<D.tailleDeck/8+1; k++){

		if(k==D.tailleDeck/8 && max!=0){
			maxi_j = 8*k+max;
		}
		else{
			maxi_j = 8*(k+1);
		}

		for (i=8*k; i<maxi_j; i++){ 
			if (Historique[D.deckTuiles[i]].X == -1){
				printf(" Tuile%2d|",D.deckTuiles[i]);
			}
		}
		printf("\n");
		for (i=0; i<3; i++){
			for (j=8*k; j<maxi_j; j++){
				if (Historique[D.deckTuiles[j]].X == -1){
					printf("  %2c%2c  |",Dico.leDico[D.deckTuiles[j]].contenu[0][i], Dico.leDico[D.deckTuiles[j]].contenu[1][i]);
				}
			}
			printf("\n");
		}
		printf("\n");
	}
	printf("\n");
}


void Affiche_Grille_Score_Regle(grilleDeJeu laGrille, int score, int h){
	int i,j,k;
	couleur("1");
	couleur("30;47");
	
	printf("\n  X");/* A MODIFIER CAR QUE POUR 0 à 99 là */
	for (k=0; k<laGrille.taille; k++){
		if (k/10>=1){
			printf("|%d",k/10);
		}
		else{
			printf("| ");
		}
	}

	printf("| ");
	printf("\n   ");
	for (k=0; k<laGrille.taille; k++){
		printf("|%d",k%10);
	}
	printf("| ");
	printf("\n");

	for (j=0;j<laGrille.taille;j++){
		if (j==0){
			printf("Y%2d", j);
		}
		else{
			printf("%3d", j);
		}
		for(i=0;i<laGrille.taille;i++){
			couleur("30;47");
			printf("|");
			ChoixCoul(laGrille.Grille[i][j].typeCase);
			if(laGrille.Grille[i][j].typeCase=='E'){
				printf("."); /* . au lieu d'un espace */
			}else{
				printf("%c",laGrille.Grille[i][j].typeCase);
			}
			couleur("30;47");
		}
		printf("|");
		printf(" ");

		/* TEST DE MODIF */
		couleur("0");
		printf("   ");
		couleur("1");
		couleur("30;47");	
		if (h==1){
		switch (j){
			case 0 : 
				printf("Rappel des moyens de gagner des points:                ");
				break;
			case 1 : 
				printf("-> (nombre de case ville du plus grand village) points.");
				break;
			case 2 : 
				printf("-> 2x (nombre de cases forêt) points.                  ");
				break;
			case 3 : 
				printf("-> 3x (nombre de cases Lac du lac -1) points.          ");
				break;
			case 4 : 
				printf("-> Un couple (R, U) = 4 points.                        ");
				break;	
			case 5:
				printf("Entrez <h> pour cacher l'aide.");
				break;
			case 7 : 
				printf(" Score : %d ", score);
				break;
			default:
				break;
		}
		}
		else{
			if (j==laGrille.taille/2-2){
				printf(" Entrez <h> pour afficher l'aide. ");
			}
			else if (j==laGrille.taille/2){
				printf(" Score : %d ", score);
			}
		}
		printf("\n");
	}
	couleur("0");
}


char getch(){
	char c;
	system("stty -echo");
	system("stty -icanon");
	c=getchar();
	system("stty icanon");
	system("stty echo");
	return c;
}


void boucle_principale(grilleDeJeu G, Deck D, dicoTuiles Dico){
	int x=-1, y=-1 ;
	char buf[50];
	int id = -1;
	int orientation = 0;
	char reponse = 'a', reponse2 = 'a';
	int appartient;
	tuile Current;
	int test; 
	int o = 0;
	unsigned int compteur = 0;
	int help = 0;
	int score = calculScore(G);
	tuilePosee *Historique = (tuilePosee *)malloc(Dico.taille*sizeof(tuilePosee));
	int i;
	for (i=0; i<Dico.taille; i++){
		Historique[i].X = -1; /* On initialise X à -1 : cela signifie que la tuile numéro i n'a pas été posée sur la grille */
	}
	int Solveur = 0;
	tuilePosee Best;

	/* Boucle principale */
	while (1){
		/*clrscr();
		Affiche_Deck(Dico, D);
		printf(" _______________________\n");
	    printf("|                       |\n");
	    printf("|   Score actuel : %d    |\n", score);
	    printf("|_______________________|\n");
		printf("Score actuel : %d\n", score);
		Affiche_Grille_Score_Regle(G, score);*/
		
		/* Initialisation des coordonnées */
		x = G.taille+1;
		y = G.taille+1;
		
		if (id != -1 ){
			Current = Dico.leDico[id];
			while (reponse != 'n' && reponse != 'y'){
				clrscr();
				Affiche_Deck(Dico, D, Historique);
				Affiche_Grille_Score_Regle(G, score, help);
				printf("\n");

				tuile_print(&Current);

				printf("Voulez-vous appliquer une rotation ? <y/n> ");
				reponse = getch();
				if (reponse == 'h'){
					help = help==1?0:1;
					continue;
				}
			}

			if (reponse == 'y'){
				do{
					clrscr();
					Affiche_Deck(Dico, D, Historique);
					Affiche_Grille_Score_Regle(G, score, help);

					printf("\n\nQuelle orientation ? <0, 1, 2, 3> Appuyer sur <q> ou <d> \n");
					tuile_print(&Current);
					o = getch();
					if (o == 'h'){
						help = help==1?0:1;
						continue;
					}
					if (o == 10){
						break;
					}
					switch (o){
						case 'd':
							if(orientation != 3){
								orientation++;
							}
							else{
								orientation = 0;
							}
							break;
						case 'q':
							if(orientation != 0){
								orientation--;
							}
							else{
								orientation = 3;
							}
							break;
						default :
							break;	
					}
					
					while(Current.orientation != orientation){
						tuile_rotation(&Current);
					}
				}while(1);
			}
			
			do{
				/* Si le message d'erreur s'affiche plusieurs fois */
				if (compteur == 3){
					compteur=0;
					clrscr();
					printf("\n");
					Affiche_Deck(Dico, D, Historique);
					Affiche_Grille_Score_Regle(G, score, help);
					printf("\n");
					tuile_print(&Current);
				}else{
					compteur++;
				}

				printf("\nOù voulez-vous la placer ?\n");
				printf("X = ");
				scanf("%d", &x);
				printf("Y = ");
				scanf("%d", &y);

				test = ( (verifHorsTerrain(x, y, G) == 0) || (PoserTuileAvecTest(&G, Current, x, y, Historique) == 0));

				if (test){ 
					printf("Impossible de poser la tuile en X=%d et Y=%d.\n", x, y);
				}
			}while(test);

			/* Réintialisation des variables */
			printf("\n");
			id = -1;
			reponse = 'a';
			orientation = 0;
			compteur = 0;
			x = -1;
			y = -1;
			score = calculScore(G);
			continue;
		}


		/* Début d'un tour */ 
		while (id == -1){

			/* Retrait de la dernière tuile */
			if (G.nbTuilePosees != 0){
				while(reponse != 'y' && reponse != 'n'){
					clrscr();
					Affiche_Deck(Dico, D, Historique);
					Affiche_Grille_Score_Regle(G, score, help);

					printf("Voulez-vous retirer la dernière tuile posée ? <y/n> ");
					scanf("%c", &reponse);
					if (reponse == 'h'){
						help = help==1?0:1;
						continue;
					}
				}
				if (reponse == 'y'){
					RetraitDerniereTuile(&G, D, Dico, Historique);
				}
				score = calculScore(G);
				reponse = 'a';
			}

			
			/* Test de fin de partie */
			if (test_fin(D, G, Dico, Historique)==0){
				printf("\n\nPlus aucune tuiles à placer. Veuillez appuyer sur une touche pour quitter la partie.");
				getch();
				getch();
				free(Historique);
				return;
			}

			/* SOLVEUR */
			while(reponse != 'y' && reponse != 'n'){
				clrscr();
				Affiche_Deck(Dico, D, Historique);
				Affiche_Grille_Score_Regle(G, score, help);
				printf("Voulez-vous afficher la solution d'un solveur ? <y/n> ");
				reponse = getch();
				if (reponse == 'h'){
					help = help==1?0:1;
					continue;
				}
				if (reponse == 'y'){
					while(reponse != '1' && reponse != '2' && reponse != '3'){
						clrscr();
						Affiche_Deck(Dico, D, Historique);
						Affiche_Grille_Score_Regle(G, score, help);
						printf("Veuillez selectionner un solveur :\n");
						printf("1 - Solveur global\n");
						printf("2 - Solveur global utilisant le solveur pour un tour\n");
						printf("3 - Solveur pour un tour\n\n");
						if (reponse == 'h'){
							help = help==1 ? 0 : 1;
						}
						reponse = getch();
					}
					switch (reponse){
						case '1':
							Solveur = Honshu_Opt(G, D, Dico, Historique);
							printf("\nMeileur score possible : %d\n", Solveur);
							break;
						case '2':
							while (reponse2 != '1' && reponse2 != '2' && reponse2 != '3' && reponse2 != '4' && reponse2 != '5' && reponse2 != '6'){
								clrscr();
								Affiche_Deck(Dico, D, Historique);
								Affiche_Grille_Score_Regle(G, score, help);
								printf("Solveur global utilisant le solveur pour un tour\n");
								printf("Choisissez ce que vous voulez maximiser :\n");
								printf("1 - Le score global\n");
								printf("2 - Les Villages\n");
								printf("3 - Les Forêts\n");
								printf("4 - Les Lacs\n");
								printf("5 - Les Ressources et les Usines\n");
								printf("6 - Afficher les scores avec chaque méthode et les nombres d'occurences de chaque type de terrains");
								reponse2 = getch();
							}

							switch (reponse2){
								case '1':
									Solveur_Heuristique(G, D, Dico, Historique, calculScore, 1);
									printf("Maximum du score global\n");
									break;
								case '2':
									Solveur_Heuristique(G, D, Dico, Historique, Score_plus_grand_village, 1);
									printf("Maximum de Villages\n");
									break;
								case '3':
									Solveur_Heuristique(G, D, Dico, Historique, ScoreForet, 1);
									printf("Maximum de Forêts\n");
									break;
								case '4':
									Solveur_Heuristique(G, D, Dico, Historique, ScoreLac, 1);
									printf("Maximum de Lacs\n");
									break;
								case '5':
									Solveur_Heuristique(G, D, Dico, Historique, ScoreRess, 1);
									printf("Maximum de Ressources et d'Usines\n");
									break;
								case '6':
									clrscr();	
									printf("\n\n");					
									printf("                           Score maximum = %d\n", Solveur_Heuristique(G, D, Dico, Historique, calculScore, 0));
									printf("         Score maximum avec les Villages = %d\n", Solveur_Heuristique(G, D, Dico, Historique, Score_plus_grand_village, 0));
									printf("           Score maximum avec les Forêts = %d\n", Solveur_Heuristique(G, D, Dico, Historique, ScoreForet, 0));
									printf("             Score maximum avec les Lacs = %d\n", Solveur_Heuristique(G, D, Dico, Historique, ScoreLac, 0));
									printf("Score maximum avec les Ressources+Usines = %d\n\n\n", Solveur_Heuristique(G, D, Dico, Historique, ScoreRess, 0));
									printf("\nType de terrains qui apparaît le plus dans le deck = %c\n", maxTypeTerrain(D, Dico, Historique));
							}
							reponse2 = 'a';
							break;
						case '3':
							Best = Solveur_tour(G, D, Dico, Historique, calculScore);
							Current = Dico.leDico[Best.id];
							while(Current.orientation != Best.orientation){
								tuile_rotation(&Current);
							}

							PoserTuileAvecTest(&G, Current, Best.X, Best.Y, Historique);
							clrscr();
							Affiche_Deck(Dico, D, Historique);
							Affiche_Grille_Score_Regle(G, calculScore(G), 0);
							printf("Meilleur action : Jouer la Tuile %d en X=%d , Y=%d avec l'orientation=%d\n\n", Best.id, Best.X, Best.Y, Best.orientation);
							reponse = 'a';
							while(reponse != 'y' && reponse != 'n'){
								printf("Voulez-vous jouer votre tour comme cela? <y/n> \n");
								reponse = getch();
								if (reponse == 'h'){
									help = help==1?0:1;
									continue;
								}
							}
							if (reponse == 'n'){
								RetraitDerniereTuile(&G, D, Dico, Historique);
							}
							else{
								score = calculScore(G);
							}
							break;
					}
					printf("\n\nAppuyer sur une touche pour continuer.");
					getch();
					reponse = 'a';
				}
			}
			reponse = 'a';

			clrscr();
			Affiche_Deck(Dico, D, Historique);
			Affiche_Grille_Score_Regle(G, score, help);

			/* SELECTION DE TUILE */
			printf("\nVeuillez selectionner une tuile : (q pour quitter)\n");
			scanf("%s", buf);

			if (strcmp(buf, "q") == 0){
				free(Historique);
				return;
			}
			else if (strcmp(buf, "h") == 0){
				help = help==1 ? 0 : 1;
				continue;
			}
			else{
				id = atoi(buf);
			}
			/* On test si l'id rentré est présent dans le deck */
			if((appartient=appartient_deck(id, D)) != -1){
				//D.deckTuiles[appartient] = -1;
				Historique[id].X = 0; /* Pour se souvenir que la tuile va être joué */
			}
			else{
				printf("L'id saisi n'est pas dans le deck.\n");
				id = -1;
			}
		}
	}
}


void jeu_fichier_random(){
	int i,j;

	/* Initialisation du dico */
	dicoTuiles Dico; 
	Dico.taille = -1;
	char entree[] = "000";
	while((atoi(entree)<= 0) || (atoi(entree)>= 100)){ /* Modifier pour lot D : 15*/
		clrscr();
		printf("                                                              \n");
		printf("                  *******************************             \n");
		printf("                  *       PARTIE ALÉATOIRE      *             \n");
		printf("                  *******************************             \n");
		printf("                                                              \n");
		printf("      Entrez la taille du deck souhaitée (entre 1 et 100): ");
		scanf("%s",entree);
	}
	Dico.taille = atoi(entree);
	Dico.taille++;
	Dico.leDico = (tuile *)malloc(Dico.taille * sizeof(tuile));
	for(i=0; i<Dico.taille; i++) {
		tuile_init_random(&Dico.leDico[i], i);
	}

	/* Initialisation du deck */
	Deck D;

	/* Il faut que la tuile de départ ne soit pas composée de 6 lacs */
	int test = 6;
	while (test==6){
		D.id_depart = rand()%Dico.taille;
		test = 0;
		for (i=0;i<2;i++){
			for (j=0;j<3;j++){
				if (Dico.leDico[D.id_depart].contenu[i][j] == 'L'){
					test++;
				}
			}
		}
	}

	D.tailleDeck = Dico.taille-1;
	D.deckTuiles = (int *)malloc(D.tailleDeck * sizeof(int));
	int k=0;
	for(i=0; i<Dico.taille; i++) {
		if (D.id_depart != i){
			D.deckTuiles[k] = i;
			k++;
		}
	}

	/*Initialisation de la grille */
	grilleDeJeu G;
	G.taille = 1;
	sprintf(entree,"0");
	while((atoi(entree)==0) || (atoi(entree) < 5) || (atoi(entree)> 100)){ /* Modifier pour lot D : 20*/
		clrscr();
		printf("                                                              \n");
		printf("                  *******************************             \n");
		printf("                  *       PARTIE ALÉATOIRE      *             \n");
		printf("                  *******************************             \n");
		printf("                                                              \n");
		printf("	                 Taille du deck = %d\n", D.tailleDeck);
		printf("\n	    Entrez la taille de la grille (entre 5 et 100): ");
		scanf("%s",entree);
	}
	printf("%d", atoi(entree));
	G.taille = atoi(entree);
	grille_create(&G,D.tailleDeck);

	/* Placement de la tuile de la tuile de départ */ 
	tuile TDepart = Dico.leDico[D.id_depart];
	tuile_rotation(&TDepart);
	PoserTuile(G, TDepart, (G.taille)/2, (G.taille)/2);


	char rep = 'a';
	while(rep != 'n' && rep != 'y'){
		clrscr();
		printf("                                                              \n");
		printf("                  *******************************             \n");
		printf("                  *       PARTIE ALÉATOIRE      *             \n");
		printf("                  *******************************             \n");
		printf("                                                              \n");
		printf("	                 Taille du deck = %d\n", D.tailleDeck);
		printf("    		    Taille de la grille =  %d\n", G.taille);
		printf("	      Voulez-vous lancer le mode solveur ? <y/n> ");
		rep = getch();
		printf("%c", rep);
	}

	if (rep == 'y'){
		mode_solveur(G, D, Dico);
	}
	else{
		boucle_principale(G, D, Dico);
	}

	clrscr();
	/* Sauvegarde du jeu */
	char reponse = 'a';
	printf("Voulez-vous sauvegarder le deck généré aléatoirement? <y/n> ");
	while (reponse != 'n' && reponse != 'y'){
		reponse = getch();
	}
	if (reponse == 'y'){
		char tmp[50];
		char FDeck[50]; /* On se limite à un nom de 50 lettres maximum */
		printf("\nDonner un nom de sauvegarde pour le Deck: ");
		scanf("%s", tmp);
		sprintf(FDeck, "./sauvegardes/Partie%s.txt", tmp);
		sauvegarde_deck(FDeck, D, G);

		char FDico[50];
		printf("Donner un nom de sauvegarde pour le dictionnaire de tuiles : ");
		scanf("%s", tmp);
		sprintf(FDico, "./sauvegardes/Tuiles%s.txt", tmp);
		sauvegarde_dico(FDico, Dico);
	}

	/* Libération mémoire pour grille */
	for(i=0; i<G.taille; i++){
		free(G.Grille[i]);
	}
	free(G.Grille);
	free(G.tuilesDejaPosees);
	/* Libération mémoire pour Dico */
	free(Dico.leDico);
	/* Libération de la mémoire pour le Deck */
	free(D.deckTuiles);

}


void jeu_fichier(){

	char tmp[50];
	char FDico[100];
	char FPartie[100];
	char rep = 'r';
	dicoTuiles Dico ;
	Dico.taille = -1;
	grilleDeJeu G;
	Deck D;
	D.tailleDeck = -1;


	while(rep != 'n' && rep != 'y'){
		clrscr();
		printf("                                                              \n");
		printf("                  *******************************             \n");
		printf("                  *      PARTIE PRÉDÉFINIE      *             \n");
		printf("                  *******************************             \n");
		printf("                                                              \n");
		printf("      	Voulez-vous choisir un deck préconçu au hasard ? <y/n> ");
		rep = getch();
		printf("%c", rep);
	}
	switch (rep){
		case 'y':
			sprintf(FDico, "./sauvegardes/Tuiles.txt");
			sprintf(FPartie, "./sauvegardes/Partie2.txt");
			Dico = tuile_init_fichier(FDico);
			D = Jeu_init_fichier(FPartie, &G);
			break;
		case 'n':
			printf("\n\nVeuillez saisir le fichier contenant un dictionnaire de tuiles parmi les suivants (ex : Tuiles):\n\n");
				system("find ./sauvegardes -name Tuiles*");
			while (Dico.taille == -1){
				
				printf("\nMon choix : ");
				scanf("%s", tmp);
				sprintf(FDico, "./sauvegardes/%s.txt", tmp);
				Dico = tuile_init_fichier(FDico);
			}
			printf("\nVeuillez saisir le fichier d'un Deck de Honshu parmi les suivants : (ex : Partie1)\n\n");
			system("find ./sauvegardes -name Partie*");

			while(D.tailleDeck == -1){
				printf("\nMon choix : ");
				scanf("%s", tmp);
				sprintf(FPartie, "./sauvegardes/%s.txt", tmp);
				D = Jeu_init_fichier(FPartie, &G);
			}
			
			break;
	}
	
	

	tuile TDepart = Dico.leDico[D.id_depart];
	tuile_rotation(&TDepart);
	PoserTuile(G, TDepart, (G.taille)/2, (G.taille)/2);

	rep = 'a';
	while(rep != 'n' && rep != 'y'){
		clrscr();
		printf("                                                              \n");
		printf("                  *******************************             \n");
		printf("                  *      PARTIE PRÉDÉFINIE      *             \n");
		printf("                  *******************************             \n");
		printf("                                                              \n");
		printf("      	Voulez-vous choisir un deck préconçu au hasard ? <y/n> \n\n");
		printf("	      Voulez-vous lancer le mode solveur ? <y/n> ");
		rep = getch();
		printf("%c", rep);
	}

	if (rep == 'y'){
		mode_solveur(G, D, Dico);
	}
	else{
		boucle_principale(G, D, Dico);
	}

	/* Libération mémoire pour grille */
	int i;
	for(i=0; i<G.taille; i++){
		free(G.Grille[i]);
	}
	free(G.Grille);
	free(G.tuilesDejaPosees);
	/* Libération mémoire pour Dico */
	free(Dico.leDico);
	/* Libération de la mémoire pour le Deck */
	free(D.deckTuiles);
}


void mode_solveur(grilleDeJeu G, Deck D, dicoTuiles Dico){
	char reponse = 'a', reponse2 = 'a';
	int help = 1;
	tuile Current;
	int score = calculScore(G);
	tuilePosee *Historique = (tuilePosee *)malloc(Dico.taille*sizeof(tuilePosee));
	int i;
	for (i=0; i<Dico.taille; i++){
		Historique[i].X = -1; /* On initialise X à -1 : cela signifie que la tuile numéro i n'a pas été posée sur la grille */
	}
	int Solveur = 0;
	tuilePosee Best;
	char quitter = 'a';


	/* Boucle principale */
	while (1){

		/* SOLVEUR */
		while(reponse != '1' && reponse != '2' && reponse != '3'){
			clrscr();
			Affiche_Deck(Dico, D, Historique);
			Affiche_Grille_Score_Regle(G, score, help);
			printf("Veuillez selectionner un solveur : \n");
			printf("1 - Solveur global\n");
			printf("2 - Solveur global utilisant le solveur pour tour\n");
			printf("3 - Solveur pour un tour (Maximisant le score global)\n\n");
			printf("q - Quitter\n");

			reponse = getch();
			if (reponse == 'q'){
				free(Historique);
				return;
			}
			if (reponse == 'h'){
				help = help==1 ? 0 : 1;
			}
		}
		switch (reponse){
			case '1':
				Solveur = Honshu_Opt(G, D, Dico, Historique);
				printf("\nMeileur score possible : %d\n", Solveur);
				break;
			case '2':
				while (reponse2 != '1' && reponse2 != '2' && reponse2 != '3' && reponse2 != '4' && reponse2 != '5' && reponse2 != '6'){
					clrscr();
					Affiche_Deck(Dico, D, Historique);
					Affiche_Grille_Score_Regle(G, score, help);
					printf("Solveur global utilisant le solveur pour tour\n");
					printf("Choisissez ce que vous voulez maximiser :\n");
					printf("1 - Le score global\n");
					printf("2 - Les Villages\n");
					printf("3 - Les Forêts\n");
					printf("4 - Les Lacs\n");
					printf("5 - Les Ressources et les Usines\n");
					printf("6 - Afficher les scores avec chaque méthode");
					reponse2 = getch();
				}

				switch (reponse2){
					case '1':
						Solveur_Heuristique(G, D, Dico, Historique, calculScore, 1);
						printf("Maximum du score global\n");
						break;
					case '2':
						Solveur_Heuristique(G, D, Dico, Historique, Score_plus_grand_village, 1);
						printf("Maximum de Villages\n");
						break;
					case '3':
						Solveur_Heuristique(G, D, Dico, Historique, ScoreForet, 1);
						printf("Maximum de Forêts\n");
						break;
					case '4':
						Solveur_Heuristique(G, D, Dico, Historique, ScoreLac, 1);
						printf("Maximum de Lacs\n");
						break;
					case '5':
						Solveur_Heuristique(G, D, Dico, Historique, ScoreRess, 1);
						printf("Maximum de Ressources et d'Usines\n");
						break;
					case '6':
						clrscr();	
						printf("\n\n");					
						printf("                           Score maximum = %d\n", Solveur_Heuristique(G, D, Dico, Historique, calculScore, 0));
						printf("         Score maximum avec les Villages = %d\n", Solveur_Heuristique(G, D, Dico, Historique, Score_plus_grand_village, 0));
						printf("           Score maximum avec les Forêts = %d\n", Solveur_Heuristique(G, D, Dico, Historique, ScoreForet, 0));
						printf("             Score maximum avec les Lacs = %d\n", Solveur_Heuristique(G, D, Dico, Historique, ScoreLac, 0));
						printf("Score maximum avec les Ressources+Usines = %d\n", Solveur_Heuristique(G, D, Dico, Historique, ScoreRess, 0));
				}
				reponse2 = 'a';
				break;
			case '3':
				while (quitter != 'q'){
					/* Test de fin de partie */
					if (test_fin(D, G, Dico, Historique)==0){
						printf("\nPlus aucune tuiles à placer. Veuillez appuyer sur une touche pour quitter la partie.");
						getch();
						getch();
						free(Historique);
						return;
					}
					Best = Solveur_tour(G, D, Dico, Historique, calculScore);
					Current = Dico.leDico[Best.id];
					while(Current.orientation != Best.orientation){
						tuile_rotation(&Current);
					}

					PoserTuileAvecTest(&G, Current, Best.X, Best.Y, Historique);
					clrscr();
					Affiche_Deck(Dico, D, Historique);
					Affiche_Grille_Score_Regle(G, calculScore(G), help);
					printf("Meilleur action : Jouer la Tuile %d en X=%d , Y=%d avec l'orientation=%d\n\n", Best.id, Best.X, Best.Y, Best.orientation);
					reponse = 'a';
					score = calculScore(G);

					printf("Appuyer sur Espace pour continuer le solveur (q pour quitter ce solveur)");
					quitter = getch();
				}
			break;
		}
		printf("\n\nAppuyer sur une touche pour continuer.");
		getch();
		quitter = 'a';
		reponse = 'a';
	}
}


