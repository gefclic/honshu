#include <stdio.h>
#include <stdlib.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../src/Tuiles.h"
#include "../src/Grille.h"
#include "../src/Jeu.h"

/* Pointer to the file used by the tests. */
static FILE* temp_file = NULL;

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite(void)
{
   if (NULL == (temp_file = fopen("tests/temp.txt", "w+"))) {
      return -1;
   }
   else {
      return 0;
   }
}


/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite(void)
{
   if (0 != fclose(temp_file)) {
      return -1;
   }
   else {
      temp_file = NULL;
      return 0;
   }
}


/*
* Teste l'égalité entre deux tuiles : renvoie 1 si on a égalité,0 sinon.
*/
int testTuileEgale(tuile* a, tuile* b){
    int i,j;

    if (a->id != b->id){
        return 0;
    }

    if (a->orientation != b->orientation) {
        return 0;
    }
    else{
        for (j=0;j<3;j++){
            for(i=0;i<3;i++){
                if (a->contenu[i][j] != b->contenu[i][j]){
                    return 0;
                }
            }
        }
    }
    return 1;
}


/*
* Test l'égalité entre deux grilles : renvoie 1 si elles sont égales, 0 sinon.
*/
int Compare_Grille(grilleDeJeu a ,grilleDeJeu b){
    int i,j;

    if (a.taille != b.taille) {
        return 0;
    }

    if (a.nbTuilePosees != b.nbTuilePosees) {
        return 0;
    }

    for (j = 0;j < a.taille;j++){
        for(i=0; i < a.taille ; i++){
            if ( a.Grille[i][j].typeCase != b.Grille[i][j].typeCase)
        return 0;
        }
    }

    return 1;
}


/*
* Test l'initialisation d'une tuile
*/
void test_init_tuile(){
    tuile a,b;

    b.id = 0;
    b.orientation = 0;
    b.contenu[0][0] ='P';
    b.contenu[1][0] = 'F';
    b.contenu[2][0] = 'E';
    b.contenu[0][1] = 'L';
    b.contenu[1][1] = 'V';
    b.contenu[2][1] = 'E';
    b.contenu[0][2] = 'R';
    b.contenu[1][2] = 'U';
    b.contenu[2][2] = 'E';

    tuile_init(&a, 0, 'P', 'F', 'L', 'V', 'R', 'U');
    CU_ASSERT(testTuileEgale(&a, &b)==1);
}


/*
* Test de la fonction tuile_init_random
*/
void test_tuileRandom(){
    tuile a, b;
    tuile_init_random(&a, 1);
    tuile_init_random(&b, 2);
    CU_ASSERT(testTuileEgale(&a,&b) != 1);
}

/*
* Test de la fonction tuile_init_fichier
*/
void test_tuile_init_fichier(){
    dicoTuiles D = tuile_init_fichier("tests/Tuiles.txt");
    tuile a,b;
    tuile_init(&a, 0, 'U', 'F', 'R', 'P', 'V', 'V');
    tuile_init(&b, 1, 'P', 'F', 'V', 'V', 'V', 'U');

    int test = 1;
    if (D.taille != 2)
        test = 0;
    if (testTuileEgale(&D.leDico[0], &a) != 1)
        test = 0;
    if(testTuileEgale(&D.leDico[1], &b) != 1)
        test = 0;

    CU_ASSERT(test == 1);
}


/*
* Teste si la rotation d'une tuile est bien réalisée, dans les 4 cas d'orientations
*/
void test_rotation(){
    tuile a,b,c,d,e;

    a.id = 0;
    a.orientation = 0;
    a.contenu[0][0] ='V';
    a.contenu[1][0] = 'V';
    a.contenu[2][0] = 'E';
    a.contenu[0][1] = 'F';
    a.contenu[1][1] = 'P';
    a.contenu[2][1] = 'E';
    a.contenu[0][2] = 'U';
    a.contenu[1][2] = 'L';
    a.contenu[2][2] = 'E';

    b.id = 0;
    b.orientation = 1;
    b.contenu[0][0] = 'U';
    b.contenu[1][0] = 'F';
    b.contenu[2][0] = 'V';
    b.contenu[0][1] = 'L';
    b.contenu[1][1] = 'P';
    b.contenu[2][1] = 'V';
    b.contenu[0][2] = 'E';
    b.contenu[1][2] = 'E';
    b.contenu[2][2] = 'E';

    c.id = 0;
    c.orientation = 2;
    c.contenu[0][0] = 'L';
    c.contenu[1][0] = 'U';
    c.contenu[2][0] = 'E';
    c.contenu[0][1] = 'P';
    c.contenu[1][1] = 'F';
    c.contenu[2][1] = 'E';
    c.contenu[0][2] = 'V';
    c.contenu[1][2] = 'V';
    c.contenu[2][2] = 'E';

    d.id = 0;
    d.orientation = 3;
    d.contenu[0][0] = 'V';
    d.contenu[1][0] = 'P';
    d.contenu[2][0] = 'L';
    d.contenu[0][1] = 'V';
    d.contenu[1][1] = 'F';
    d.contenu[2][1] = 'U';
    d.contenu[0][2] = 'E';
    d.contenu[1][2] = 'E';
    d.contenu[2][2] = 'E';

    e.id = 0;
    e.orientation = 0;
    e.contenu[0][0] ='V';
    e.contenu[1][0] = 'V';
    e.contenu[2][0] = 'E';
    e.contenu[0][1] = 'F';
    e.contenu[1][1] = 'P';
    e.contenu[2][1] = 'E';
    e.contenu[0][2] = 'U';
    e.contenu[1][2] = 'L';
    e.contenu[2][2] = 'E';

    tuile_rotation(&a);
    CU_ASSERT(testTuileEgale (&a,&b)==1);
    tuile_rotation(&a);
    CU_ASSERT(testTuileEgale (&a,&c)==1);
    tuile_rotation(&a);
    CU_ASSERT(testTuileEgale (&a,&d)==1);
    tuile_rotation(&a);
    CU_ASSERT(testTuileEgale (&a,&e)==1);

}


