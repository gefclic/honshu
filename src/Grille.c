#include <stdio.h>
#include <stdlib.h> 

#include "Grille.h"
#include "Tuiles.h"
#include "Jeu.h"

#define clrscr() printf("\033[H\033[2J")
#define couleur(param) printf("\033[%sm",param)


void grille_create(grilleDeJeu *laGrille, int nbDeTuilesDuDeck){
	int i,j;
	laGrille->Grille = (laCase **)calloc(laGrille->taille, sizeof(laCase *));
	for (i=0; i<laGrille->taille; i++){
		laGrille->Grille[i] = (laCase *)calloc(laGrille->taille, sizeof(laCase));
	}
	for (i=0; i<laGrille->taille; i++){
		for (j=0; j<laGrille->taille; j++){
			laGrille->Grille[i][j].numeroTuile = -1;
			laGrille->Grille[i][j].typeCase = Vide;
			laGrille->Grille[i][j].comptage = 0;
		}	
	}
	laGrille->nbTuilePosees = 0;
	laGrille->tuilesDejaPosees = (int *)calloc(nbDeTuilesDuDeck, sizeof(int));
	for (i=0; i<nbDeTuilesDuDeck; i++){
		laGrille->tuilesDejaPosees[i] = -1;
	}
}


terrain lireCaseType (int x, int y, grilleDeJeu laGrille){
	return laGrille.Grille[x][y].typeCase;
}


int lireCaseNumeroTuile (int x, int y, grilleDeJeu laGrille){
	return laGrille.Grille[x][y].numeroTuile;
}


void resetCompteurGrille(grilleDeJeu laGrille){
	int i,j;
	for (i=0;i<laGrille.taille;i++){
		for (j=0;j<laGrille.taille;j++){
			laGrille.Grille[j][i].comptage=0;
		}
	}
}


void ChoixCoul(terrain leTerrain){
	switch(leTerrain){
		case 'E':
			couleur("30;47");
			break;
		case 'P':
			couleur("30;42");
			break;
		case 'F':
			couleur("30;43");
			break;
		case 'L':
			couleur("30;46");
			break;
		case 'V':
			couleur("37;40");
			break;
		case 'U':
			couleur("30;41");
			break;
		case 'R':
			break;
	}
}


void afficheGrille(grilleDeJeu laGrille){
	 // clrscr(); //Efface l'écran
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
		couleur("1");
		printf(" ");
		couleur("30;47");	
		printf("\n");
	}
	couleur("0");
}


int PoserTuile(grilleDeJeu laGrille, tuile laTuile, int X, int Y){
	int result =1;
	//On va d'abord verifier que l'on ne sort pas de la grille de jeu. Pour cela on a 2 case a traité : orientation 
	//verticale ou orientatin horizontale
	if (laTuile.orientation==0 || laTuile.orientation==2){
		if(X>laGrille.taille-1||Y>laGrille.taille-2){
			return 0;
		} 
	}else{
		if(X>laGrille.taille-2||Y>laGrille.taille-1){
			return 0;
		}
	}

	//ici on a fini tous les tests, on peut donc placer la tuile sur la grille
	if (result==1){
		int i,j;
		if (laTuile.orientation==0 || laTuile.orientation==2){
			//Tuile Vertical
			for(j=0;j<3;j++){
				for(i=0;i<2;i++){
					laGrille.Grille[X+i][Y+j].typeCase = laTuile.contenu[i][j];
					laGrille.Grille[X+i][Y+j].numeroTuile = laTuile.id;
				}
			}

		}else{
			//tuile horizontale
			for(j=0;j<2;j++){
				for(i=0;i<3;i++){
					laGrille.Grille[X+i][Y+j].typeCase = laTuile.contenu[i][j];
					laGrille.Grille[X+i][Y+j].numeroTuile = laTuile.id;
				}
			}

		}
	}
	return result;
}


int verifHorsTerrain(int x, int y, grilleDeJeu laGrille){
	if (x<0||y<0){
		return 0;
	}else if(x>laGrille.taille-1||y>laGrille.taille-1){
		return 0;
	}
	return 1;
}


int verifLac(grilleDeJeu laGrille, tuile laTuile, int X, int Y){
	//il faut faire le meme parcours que pour poser la tuile juste en vérifiant que ce n'est pas un lac
	int i,j;
	if (laTuile.orientation==0 || laTuile.orientation==2){
			//Tuile Vertical
		for(j=0;j<3;j++){
			for(i=0;i<2;i++){
				if(lireCaseType(X+i,Y+j,laGrille)=='L'){
				//	printf("Recouvrement d'un lac.\n");
					return 0;
				}	
			}
		}
	}else{
			//tuile Horizontale
		for(j=0;j<2;j++){
			for(i=0;i<3;i++){
				if(lireCaseType(X+i,Y+j,laGrille)=='L'){
				//	printf("Recouvrement d'un lac.\n");
					return 0;
				}
			}
		}

	}
	return 1;
}


int verifRecouvreUneTuile(grilleDeJeu laGrille, tuile laTuile, int X, int Y){
	//il faut faire le meme parcours que pour poser la tuile juste en vérifiant que tout n'est pas vide
	int i,j;
	if (laTuile.orientation==0 || laTuile.orientation==2){
			//Tuile Vertical
		for(j=0;j<3;j++){
			for(i=0;i<2;i++){
				if(lireCaseType(X+i,Y+j,laGrille)!='E'){
					return 1;
				}	
			}
		}
		
	}else{
			//tuile Horizontale
		for(j=0;j<2;j++){
			for(i=0;i<3;i++){
				if(lireCaseType(X+i,Y+j,laGrille)!='E'){
					return 1;
				}
			}
		}

	}
	//printf("Ne recouvre aucune case d'une tuile déjà posée.\n");
	return 0;
}


