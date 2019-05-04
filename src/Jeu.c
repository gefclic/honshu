#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Jeu.h"
#include "Grille.h"
#include "Tuiles.h"
#include "Affichage.h"


Deck Jeu_init_fichier(char *fichier, grilleDeJeu *laGrille){
	
	Deck J;
	FILE* F = NULL;
	F = fopen(fichier,"r");
	if (F == NULL){
		fprintf(stderr,"Jeu_init_fichier: pb ouverture %s\n", fichier);
		J.tailleDeck = -1;
		return J;
	}

	int i;
	fscanf(F, "%d %d\n", &laGrille->taille, &J.tailleDeck);


	/* Initialisation de la grille */
	grille_create(laGrille, J.tailleDeck);

	J.deckTuiles = (int *)malloc(J.tailleDeck * sizeof(int));
	for(i=0; i<J.tailleDeck; i++) {
		fscanf(F, "%d ", &J.deckTuiles[i]);
	}
	fscanf(F, "%d\n", &J.id_depart);

	fclose(F);
	return J;
}


void sauvegarde_deck(char* fichier, Deck D, grilleDeJeu g){
	int i;

	FILE* F = fopen(fichier,"w");
	if (F == NULL){
		fprintf(stderr,"sauvegarde_deck: pb ouverture %s\n", fichier);
		exit(1);
	}
	fprintf(F, "%d %d\n", g.taille, D.tailleDeck);
	for (i=0; i<D.tailleDeck; i++){
		fprintf(F, "%d ", D.deckTuiles[i]);
	}
	fprintf(F, "\n%d\n", D.id_depart);
	fclose(F);
}


void sauvegarde_dico(char* fichier, dicoTuiles D){
	int i, j;

	FILE* F = fopen(fichier,"w");
	if (F == NULL){
		fprintf(stderr,"sauvegarde_dico: pb ouverture %s\n", fichier);
		exit(1);
	}

	fprintf(F, "%d\n", D.taille);
	for (i=0; i<D.taille; i++){
		fprintf(F, "%d\n", D.leDico[i].id);
		while(D.leDico[i].orientation != 0){
			tuile_rotation(&D.leDico[i]);
		}
		for (j=0; j<3; j++){
			fprintf(F, "%c %c\n", D.leDico[i].contenu[0][j], D.leDico[i].contenu[1][j]);
		}
	}
	fclose(F);
}

int appartient_deck(int id, Deck D){
	int n = D.tailleDeck;
	int i;
	for(i = 0; i < n; i++) {
		if(id == D.deckTuiles[i])
			return i;
	}
	return -1;
}


int test_fin(Deck D, grilleDeJeu G, dicoTuiles dico, tuilePosee *Historique){
	int i,X,Y,orientation;
	int test = 0;
	tuile T;

	/* On test s'il reste des tuiles non posées dans le deck */
	for(i = 0; i < D.tailleDeck; i++) {
		if(Historique[D.deckTuiles[i]].X == -1){
			test=1;
			break;
		}
	}
	if (test == 0){
		return 0;
	}
	/* On test si aucune tuile ne peut être posée, on s'arrête dès qu'on trouve une tuile posable */
	for (i = 0; i < D.tailleDeck; i++){
		if (Historique[D.deckTuiles[i]].X == -1){
			T = dico.leDico[D.deckTuiles[i]];
			/* On doit tester pour les 4 orientations possibles */
			for (orientation=0; orientation<4; orientation++){
				while(T.orientation != orientation){
					tuile_rotation(&T);
				}

				for(X=0; X<G.taille;X++){
					for (Y=0; Y<G.taille; Y++){
						test = 1;
						if (T.orientation==0 || T.orientation==2){
							if(X>G.taille-2||Y>G.taille-3){
								test = 0;
							}
						}else{
							if(X>G.taille-3||Y>G.taille-2){
								test = 0;
							}
						}

						if (test && (neRecouvrePasTotalementUneTuile(G,T,X,Y)&&verifRecouvreUneTuile(G,T,X,Y)&&verifLac(G,T,X,Y))){
							return 1;
						}
					}
				}
			}
		}
	}
	return 0;
}


int ScoreForet(grilleDeJeu G) {
	int result = 0;
	int i, j;

	for(i = 0; i < G.taille; i++) {
		for(j = 0; j < G.taille; j++) {
			if(G.Grille[i][j].typeCase == 'F')
				result++;		
		}	
	}
	return (result*2);
}


int ScoreLac(grilleDeJeu G) {
	int result = 0;
	int i, j;
	for(i = 0; i < G.taille; i++) {
		for(j = 0; j < G.taille; j++) {
			if(G.Grille[i][j].typeCase == 'L')
				result++;		
		}	
	}
	return (result-1)*3;
}