/*
* Test la fonction lireCaseType
*/
void test_LireCaseType() {
    grilleDeJeu g;
    g.taille = 3;
    grille_create(&g, 5); /* 5 est arbitraire */
    g.Grille[0][0].typeCase = Vide;
    g.Grille[0][1].typeCase = Plaine;
    g.Grille[0][2].typeCase = Foret;
    g.Grille[1][0].typeCase = Lac;
    g.Grille[1][1].typeCase = Ville;
    g.Grille[1][2].typeCase = Ressource;
    g.Grille[2][0].typeCase = Usine;

    CU_ASSERT(lireCaseType(0, 0, g) == Vide);
    CU_ASSERT(lireCaseType(0, 1, g) == Plaine);
    CU_ASSERT(lireCaseType(0, 2, g) == Foret);
    CU_ASSERT(lireCaseType(1, 0, g) == Lac);
    CU_ASSERT(lireCaseType(1, 1, g) == Ville);
    CU_ASSERT(lireCaseType(1, 2, g) == Ressource);
    CU_ASSERT(lireCaseType(2, 0, g) == Usine);

    /* Libération de la mémoire allouée pour g */
    int i;
    for(i=0; i<g.taille; i++)
        free(g.Grille[i]);
    free(g.Grille);
    free(g.tuilesDejaPosees);
}


/*
* Test la fonction lireCaseNumeroTuile
*/
void test_lireCaseNumeroTuile() {
    grilleDeJeu g;
    g.taille = 3;
    grille_create(&g,5);
    g.Grille[0][1].numeroTuile = 10;

    CU_ASSERT(lireCaseNumeroTuile(0, 1, g) == 10);
}


/*
* Fonction pour vérifier qu'une grille est bien initialisée.
*/
int test_grille_init(grilleDeJeu a, int nbTuilesDeck) {
    int i, j;

    for(i= 0; i<a.taille; i++) {
        for(j=0; j< a.taille; j++){
            if(a.Grille[i][j].typeCase != Vide || a.Grille[i][j].numeroTuile != -1)
                return 0;
        }
    }

    if (a.nbTuilePosees != 0)
        return 0;

    for(i= 0; i<nbTuilesDeck; i++) {
        if(a.tuilesDejaPosees[i] != -1)
            return 0;
    }

    return 1;
}


/*
* Test de la fonction grille_create
*/
void test_grilleCreate() {
    grilleDeJeu g;
    g.taille = 6;

    grille_create(&g, 3);

    CU_ASSERT(test_grille_init(g, 3)==1);

    /* Libération de la mémoire allouée pour g */
    int i;
    for(i=0; i<g.taille; i++)
        free(g.Grille[i]);
    free(g.Grille);
    free(g.tuilesDejaPosees);
}


/*
* Fonction intermédiaire pour test_poserTuile 
*/
int testPoserTuile(grilleDeJeu laGrille, int X, int Y, tuile laTuile){

    int i, j;
    if (laTuile.orientation==0 || laTuile.orientation==2)//Tuile Vertical
        for(j=0;j<3;j++){
            for(i=0;i<2;i++){
                    if(laGrille.Grille[X+i][Y+j].typeCase != laTuile.contenu[i][j])
                        return 0;
            }
        }
    else{
            //tuile horizontale
            for(j=0;j<2;j++){
                for(i=0;i<3;i++){
                    if(laGrille.Grille[X+i][Y+j].typeCase != laTuile.contenu[i][j])
                        return 0;
                }
            }
        }
    return 1;
}


