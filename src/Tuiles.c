#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 
#include "Tuiles.h"


void tuile_print(tuile *T){
	int i,j;
	printf("Tuile n°%d\n", T->id);
	for (j=0; j<3; j++){
		for (i=0; i<3; i++){
			if (T->contenu[i][j] != 'E'){
				printf("%3c", T->contenu[i][j]);
			}
		}
		printf("\n");
	}
	printf("Orientation = %d\n\n", T->orientation);
}


void tuile_init(tuile *T, int id, char t1, char t2, char t3, char t4, char t5, char t6){
	int i;
	T->id = id;
	T->orientation = 0; 
	T->contenu[0][0] = t1;
	T->contenu[1][0] = t2;
	T->contenu[0][1] = t3;
	T->contenu[1][1] = t4;
	T->contenu[0][2] = t5;
	T->contenu[1][2] = t6;
	for (i=0; i<3; i++){
		T->contenu[2][i] = Vide;
	}
}


void tuile_init_random(tuile *T, int id){
	char C[] = "PFLVRU";
	tuile_init(T, id, C[rand()%6], C[rand()%6], C[rand()%6], C[rand()%6], C[rand()%6], C[rand()%6]);
}


dicoTuiles tuile_init_fichier(char *fichier){
	FILE* F = NULL;
	char chaine[6];	
	int i;
	int id;
	dicoTuiles D;

	F = fopen(fichier,"r");
	if (F == NULL){
		fprintf(stderr,"tuile_init_fichier: problème d'ouverture %s\n", fichier);
		D.taille = -1;
		return D;
	}

	
	
	if (fgets(chaine, 4, F) == NULL){
		fprintf(stderr,"tuile_init_fichier: problème lecture %s\n", fichier);
		D.taille = -1;
		return D;
	}
	D.taille = atoi(chaine);	
	D.leDico = (tuile *)malloc(D.taille * sizeof(tuile));

	for(i=0; i<D.taille; i++) {
		if (fscanf(F, "%d\n", &id) != 1){
			fprintf(stderr,"tuile_init_fichier: problème lecture %s\n", fichier);
			D.taille = -1;
			return D;
		}
		if (fscanf(F, "%c %c\n", &chaine[0], &chaine[1]) != 2){
			fprintf(stderr,"tuile_init_fichier: problème lecture %s\n", fichier);
			D.taille = -1;
			return D;
		}
		if (fscanf(F, "%c %c\n", &chaine[2], &chaine[3]) != 2){
			fprintf(stderr,"tuile_init_fichier: problème lecture %s\n", fichier);
			D.taille = -1;
			return D;
		}
		if (fscanf(F, "%c %c\n", &chaine[4], &chaine[5]) != 2){
			fprintf(stderr,"tuile_init_fichier: problème lecture %s\n", fichier);
			D.taille = -1;
			return D;
		}
		
		tuile_init(&D.leDico[i], id, chaine[0], chaine[1],chaine[2], chaine[3], chaine[4], chaine[5]);
	}
	fclose(F);
	return D;
}


void tuile_rotation(tuile *T){
	char Tampon[9];
	int i,j,k;
	k=0;
	//on charge dans un tableau de 9 char les valeurs de la tuile de départ
	for (j=0;j<3;j++){
		for(i=0;i<3;i++){
			Tampon[k]=T->contenu[i][j];
			k++;
		}
	}
	
	//2 cas a traités : Horizontal -> Vertical et inversement
	// premier cas vertical -> horizontal
	if (T->orientation==0 || T->orientation== 2){
		T->contenu[0][0]=Tampon[6];
		T->contenu[0][1]=Tampon[7];
		T->contenu[0][2]=Tampon[8];
		T->contenu[1][0]=Tampon[3];
		T->contenu[1][1]=Tampon[4];
		T->contenu[1][2]=Tampon[5];
		T->contenu[2][0]=Tampon[0];
		T->contenu[2][1]=Tampon[1];
		T->contenu[2][2]=Tampon[2];
	}else{
		T->contenu[0][0]=Tampon[3];
		T->contenu[1][0]=Tampon[0];
		T->contenu[2][0]=Tampon[6];
		T->contenu[0][1]=Tampon[4];
		T->contenu[1][1]=Tampon[1];
		T->contenu[2][1]=Tampon[7];
		T->contenu[0][2]=Tampon[5];
		T->contenu[1][2]=Tampon[2];
		T->contenu[2][2]=Tampon[8];
	}
	T->orientation++;
	if (T->orientation==4){
		T->orientation=0;
	}
} 