int ScoreRess(grilleDeJeu G) {
	int result = 0;
	int i, j;
	int nbR = 0, nbU = 0; 
	for(i = 0; i < G.taille; i++) {
		for(j = 0; j < G.taille; j++) {
			if(G.Grille[i][j].typeCase == 'R')
				nbR++;
			else if(G.Grille[i][j].typeCase == 'U')
				nbU++;		
		}	
	}
	result = 4*((nbR<nbU) ? nbR : nbU);
	return result;
}


int ScoreVillage(grilleDeJeu laGrille , int X ,int Y,int parent) {
	
	int s=0;
	if (laGrille.Grille[X][Y].typeCase != 'V' || laGrille.Grille[X][Y].comptage==1 ){
		return 0;
	}
	else {
		s = 1;
		laGrille.Grille[X][Y].comptage=1;
		if (verifHorsTerrain(X-1,Y,laGrille)) {s = s + ScoreVillage(laGrille,X-1,Y,parent*5);}
		if (verifHorsTerrain(X+1,Y,laGrille)) {s = s + ScoreVillage(laGrille,X+1,Y,parent*3);}
		if (verifHorsTerrain(X,Y+1,laGrille)) {s = s + ScoreVillage(laGrille,X,Y+1,parent*11);}
		if (verifHorsTerrain(X,Y-1,laGrille)) {s = s + ScoreVillage(laGrille,X,Y-1,parent*7);}
	}
	return s;
}


int Score_plus_grand_village(grilleDeJeu laGrille){
	int s = 0;
	int s_en_cour = 0;
	int i,j;
	for (i = 0;i < laGrille.taille ; i++) {
		for(j = 0 ; j < laGrille.taille; j++){
			s_en_cour = ScoreVillage(laGrille,i,j,1);
			if (s < s_en_cour) {
				s = s_en_cour;
			}
		}
	}
	resetCompteurGrille(laGrille);
	return s;
}


int calculScore(grilleDeJeu G) {
	return ScoreForet(G)+ScoreLac(G)+ScoreRess(G)+Score_plus_grand_village(G);
}


int Honshu_Opt(grilleDeJeu G, Deck D, dicoTuiles Dico, tuilePosee *Historique){
	int i, X, Y, orientation;
	int test = 0;
	int Best, Tmp_Score;
	tuile T;

	/* S'il ne reste plus aucune tuiles dans le Deck */
	for(i = 0; i < D.tailleDeck; i++) {
		if(Historique[D.deckTuiles[i]].X == -1){
			test=1;
			break;
		}
	}
	if (test == 0){
		/*clrscr();
		Affiche_Deck(Dico, D, Historique);
		Affiche_Grille_Score_Regle(G, calculScore(G), 0);*/
		return calculScore(G);
	}
	Best = -1;
	/* On cherche une tuile non placée */
	for (i = 0; i < D.tailleDeck; i++){
		if (Historique[D.deckTuiles[i]].X == -1){
			T = Dico.leDico[D.deckTuiles[i]];

			/* On doit tester pour les 4 orientations possibles */
			for (orientation = 0; orientation < 4; orientation++){
				while(T.orientation != orientation){
					tuile_rotation(&T);
				}

				for(X=0; X<G.taille;X++){
					for (Y=0; Y<G.taille; Y++){
						if(PoserTuileAvecTest(&G, T, X, Y, Historique)){

							Tmp_Score = Honshu_Opt(G, D, Dico, Historique);

							if (Tmp_Score > Best){
								Best = Tmp_Score;
							}

							RetraitDerniereTuile(&G, D, Dico, Historique);
						}
					}
				}
			}
		}
	}
	return Best;
}


tuilePosee Solveur_tour(grilleDeJeu G, Deck D, dicoTuiles Dico, tuilePosee *Historique, int (*Calcul)(grilleDeJeu)){
	int i, X, Y, orientation;
	int Best, Tmp_Score;
	tuilePosee Res;
	tuile T;

	/* Le test de fin de partie est déjà réalisée avant l'appel à cette fonction */
	
	Best = -1;
	/* On cherche une tuile non placée */
	for (i = 0; i < D.tailleDeck; i++){
		if (Historique[D.deckTuiles[i]].X == -1){
			T = Dico.leDico[D.deckTuiles[i]];

			/* On doit tester pour les 4 orientations possibles */
			for (orientation = 0; orientation < 4; orientation++){
				while(T.orientation != orientation){
					tuile_rotation(&T);
				}

				for(X=0; X<G.taille;X++){
					for (Y=0; Y<G.taille; Y++){
						if(PoserTuileAvecTest(&G, T, X, Y, Historique)){
							Tmp_Score = (*Calcul)(G);
							if (Tmp_Score > Best){
								Best = Tmp_Score;
								Res.id = T.id;
								Res.X = X;
								Res.Y = Y;
								Res.orientation = orientation;
							}

							RetraitDerniereTuile(&G, D, Dico, Historique);
						}
					}
				}
			}
		}
	}
	
	return Res;
}