/* Fonction pour tester la fonction Jeu_init_fichier */
void test_poserTuile(){
    tuile b;
    b.orientation = 0;
    b.contenu[0][0] ='P';
    b.contenu[0][1] = 'F';
    b.contenu[0][2] = 'E';
    b.contenu[1][0] = 'L';
    b.contenu[1][1] = 'V';
    b.contenu[1][2] = 'E';
    b.contenu[2][0] = 'R';
    b.contenu[2][1] = 'U';
    b.contenu[2][2] = 'E';

    grilleDeJeu a;
    a.taille = 50;
    grille_create(&a, 1);
    int X = 0, Y = 0;
    PoserTuile(a, b, X, Y);

    CU_ASSERT(testPoserTuile(a,X,Y,b)==1);

    /* Libération de la mémoire allouée pour g */
    int i;
    for(i=0; i<a.taille; i++)
        free(a.Grille[i]);
    free(a.Grille);
    free(a.tuilesDejaPosees);
}


/*
* Fonction intermédiaire pour test_poserTuile 
*/
void test_jeu_init_fichier(){
    grilleDeJeu g;
    Deck D = Jeu_init_fichier("tests/PartieTest.txt", &g);

    int result = 1;
    if (g.taille != 10) result = 0;
    if (D.tailleDeck != 2) result = 0;
    if (D.deckTuiles[0] != 15 || D.deckTuiles[1] != 1) result = 0;
    if (D.id_depart != 15) result = 0;

    CU_ASSERT(result == 1);

    /* Libération de la mémoire allouée pour g */
    int i;
    for(i=0; i<g.taille; i++)
        free(g.Grille[i]);
    free(g.Grille);
    free(g.tuilesDejaPosees);

    /* Libération mémoire pour D */
    free(D.deckTuiles);
}


void verifPoseLac(){
    /*On génrère une tuile comportant un lac, on la pose sur une grille puis on essaye de poser une autre tuile sur une case lac */
    grilleDeJeu g;
    g.taille=10;
    grille_create(&g,2);
    tuile t,t2;
    tuile_init(&t,1,'V','F','L','L','L','F');
    PoserTuile(g,t,2,2);
    tuile_init_random(&t2,2);
    CU_ASSERT(verifLac(g,t2,2,4)==0);
    CU_ASSERT(verifLac(g,t2,3,4));

    /* Libération de la mémoire allouée pour g */
    int i;
    for(i=0; i<g.taille; i++)
        free(g.Grille[i]);
    free(g.Grille);
    free(g.tuilesDejaPosees);   

}


void CoordVerifHorsTerrain(){
    grilleDeJeu g;
    g.taille=10;
    int i;
    grille_create(&g,2);
    CU_ASSERT(verifHorsTerrain(9,9,g));
    CU_ASSERT(verifHorsTerrain(9,10,g)==0);
    CU_ASSERT(verifHorsTerrain(10,9,g)==0);
    CU_ASSERT(verifHorsTerrain(-2,5,g)==0);
    CU_ASSERT(verifHorsTerrain(3,-2,g)==0);
    CU_ASSERT(verifHorsTerrain(8,7,g));

    for(i=0; i<g.taille; i++)
        free(g.Grille[i]);
    free(g.Grille);
    free(g.tuilesDejaPosees); 
}


void VerifRecouvreAuMoinUneTuile(){
    grilleDeJeu g;
    g.taille=10;
    grille_create(&g,2);
    int i;
    tuile t,t2;
    tuile_init(&t,1,'V','F','L','L','L','F');
    PoserTuile(g,t,2,2);
    tuile_init_random(&t2,2);
    CU_ASSERT(verifRecouvreUneTuile(g,t2,3,4));
    CU_ASSERT(verifRecouvreUneTuile(g,t2,4,4)==0);

    for(i=0; i<g.taille; i++)
        free(g.Grille[i]);
    free(g.Grille);
    free(g.tuilesDejaPosees); 
}


void VerifRecouvreTotalUneTuile(){
    grilleDeJeu g;
    g.taille=10;
    grille_create(&g,2);
    int i;
    tuile t,t2;
    tuile_init(&t,1,'V','F','L','L','L','F');
    PoserTuile(g,t,2,4);
    tuile_init_random(&t2,2);
   
    CU_ASSERT(neRecouvrePasTotalementUneTuile(g,t2,2,4)==0);
    CU_ASSERT(neRecouvrePasTotalementUneTuile(g,t2,2,6));

    for(i=0; i<g.taille; i++)
        free(g.Grille[i]);
    free(g.Grille);
    free(g.tuilesDejaPosees);
}