int neRecouvrePasTotalementUneTuile(grilleDeJeu laGrille, tuile laTuile, int X, int Y){
	int Xdeb,Ydeb,Xfin,Yfin,i,j;
	Xdeb = X-2;
	Ydeb = Y-2;
	int histogramme[100];
	/*Initialisation du tableau à -1*/
	for (i=0;i<100;i++){
		histogramme[i]=-1;
	}
	/*2 parcours Tuile Horizontal ou vertical */
	if(laTuile.orientation==0||laTuile.orientation==2){
		Xfin=Xdeb+6;
		Yfin=Ydeb+7;
	}else{
		Xfin=Xdeb+7;
		Yfin=Ydeb+6;
	}
	/*parcour du premier Histogramme */
	for(j=Ydeb;j<Yfin;j++){
		for(i=Xdeb;i<Xfin;i++){
			if(verifHorsTerrain(i,j,laGrille)){
				if(laGrille.Grille[i][j].typeCase!='E'){
					if(histogramme[laGrille.Grille[i][j].numeroTuile]==-1){
						histogramme[laGrille.Grille[i][j].numeroTuile]=1;
					}else{
						histogramme[laGrille.Grille[i][j].numeroTuile]++;
					}
				}
			}
			
		}
	}
	
	/*Fin du premier Histograme */
	/*On fait le deuxieme parcours */
	if (laTuile.orientation==0 || laTuile.orientation==2){
		//Tuile Vertical
		for(j=0;j<3;j++){
			for(i=0;i<2;i++){
				if(laGrille.Grille[X+i][Y+j].typeCase!='E'){
					histogramme[laGrille.Grille[X+i][Y+j].numeroTuile]--;
					if(histogramme[laGrille.Grille[X+i][Y+j].numeroTuile]==0){
						/*printf("Une tuile ne peut être complètement recouverte.\n");*/
						return 0;
					}

				}
			}
		}
		
	}else{
		//tuile horizontale
		for(j=0;j<2;j++){
			for(i=0;i<3;i++){
				if(laGrille.Grille[X+i][Y+j].typeCase!='E'){
					histogramme[laGrille.Grille[X+i][Y+j].numeroTuile]--;
					if(histogramme[laGrille.Grille[X+i][Y+j].numeroTuile]==0){
						/*printf("Une tuile ne peut être complètement recouverte.\n");*/
						return 0;
					}
				}
			}
		}
	}

	return 1;
}


int PoserTuileAvecTest(grilleDeJeu *laGrille, tuile laTuile, int X, int Y, tuilePosee *Historique){
//On va d'abord verifier que l'on ne sort pas de la grille de jeu. Pour cela on a 2 cas à traité : orientation 
	//verticale ou orientation horizontale
	
	if (laTuile.orientation==0 || laTuile.orientation==2){
		if(X>laGrille->taille-2||Y>laGrille->taille-3){
			return 0;
		} 
	}else{
		if(X>laGrille->taille-3||Y>laGrille->taille-2){
			return 0;
		}
	}
	if(neRecouvrePasTotalementUneTuile(*laGrille,laTuile,X,Y)&&verifRecouvreUneTuile(*laGrille,laTuile,X,Y)&&verifLac(*laGrille,laTuile,X,Y)){

		if (PoserTuile(*laGrille,laTuile,X,Y)){
			/* Sauvegarde des informations dans Historique */
			Historique[laTuile.id].X = X;
			Historique[laTuile.id].Y = Y;
			Historique[laTuile.id].orientation = laTuile.orientation;

			/* Sauvegarde des informations dans G */
			laGrille->tuilesDejaPosees[laGrille->nbTuilePosees] = laTuile.id;
			laGrille->nbTuilePosees++;

			return 1;
		}
	}
	return 0;
}


int RetraitDerniereTuile(grilleDeJeu *G, Deck D, dicoTuiles Dico, tuilePosee *Historique){
	
	int i,j;
	int currentID;
	tuile currentT;

	for (i=0; i<G->taille; i++){
		for (j=0;j<G->taille; j++){
			G->Grille[i][j].numeroTuile = -1;
			G->Grille[i][j].typeCase = Vide;
		}
	}

	/* On rejoue la tuile de départ */
	currentT = Dico.leDico[D.id_depart];
	tuile_rotation(&currentT);
	PoserTuile(*G, currentT, (G->taille)/2, (G->taille)/2);

	/* On rejoue toutes les tuiles sauf la dernière tuile posée */
	for (i=0; i<G->nbTuilePosees-1; i++){
		currentID = G->tuilesDejaPosees[i];
		currentT = Dico.leDico[currentID];

		while(currentT.orientation != Historique[currentID].orientation){
			tuile_rotation(&currentT);
		}

		PoserTuile(*G, currentT, Historique[currentID].X, Historique[currentID].Y);
	}

	Historique[G->tuilesDejaPosees[G->nbTuilePosees-1]].X = -1;
	G->tuilesDejaPosees[G->nbTuilePosees-1] = -1;
	G->nbTuilePosees--;
	
	return 1;
}