int Solveur_Heuristique(grilleDeJeu G, Deck D, dicoTuiles Dico, tuilePosee *Historique, int (*Calcul)(grilleDeJeu), int afficher){
	
	tuilePosee Best;
	tuile Current;
	int nbDeTuilePosee_initial = G.nbTuilePosees;

	while (test_fin(D, G, Dico, Historique)!=0){
		Best = Solveur_tour(G, D, Dico, Historique, *Calcul);
		Current = Dico.leDico[Best.id];
		while(Current.orientation != Best.orientation){
			tuile_rotation(&Current);
		}
		PoserTuileAvecTest(&G, Current, Best.X, Best.Y, Historique);
	}

	int Res = calculScore(G);
	if (afficher == 1){
		clrscr();
		afficheGrille(G);


		couleur("1");
		couleur("30;47");	
		printf("\n Estimation du meilleur score possible = %d \n", Res);
		couleur("0");
	}
	
	do{
		RetraitDerniereTuile(&G, D, Dico, Historique);
	}while(G.nbTuilePosees != nbDeTuilePosee_initial);

	return Res;
}


terrain maxTypeTerrain(Deck D, dicoTuiles Dico, tuilePosee *Historique){
	int i, j, k;

	terrain typeTerrains[5] = {Foret, Lac, Ville, Ressource, Usine};
	int nb[5] = {0};
	int maxIndex, max;

	/* Comptage des occurences dans le deck des tuiles disponibles */
	for(i=0; i<D.tailleDeck; i++){
		if (Historique[D.deckTuiles[i]].X == -1){
			for (j=0; j<2; j++){
				for (k=0; k<3; k++){
					switch(Dico.leDico[D.deckTuiles[i]].contenu[j][k]){
						case 'F':
							nb[0]++;
							break;
						case 'L':
							nb[1]++;
							break;
						case 'V':
							nb[2]++;
							break;
						case 'R':
							nb[3]++;
							break;
						case 'U':
							nb[4]++;
							break;
						default:
							break;
					}
				}
			}
		}
	}

	/* Recherche du max */
	maxIndex = 0;
	max = nb[maxIndex];
	for (i=0; i<5; i++){
		if (nb[i] > max){
			max = nb[i];
			maxIndex = i;
		}
	}

	for (j=0; j<5; j++){
		printf("%c : %d ; ", typeTerrains[j], nb[j]);
	}

	if (maxIndex == 3 || maxIndex == 4){
		if (abs(nb[3] - nb[4])>D.tailleDeck/10){
			maxIndex = 0;
			max = nb[maxIndex];
			for (i=0; i<3; i++){
				if (nb[i] > max){
					max = nb[i];
					maxIndex = i;
				}
			}
		}
	}

	return typeTerrains[maxIndex];
}


int solveurMaxTypeTerrain(grilleDeJeu *G, Deck D, dicoTuiles Dico, tuilePosee *Historique){
	terrain BestType = maxTypeTerrain(D, Dico,Historique);
	tuilePosee Best;
	
	switch (BestType){
		case 'V':
			Best = Solveur_tour(*G, D, Dico, Historique, Score_plus_grand_village);
			printf("Maximum du Village\n");
			break;
		case 'F':
			Best = Solveur_tour(*G, D, Dico, Historique, ScoreForet);
			printf("Maximum de Foret\n");
			break;
		case 'L':
			Best = Solveur_tour(*G, D, Dico, Historique, ScoreLac);
			printf("Maximum de Lac\n");
			break;
		case 'U':
			Best = Solveur_tour(*G, D, Dico, Historique, ScoreRess);
			printf("Maximum de Ressources et d'Usines\n");
			break;
		case 'R':
			Best = Solveur_tour(*G, D, Dico, Historique, ScoreRess);
			printf("Maximum de Ressources et d'Usines\n");
			break;
		default:
			return 0;
			break;
	}

	tuile Current = Dico.leDico[Best.id];
	while(Current.orientation != Best.orientation){
		tuile_rotation(&Current);
	}
	PoserTuileAvecTest(G, Current, Best.X, Best.Y, Historique);
	return 1;
}

/*
 * Renvoie 1 si n est présent dans T, 0 sinon
 */
int estPresent(int index, int *T, int n){
	int i;
	for (i=0; i<=index; i++){
		if (T[i] == n){
			return 1;
		}
	}
	return 0;
}

Deck deckRandomDico(dicoTuiles Dico, int tailleDeck){
	Deck D;
	
	D.tailleDeck = tailleDeck;
	D.deckTuiles = (int *)malloc(D.tailleDeck * sizeof(int));
	int i;
	D.id_depart = rand()%Dico.taille;
	int r;
	for(i=0; i<D.tailleDeck; i++) {
		r = rand()%Dico.taille;
		while (estPresent(i, D.deckTuiles, r) == 1){
			r = rand()%Dico.taille;
		}

		D.deckTuiles[i] = r;
	}

	/*for (i=0; i<D.tailleDeck; i++){
		printf("%d ->", D.deckTuiles[i]);
	}*/
	return D;
}
