void VerifGrandVillage(){
    grilleDeJeu g;
    g.taille = 10;
    grille_create(&g,2);
    tuile t,t2;
    int i;
    tuile_init(&t,1,'V','V','V','V','L','F');
    tuile_init(&t2,2,'V','U','V','F','V','F');
    tuile_rotation(&t2);
    PoserTuile(g,t,2,4);
    PoserTuile(g,t2,3,5);
    CU_ASSERT(ScoreVillage(g,2,4,1)==6);

    for(i=0; i<g.taille; i++)
        free(g.Grille[i]);
    free(g.Grille);
    free(g.tuilesDejaPosees); 
}


void VerifPlusGrandVillage(){
    grilleDeJeu g;
    g.taille=10;
    grille_create(&g,10);

    dicoTuiles D = tuile_init_fichier("tests/TuilesB.txt");
    printf("charge ok \n");
    PoserTuile(g,D.leDico[0],0,2);
    PoserTuile(g,D.leDico[1],2,2);
    PoserTuile(g,D.leDico[2],4,2);
    PoserTuile(g,D.leDico[3],6,2);
    printf("pause\n");
    PoserTuile(g,D.leDico[4],8,2);
    printf("pause2\n");
    PoserTuile(g,D.leDico[5],0,5);
    PoserTuile(g,D.leDico[6],2,5);
    PoserTuile(g,D.leDico[7],4,5);
    PoserTuile(g,D.leDico[8],6,5);
    PoserTuile(g,D.leDico[9],8,5);

    afficheGrille(g);
    int tmpScore= Score_plus_grand_village(g);
    printf("score: %d \n",tmpScore);
    CU_ASSERT(tmpScore==13);

    int i;
    for(i=0; i<g.taille; i++)
        free(g.Grille[i]);
    free(g.Grille);
    free(g.tuilesDejaPosees); 
}


int main(){
    CU_pSuite pSuite =NULL;
    //intialisation du registre de test CUNIT
    CU_pSuite pSuiteLotB =NULL;
    CU_pSuite pSuiteLotC =NULL;
    if (CU_initialize_registry() != CUE_SUCCESS){
        return CU_get_error();
    }

    //Ajout de la suite au registre
    pSuite = CU_add_suite("Suite", init_suite, clean_suite);
    if(pSuite == NULL)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    pSuiteLotB = CU_add_suite("SuiteB", init_suite, clean_suite);
    if(pSuiteLotB == NULL)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    pSuiteLotC = CU_add_suite("SuiteC", init_suite, clean_suite);
    if(pSuiteLotC == NULL)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    printf("ok\n");
    //ajout du test à la suite
    if ((CU_add_test(pSuite, "Test d'initialisation d'une tuile", test_init_tuile) == NULL) ||
        (CU_add_test(pSuite, "Test d'initialisation aléatoire d'une tuile", test_tuileRandom) == NULL) ||
        (CU_add_test(pSuite, "Test d'initialisation d'un dictionnaire de tuiles à partir d'un fichier", test_tuile_init_fichier) == NULL) ||
        (CU_add_test (pSuite, "Test de rotation", test_rotation) == NULL) ||
        (CU_add_test(pSuite, "Test de Lecture de terrain d'une case", test_LireCaseType) == NULL) ||
        (CU_add_test(pSuite, "Test de Lecture du numéro de tuile sur une case", test_lireCaseNumeroTuile) == NULL) ||
        (CU_add_test(pSuite, "Test de Creation de Grille", test_grilleCreate) == NULL) ||
        (CU_add_test(pSuite, "Test de Poser une tuile sur la grille", test_poserTuile) == NULL) ||
        (CU_add_test(pSuite, "Test de Création d'un Deck à partir d'un fichier", test_jeu_init_fichier) == NULL)
        ){
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Ajout des test du lot B
    if ((CU_add_test(pSuiteLotB,"Test de recouvrement d'un Lac",verifPoseLac)==NULL)||
    (CU_add_test(pSuiteLotB,"Test limitation Terrain",CoordVerifHorsTerrain)==NULL)||
    (CU_add_test(pSuiteLotB,"Test Recouvre au moins une tuile",VerifRecouvreAuMoinUneTuile)==NULL)||
    (CU_add_test(pSuiteLotB,"Teste Recouvre Totalement une Tuile",VerifRecouvreTotalUneTuile)==NULL)
    ){
        CU_cleanup_registry();
        return CU_get_error();
    }
    // Ajout des test du lot C
    if ((CU_add_test(pSuiteLotC,"Test taille Village",VerifGrandVillage)==NULL)||
    (CU_add_test(pSuiteLotC,"Test du plus Grand Village",VerifPlusGrandVillage)==NULL)){
        CU_cleanup_registry();
        return CU_get_error();
    }
    //Execution de tous les tests
    CU_basic_set_mode (CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}