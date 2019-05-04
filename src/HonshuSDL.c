#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <time.h>
#include "Jeu.h"
#include "Grille.h"
#include "Tuiles.h"
#include "Affichage.h"
#include "HonshuSDL.h"
#define TAILLE_TEXTURE 34

TTF_Font *policeLCD = NULL;
TTF_Font *policeJuice = NULL;
TTF_Font *policePrototype = NULL;
SDL_Surface* Texture[TAILLE_TEXTURE];
int tempsMouse;

enum textures{
texture_Affichage_Honhsu=0,
texture_AffichageLCD,
texture_bleuH,
texture_bleuV,
texture_caseClaire,
texture_caseSombre,
texture_dos_cartes,
texture_EcranTitre,
texture_finPartie,
texture_flecheRD,
texture_flecheRG,
texture_flecheVD,
texture_flecheVG,
texture_fondJeu,
texture_foret,
texture_lac,
texture_ligneH,
texture_ligneV,
texture_maison,
texture_noCarte,
texture_plaque,
texture_plateau,
texture_prairie,
texture_ressource,
texture_rougeH,
texture_rougeV,
texture_SeparationH,
texture_SeparationV,
texture_TemoinNoire,
texture_TemoinRouge,
texture_TemoinVert,
texture_usine,
texture_vertH,
texture_vertV
};


void  load_Texture(){
    Texture[0]=IMG_Load("bin/Affichage_Honhsu.png");
    Texture[1]=IMG_Load("bin/AffichageLCD.png");
    Texture[2]=IMG_Load("bin/bleuH.png");
    Texture[3]=IMG_Load("bin/bleuV.png");
    Texture[4]=IMG_Load("bin/caseClaire.png");
    Texture[5]=IMG_Load("bin/caseSombre.png");
    Texture[6]=IMG_Load("bin/dos_cartes.png");
    Texture[7]=IMG_Load("bin/EcranTitre.png");
    Texture[8]=IMG_Load("bin/finPartie.png");
    Texture[9]=IMG_Load("bin/flecheRD.png");
    Texture[10]=IMG_Load("bin/flecheRG.png");
    Texture[11]=IMG_Load("bin/flecheVD.png");
    Texture[12]=IMG_Load("bin/flecheVG.png");
    Texture[13]=IMG_Load("bin/fondJeu.png");
    Texture[14]=IMG_Load("bin/foret.png");
    Texture[15]=IMG_Load("bin/lac.png");
    Texture[16]=IMG_Load("bin/ligneH.png");
    Texture[17]=IMG_Load("bin/ligneV.png");
    Texture[18]=IMG_Load("bin/maison.png");
    Texture[19]=IMG_Load("bin/noCarte.png");
    Texture[20]=IMG_Load("bin/plaque.png");
    Texture[21]=IMG_Load("bin/plateau.png");
    Texture[22]=IMG_Load("bin/prairie.png");
    Texture[23]=IMG_Load("bin/ressource.png");
    Texture[24]=IMG_Load("bin/rougeH.png");
    Texture[25]=IMG_Load("bin/rougeV.png");
    Texture[26]=IMG_Load("bin/SeparationH.png");
    Texture[27]=IMG_Load("bin/SeparationV.png");
    Texture[28]=IMG_Load("bin/TemoinNoire.png");
    Texture[29]=IMG_Load("bin/TemoinRouge.png");
    Texture[30]=IMG_Load("bin/TemoinVert.png");
    Texture[31]=IMG_Load("bin/usine.png");
    Texture[32]=IMG_Load("bin/vertH.png");
    Texture[33]=IMG_Load("bin/vertV.png");
    }
void sdlFreeTexture(){
    int i;
    for (i=0;i<TAILLE_TEXTURE;i++){
        SDL_FreeSurface(Texture[i]);
    }
}
int locationSouris(int pos[]){
     int result = 0;
    if (pos[1]>756 && pos[1]<789){
        if (pos[0]>440 && pos[0]<497){
            result =2;
        }
        else if (pos[0]>13 && pos[0]<72){
            result =1;
        }   
    }else if ((pos[0]>209 && pos[0]<293) && (pos[1]>705 && pos[1]<833)){
        result =3;
    }
    return result;  
}


int pause(int pos[]){
    SDL_Event event;
    int continuer2 = 1;
    int result =0;
    int temps;
    while (continuer2){
        SDL_WaitEvent(&event);
        
        switch (event.type){
            case SDL_QUIT:
                continuer2 = 0;
                result=-1;
                break;
            case SDL_MOUSEBUTTONDOWN: 
                if(event.button.button==SDL_BUTTON_LEFT){
                    
                    pos[0]=event.button.x;
                    pos[1]=event.button.y;
                    //printf("x : %d , y: %d \n",event.button.x,event.button.y);
                    result=10;
                    continuer2=0;
                }else if(event.button.button==SDL_BUTTON_RIGHT){
                    pos[0]=event.button.x;
                    pos[1]=event.button.y;
                    //printf("x : %d , y: %d \n",event.button.x,event.button.y);
                    result=11;
                    continuer2=0;
                }
                    break;
            case SDL_MOUSEMOTION:
                temps= SDL_GetTicks();
                if((temps-tempsMouse)>50){
                     pos[0]=event.motion.x;
                    pos[1]=event.motion.y;
                    result=11;
                    continuer2=0;
                    tempsMouse=temps;}
                    break; 
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym){
                    case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
                        continuer2 = 0;
                        result = -1; 
                        break;
                    case SDLK_q:
                        continuer2 = 0;
                        result =-1;
                        break;
                    case SDLK_DOWN:
                        result=1;
                        continuer2 = 0;
                        break;
                    case SDLK_UP:
                        result = 2;
                        continuer2 = 0;
                        break;
                    case SDLK_RETURN:
                        result = 3;
                        continuer2 = 0;
                        break;
                    case SDLK_LEFT:
                        result= 4;
                        continuer2=0;
                        break;
                    case SDLK_RIGHT:
                        result=5;
                        continuer2=0;
                        break;
                    case SDLK_h:
                        result=6;
                        continuer2=0;
                        break;
                    case SDLK_d:
                        result = 7;
                        continuer2=0;
                        break;
                    case SDLK_o:
                        result=8;
                        continuer2=0;
                        break;
                    case SDLK_r:
                        result=9;
                        continuer2=0;
                        break;    
                    default:    
                    continue;
                }
            default:
                continue;
           
        }

        /*tempsactuel = SDL_GetTicks();
        if ((tempsactuel - tempsavant)> 5){
        SDL_Flip(ecran);
        }
        else{
            SDL_Delay(5 -(tempsactuel-tempsavant));
        }*/
    }
    
    return result;
}

void setPos(SDL_Color tabCol[], int pos){
    /*Sert au menu */
    SDL_Color couleurNoire = {0, 0, 0, 255};
    SDL_Color couleurRouge = {255, 0, 0, 255};
    tabCol[0]=couleurNoire;
    tabCol[1]=couleurNoire;
    tabCol[2]=couleurNoire;
    tabCol[3]=couleurNoire;
    tabCol[4]=couleurNoire;
    tabCol[pos]=couleurRouge;
}

int EcranTitre(SDL_Surface *ecran){
    int result= 0;
    TTF_Font *police = NULL;
    SDL_Color tabCol[5];
    int posCur =0;
    int action;
    int continuer = 1;
    int pos[2];
    SDL_Surface *txtDemarer = NULL, *txtQuit = NULL;
    
    police = TTF_OpenFont("bin/orange_juice.ttf", 65);
    SDL_Rect position;
    while(continuer){
        setPos(tabCol,posCur);
        position.x = 0;
        position.y = 0;
        SDL_BlitSurface(Texture[7], NULL, ecran, &position);
        
        txtDemarer = TTF_RenderText_Blended(police, "Nouvelle Partie", tabCol[0]);
        txtQuit = TTF_RenderText_Blended(police, "Quitter", tabCol[1]);
        position.x = 350;
        position.y = 500;
        SDL_BlitSurface(txtDemarer, NULL, ecran, &position);
        position.x = 350;
        position.y = 550;
        SDL_BlitSurface(txtQuit, NULL, ecran, &position);
        SDL_Flip(ecran); 
        action = pause(pos);
        switch (action) {
            case -1:
                continuer = 0;
                break;
            case 1:
                posCur = 1;
                
                break;
            case 2:
                 posCur = 0;
                break;
            case 3:
                if (posCur==0){
                    result = 1;
                }
                continuer =0;
                break;
            default:
                continue;
        }
    }
    return result;

}


void menuDebutPartie(SDL_Surface *ecran, int result[]){
    SDL_Rect position;
    int pos[2];
    SDL_Surface *Txttoprint = NULL;
   
    TTF_Font *police = NULL;
    SDL_Color tabCol[5];
    police = TTF_OpenFont("bin/orange_juice.ttf", 40);
    int continuer = 1;
    int tailleGrille  =10;
    int TailleDeck = 5;
    int posCur=0;
    int action;
    char StrNbr[5];
    result[0]=0;
    result[1]=0;
    result[2]=0;
    while(continuer){
         
        setPos(tabCol,posCur);
        position.x = 0;
        position.y = 0;
        SDL_BlitSurface(Texture[7], NULL, ecran, &position);
 
        position.x = 350;
        position.y = 500;
        Txttoprint = TTF_RenderText_Blended(police, "Taille de la Grille",tabCol[0]);
        SDL_BlitSurface(Txttoprint, NULL, ecran, &position);
        sprintf(StrNbr,"%d",tailleGrille);
        Txttoprint = TTF_RenderText_Blended(police, StrNbr, tabCol[0]);
        position.x=630;
        SDL_BlitSurface(Txttoprint, NULL, ecran, &position);
        position.x = 350;
        position.y = 550;
        Txttoprint = TTF_RenderText_Blended(police, "Taille Du Deck :", tabCol[1]);
        SDL_BlitSurface(Txttoprint, NULL, ecran, &position);
        sprintf(StrNbr,"%d",TailleDeck);
        Txttoprint = TTF_RenderText_Blended(police, StrNbr, tabCol[1]);
        position.x=600;
        SDL_BlitSurface(Txttoprint, NULL, ecran, &position);
        position.x = 350;
        position.y = 600;
        Txttoprint =  TTF_RenderText_Blended(police, "Charger Partie", tabCol[2]);
        SDL_BlitSurface(Txttoprint, NULL, ecran, &position);
         position.x = 350;
        position.y = 650;
        Txttoprint =  TTF_RenderText_Blended(police, "Demarer Partie", tabCol[3]);
        SDL_BlitSurface(Txttoprint, NULL, ecran, &position);
        position.x = 350;
        position.y = 700;
        Txttoprint =  TTF_RenderText_Blended(police, "Quitter", tabCol[4]);

        SDL_Flip(ecran);
  
        action = pause(pos);
        
        switch (action) {
            /*4 G 5 D */
            case -1:
                continuer = 0;
                break;
            case 1:
                if (posCur<3){
                    posCur++;
                }
                            
                break;
            case 2:
                if (posCur>0){
                    posCur--;
                }
                break;
            case 3:
                switch(posCur){
                    case 2:
                        result[0]=2;
                         /*demarer partie chargé */
                         continuer=0;
                        break;
                    case 3:
                        /*Demarer la partie aleatoire*/    
                        result[0]=1;
                        result[1]=tailleGrille;
                        result[2]=TailleDeck;
                        continuer=0;
                        break;
                    case 4:
                        result[0]=0;
                        continuer=0;
                        /*Quitter */
                        break;
                    default:
                        break;
                }
                
                break;
            case 4:
                switch(posCur){
                    case 0:
                        if(tailleGrille>5){
                        tailleGrille--;}
                        break;
                    case 1:
                        if(TailleDeck>5){
                        TailleDeck--;}
                        break;
                    default:
                        break;
                }
                break;
            case 5:
              switch(posCur){
                    case 0:
                        if (tailleGrille<15){
                        tailleGrille++;}
                        break;
                    case 1: 
                        if(TailleDeck<12){
                        TailleDeck++;}
                        break;
                    default:
                        break;
                }
                break;
            default:
                continue;
        }
    }
}


void quitSDL(){
    sdlFreeTexture();
    TTF_Quit();
    SDL_Quit();
    Mix_CloseAudio(); 
}


void afficheTuileSDL(SDL_Surface *ecran, int x, int y, tuile T){
    SDL_Rect pos_tuile;
    int i, j;
    if((T.orientation==0)||(T.orientation==2)){
        for (i=0; i<2; i++){
            for (j=0; j<3; j++){
                pos_tuile.x =x+(i*44);
                pos_tuile.y =y+(j*44);
                switch(T.contenu[i][j]){
                    case 'P':
                        SDL_BlitSurface(Texture[22], NULL, ecran, &pos_tuile);
                        break;
                    case 'F':
                        SDL_BlitSurface(Texture[14], NULL, ecran, &pos_tuile);
                        break;
                    case 'L':
                        SDL_BlitSurface(Texture[15], NULL, ecran, &pos_tuile);
                        break;
                    case 'V':
                        SDL_BlitSurface(Texture[18], NULL, ecran, &pos_tuile);
                        break;
                    case 'U':
                        SDL_BlitSurface(Texture[31], NULL, ecran, &pos_tuile);
                        break;
                    case 'R':
                        SDL_BlitSurface(Texture[23], NULL, ecran, &pos_tuile); 
                    default : 
                        break;
                }
            }
        }
    }else{
        for (i=0; i<3; i++){
            for (j=0; j<2; j++){
                pos_tuile.x =x+(i*44);
                pos_tuile.y =y+(j*44);
                switch(T.contenu[i][j]){
                    case 'P':
                        SDL_BlitSurface(Texture[22], NULL, ecran, &pos_tuile);
                        break;
                    case 'F':
                        SDL_BlitSurface(Texture[14], NULL, ecran, &pos_tuile);
                        break;
                    case 'L':
                        SDL_BlitSurface(Texture[15], NULL, ecran, &pos_tuile);
                        break;
                    case 'V':
                        SDL_BlitSurface(Texture[18], NULL, ecran, &pos_tuile);
                        break;
                    case 'U':
                        SDL_BlitSurface(Texture[31], NULL, ecran, &pos_tuile);
                        break;
                    case 'R':
                        SDL_BlitSurface(Texture[23], NULL, ecran, &pos_tuile);
                    default : 
                        break;
                }
            }
        }
    }
}
int PremierCarteDeck(Deck D, tuilePosee *Historique, int idTuile){
    int result = 1;
    if (idTuile==0){
        result=1;
    }else{
        int i;
        for (i=0; i<idTuile;i++){
            if (Historique[D.deckTuiles[i]].X == -1){
                result=0;
            }
        }
    }
    return result;
}
int DerniereCarteDeck(Deck D, tuilePosee *Historique, int indexTuile){
    int result = 1;
    if (indexTuile==D.tailleDeck-1){
        result=1;
    }else{
        int i;
        for (i=indexTuile+1;i<D.tailleDeck;i++){
            if (Historique[D.deckTuiles[i]].X == -1){
                result=0;
                
            }
            
        }
    }
    return result;
}

int premiereCarteAvant(Deck D, tuilePosee *Historique, int idTuile){
    int result;
        if(PremierCarteDeck(D,Historique,idTuile)==0){
            int i = 1;
            while (i){
                if (idTuile==0){
                    /*ne devrait jamais se produire*/
                    i=0;
                    result=-1;
                }else{
                    idTuile --;
                    if (Historique[D.deckTuiles[idTuile]].X == -1){
                    i=0;
                    return idTuile;
                    }         
                }
                          
            }
        }else{
            result=-1;
        }

    return result;
}
int premiereCarteApres(Deck D, tuilePosee *Historique, int idTuile){
    int result;
        if(DerniereCarteDeck(D,Historique,idTuile)==0){
            int i=1;
            while(i){
                if (idTuile==D.tailleDeck-1){
                    /*ne devrai jamais se produire */
                    result = -1;
                }else{
                    idTuile++;
                    if (Historique[D.deckTuiles[idTuile]].X == -1){
                    i=0;
                    return idTuile;
                    }
                }
            }
        }else{
            result=-1;
        }
    return result;
}

void afficheDeckSDL(SDL_Surface *ecran, dicoTuiles Dico, Deck D, tuilePosee *Historique, int IdTuileEnCour){
   
   
    SDL_Rect position;
    
    position.y=700;
    afficheTuileSDL(ecran, 210, 705, Dico.leDico[D.deckTuiles[IdTuileEnCour]]);
  
    position.x=10;
    position.y=750;

    if (PremierCarteDeck(D,Historique, IdTuileEnCour)){
        position.y=750;
        SDL_BlitSurface(Texture[texture_flecheRG],NULL,ecran,&position);
        position.x=320;
        position.y=700;
        SDL_BlitSurface(Texture[texture_noCarte],NULL,ecran,&position);
    }else{
        position.y=750;
        SDL_BlitSurface(Texture[texture_flecheVG],NULL,ecran,&position);
        position.x=320;
        position.y=700;
        SDL_BlitSurface(Texture[texture_dos_cartes],NULL,ecran,&position);
    }
    position.x = 440;
    if (DerniereCarteDeck(D,Historique, IdTuileEnCour)){
        position.y=750;
        SDL_BlitSurface(Texture[texture_flecheRD],NULL,ecran,&position);
        position.y=700;
        position.x=90;
        SDL_BlitSurface(Texture[texture_noCarte],NULL,ecran,&position);
    }else{
        position.y=750;
        SDL_BlitSurface(Texture[texture_flecheVD],NULL,ecran,&position);
        position.y=700;
        position.x=90;
        SDL_BlitSurface(Texture[texture_dos_cartes],NULL,ecran,&position);
    }
}

void afficheDeckSDLv(SDL_Surface *ecran, dicoTuiles Dico, Deck D, tuilePosee *Historique){
    int i;
    int x = 11;
    int y = 0;

    for (i=0; i<D.tailleDeck; i++){
        if (Historique[D.deckTuiles[i]].X == -1){
            afficheTuileSDL(ecran, x, y, Dico.leDico[D.deckTuiles[i]]);
            if (x == 20){
                x = 11;
            }
            else{
                x += 3;
            }
            if (x == 11){
                y += 4;
            }
        }
    }
}

void AfficheRectTuile(SDL_Surface *ecran,int X, int Y, int Color, int orientation){
    /* color : 1 vert, 2 bleu, 3 rouge */
    /* orientation 0 : Vertivale, 1 Horizontale */
    SDL_Surface *Rectangle = NULL;
    SDL_Rect position;
    if (orientation==0){
        switch(Color){
            case 1:
                Rectangle=Texture[texture_vertV]; //IMG_Load("bin/vertV.png");
                break;
            case 2:
                Rectangle=Texture[texture_bleuV];// IMG_Load("bin/bleuV.png");
                break;
            case 3:
                Rectangle=Texture[texture_rougeV];   //IMG_Load("bin/rougeV.png");
                break;
            default:
                break;
        }
    }else{
        /*Tuile Horizontale */
        switch(Color){
            case 1:
                Rectangle=Texture[texture_vertH];   //IMG_Load("bin/vertH.png");
                break;
            case 2:
                Rectangle=Texture[texture_bleuH];   //IMG_Load("bin/bleuH.png");
                break;
            case 3:
                Rectangle=Texture[texture_rougeH]; //IMG_Load("bin/rougeH.png");
                break;
            default:
                break;
        }
    }
    position.x=X;
    position.y=Y;
    SDL_BlitSurface(Rectangle, NULL, ecran, &position);

}

int numeroTuileSelectionner(int idIndex, Deck D){
    return D.deckTuiles[idIndex];
}
void afficheTraitDelimitation(SDL_Surface *ecran){
    SDL_Surface *TraitH = NULL, *TraitV = NULL;
    TraitH=Texture[texture_SeparationH]; //IMG_Load("bin/SeparationH.png");
    TraitV=Texture[texture_SeparationV]; //IMG_Load("bin/SeparationV.png");
    SDL_Rect position;
    position.x=0;
    position.y=684;
    int i;
    for (i=0;i<684;i++){
        position.x = i;
        SDL_BlitSurface(TraitH, NULL, ecran, &position);
    }
    for (i=0;i<684;i++){
        position.y = i;
        SDL_BlitSurface(TraitV, NULL, ecran, &position);
    }
}
void verifSiPossiblePourVoyant(grilleDeJeu G, tuile T, int X, int Y, int TabResult[]){
    TabResult[2]=neRecouvrePasTotalementUneTuile(G,T,X,Y);
    TabResult[0]=verifLac(G,T,X,Y);
    TabResult[1]=verifRecouvreUneTuile(G,T,X,Y);    
}
void AfficheVoyant(SDL_Surface *ecran, grilleDeJeu G,tuile T, int X, int Y, int Etat){
    SDL_Surface *Tvert =NULL, *Trouge = NULL, *Tnoir = NULL;
    Tvert=Texture[texture_TemoinVert]; //IMG_Load("bin/TemoinVert.png");
    Trouge=Texture[texture_TemoinRouge]; //IMG_Load("bin/TemoinRouge.png");
    Tnoir=Texture[texture_TemoinNoire]; //IMG_Load("bin/TemoinNoire.png");
    int Possible[3];
    SDL_Rect position;
     
    if (Etat==0){
        position.y = 180;
        position.x = 740;
        SDL_BlitSurface(Tnoir,NULL,ecran,&position);
        position.x=740;
        position.y = 230;
        SDL_BlitSurface(Tnoir,NULL,ecran,&position);
        position.x=740;
        position.y = 280;
        SDL_BlitSurface(Tnoir,NULL,ecran,&position);
    }else{
        verifSiPossiblePourVoyant(G,T,X,Y,Possible);
        position.y = 180;
        position.x = 740;
        if(Possible[0]){
            SDL_BlitSurface(Tvert,NULL,ecran,&position);
        }else{
            SDL_BlitSurface(Trouge,NULL,ecran,&position);
        }
        position.x=740;
        position.y = 230;
        if(Possible[1]){
            SDL_BlitSurface(Tvert,NULL,ecran,&position);
        }else{
            SDL_BlitSurface(Trouge,NULL,ecran,&position);
        }
        position.x=740;
        position.y = 280;
        if(Possible[2]){
            SDL_BlitSurface(Tvert,NULL,ecran,&position);
        }else{
            SDL_BlitSurface(Trouge,NULL,ecran,&position);
        }
    }
  
}
void afficheTxt(SDL_Surface *ecran, grilleDeJeu G, int vie, int Etat){
    /*Partie pour Heykel*/
   
    SDL_Rect position;
    SDL_Surface *ScoreTTF=NULL, *Afficheur = NULL; 
    Afficheur=Texture[texture_Affichage_Honhsu];//IMG_Load("bin/Affichage_Honhsu.png");
    position.x=700;
    position.y=10;
    SDL_BlitSurface(Afficheur,NULL,ecran,&position);
    SDL_Color couleurNoir = {0, 0, 0, 150};
    SDL_Color couleurViolet = {0, 200, 200, 255};
    SDL_Color couleurBlanc = {255,255,255,200};
    int score = calculScore(G);
 
    char strScore[15];
    char strVie[15];
    sprintf(strScore,"Score : %d",score);
    sprintf(strVie,"Vie : %d",vie);
    position.x = 740;
    position.y = 75;
    ScoreTTF=TTF_RenderText_Blended(policeLCD,strScore,couleurViolet);
    SDL_BlitSurface(ScoreTTF, NULL, ecran, &position);
    position.y=115;
    ScoreTTF=TTF_RenderText_Blended(policeLCD,strVie,couleurViolet);
    SDL_BlitSurface(ScoreTTF, NULL, ecran, &position);

    ScoreTTF=TTF_RenderText_Blended(policePrototype,"Ne recouvre pas un Lac",couleurNoir);
    position.x=780;
    position.y=180;
    SDL_BlitSurface(ScoreTTF, NULL, ecran, &position);

    ScoreTTF=TTF_RenderText_Blended(policePrototype,"Recouvre au moins",couleurNoir);
    position.x=780;
    position.y=225;
    SDL_BlitSurface(ScoreTTF, NULL, ecran, &position);
    position.y=245;
    ScoreTTF=TTF_RenderText_Blended(policePrototype,"une case",couleurNoir);
     SDL_BlitSurface(ScoreTTF, NULL, ecran, &position);
    position.y=275;
    ScoreTTF=TTF_RenderText_Blended(policePrototype,"Ne recouvre pas",couleurNoir);  
    position.x=780;
    SDL_BlitSurface(ScoreTTF, NULL, ecran, &position);
    ScoreTTF=TTF_RenderText_Blended(policePrototype,"totalement une tuile",couleurNoir);
    position.y = 300;
    
    
    SDL_BlitSurface(ScoreTTF, NULL, ecran, &position);
 
    
    switch(Etat){    
        case 0:
            
            position.x =703;
            position.y= 403;
            ScoreTTF=TTF_RenderText_Blended(policePrototype,"Selection Tuile",couleurNoir);
            SDL_BlitSurface(ScoreTTF, NULL, ecran, &position);
            position.x =700;
            position.y= 400;
            ScoreTTF=TTF_RenderText_Blended(policePrototype,"Selection Tuile",couleurBlanc);
            SDL_BlitSurface(ScoreTTF, NULL, ecran, &position);
            position.x =703;
            position.y= 453;
            ScoreTTF=TTF_RenderText_Blended(policePrototype,"D : Affiche Le deck",couleurNoir);
            SDL_BlitSurface(ScoreTTF, NULL, ecran, &position);
            position.x =700;
            position.y= 450;
            ScoreTTF=TTF_RenderText_Blended(policePrototype,"D : Affiche Le deck",couleurBlanc);
            SDL_BlitSurface(ScoreTTF, NULL, ecran, &position);
            position.x =703;
            position.y= 478;
            ScoreTTF=TTF_RenderText_Blended(policePrototype,"H : Utiliser le Solveur",couleurNoir);
            SDL_BlitSurface(ScoreTTF, NULL, ecran, &position);
            position.x =700;
            position.y= 475;
            ScoreTTF=TTF_RenderText_Blended(policePrototype,"H : Utiliser le solveur",couleurBlanc);
            SDL_BlitSurface(ScoreTTF, NULL, ecran, &position);
            position.x =703;
            position.y= 503;
            ScoreTTF=TTF_RenderText_Blended(policePrototype,"Entrer : Choix de la tuile",couleurNoir);
            SDL_BlitSurface(ScoreTTF, NULL, ecran, &position);
            position.x =700;
            position.y= 500;
            ScoreTTF=TTF_RenderText_Blended(policePrototype,"Entrer : Choix de la tuile",couleurBlanc);
            SDL_BlitSurface(ScoreTTF, NULL, ecran, &position);
             position.x =703;
            position.y= 528;
            ScoreTTF=TTF_RenderText_Blended(policePrototype,"ESC ou Q : Quitter",couleurNoir);
            SDL_BlitSurface(ScoreTTF, NULL, ecran, &position);
            position.x =700;
            position.y= 525;
            ScoreTTF=TTF_RenderText_Blended(policePrototype,"ESC ou Q : Quitter",couleurBlanc);
            SDL_BlitSurface(ScoreTTF, NULL, ecran, &position);
            break;
        case 1:
        position.x =703;
            position.y= 403;
            ScoreTTF=TTF_RenderText_Blended(policePrototype,"Poser Tuile",couleurNoir);
            SDL_BlitSurface(ScoreTTF, NULL, ecran, &position);
            position.x =700;
            position.y= 400;
            ScoreTTF=TTF_RenderText_Blended(policePrototype,"Poser Tuile",couleurBlanc);
            SDL_BlitSurface(ScoreTTF, NULL, ecran, &position);
            position.x =703;
            position.y= 453;
            ScoreTTF=TTF_RenderText_Blended(policePrototype,"O : rotation",couleurNoir);
            SDL_BlitSurface(ScoreTTF, NULL, ecran, &position);
            position.x =700;
            position.y= 450;
            ScoreTTF=TTF_RenderText_Blended(policePrototype,"O : rotation",couleurBlanc);
            SDL_BlitSurface(ScoreTTF, NULL, ecran, &position);
            position.x =703;
            position.y= 478;
            ScoreTTF=TTF_RenderText_Blended(policePrototype,"Entrer : Valider la pose",couleurNoir);
            SDL_BlitSurface(ScoreTTF, NULL, ecran, &position);
            position.x =700;
            position.y= 475;
            ScoreTTF=TTF_RenderText_Blended(policePrototype,"Entrer : Valider la pose",couleurBlanc);
            SDL_BlitSurface(ScoreTTF, NULL, ecran, &position);
            position.x =703;
            position.y= 503;            
            ScoreTTF=TTF_RenderText_Blended(policePrototype,"Clic Gauche : Valider la pose",couleurNoir);
            SDL_BlitSurface(ScoreTTF, NULL, ecran, &position);
            position.x =700;
            position.y= 500;
            ScoreTTF=TTF_RenderText_Blended(policePrototype,"Clic Gauche : Valider la pose",couleurBlanc);
            SDL_BlitSurface(ScoreTTF, NULL, ecran, &position);
             position.x =703;
            position.y= 528;            
            ScoreTTF=TTF_RenderText_Blended(policePrototype,"Clic Droit : Verifier Position Tuile",couleurNoir);
            SDL_BlitSurface(ScoreTTF, NULL, ecran, &position);
            position.x =700;
            position.y= 525;
            ScoreTTF=TTF_RenderText_Blended(policePrototype,"Clic Droit : Verifier Position Tuile",couleurBlanc);
            SDL_BlitSurface(ScoreTTF, NULL, ecran, &position);
            position.x =703;
            position.y= 553;            
            ScoreTTF=TTF_RenderText_Blended(policePrototype,"ESC ou Q : Quitter",couleurNoir);
            SDL_BlitSurface(ScoreTTF, NULL, ecran, &position);
            position.x =700;
            position.y= 550;
            ScoreTTF=TTF_RenderText_Blended(policePrototype,"ESC ou Q : Quitter",couleurBlanc);
            SDL_BlitSurface(ScoreTTF, NULL, ecran, &position);
            break;
        default:
            break;
    }
    SDL_FreeSurface(ScoreTTF);
    
}

void afficheDeckPleinEcran(SDL_Surface *ecran,Deck D, dicoTuiles Dico, tuilePosee *Historique){
    /*Partie Jiahui */
    TTF_Font *police = NULL;
    SDL_Color tabCol[4];
    int posCur =0;
    setPos(tabCol,posCur);
    SDL_Surface *txtJoue = NULL, *txtNonJoue = NULL;
    police = TTF_OpenFont("bin/orange_juice.ttf", 65);
    txtJoue = TTF_RenderText_Blended(police, "Joue", tabCol[1]);
    txtNonJoue = TTF_RenderText_Blended(police, "Non Joue", tabCol[1]);
    SDL_Surface  *fondJeu = NULL;
    int i;
    int x = 10, y = 10;
    int countX = 1;
    SDL_Rect position;
   
    fondJeu =Texture[texture_fondJeu]; //IMG_Load("bin/fondJeu.png");
    position.x = 0;
    position.y = 0;
    SDL_BlitSurface(fondJeu, NULL, ecran, &position);
    position.x = x;
    position.y = y;
    SDL_BlitSurface(txtNonJoue, NULL, ecran, &position);
    y += 60;
    for(i = 0; i < D.tailleDeck; i++) {
        if (Historique[D.deckTuiles[i]].X == -1) {
            if(countX <= 5){
                afficheTuileSDL(ecran, x, y, Dico.leDico[D.deckTuiles[i]]);
                countX++;
                x += 195;
            } else {
                countX = 1;
                x = 20;
                y += 200;
                afficheTuileSDL(ecran, x, y, Dico.leDico[D.deckTuiles[i]]);
            }
        }
    }
    x = 10;
    y += 200;
    position.y = y;
    for(i = 0; i < 400; i++) {
        position.x = x + i - 10;
        //SDL_BlitSurface(TraitH, NULL, ecran, &position);
    }

    y += 20;
    position.x = x;
    position.y = y;
    SDL_BlitSurface(txtJoue, NULL, ecran, &position);
    y += 60;
    countX = 1;
    for(i = 0; i < D.tailleDeck; i++) {
        if (Historique[D.deckTuiles[i]].X != -1) {
            if(countX <= 5){
                afficheTuileSDL(ecran, x, y, Dico.leDico[D.deckTuiles[i]]);
                countX++;
                x += 195;
            } else {
                countX = 1;
                x = 20;
                y += 2000;
                afficheTuileSDL(ecran, x, y, Dico.leDico[D.deckTuiles[i]]);
            }
        }
    }

}

int RentreDansLaGrille(grilleDeJeu G, int X, int Y, tuile T){
    int result =1;
    if ((T.orientation==0)||(T.orientation==2)){
        if((X<0)||(X>G.taille-2)){result=0;}
        if((Y<0)||(Y>G.taille-3)){result=0;}
    }else{
        if((X<0)||(X>G.taille-3)){result=0;}
        if((Y<0)||(Y>G.taille-2)){result=0;}
    }
    return result;
}
void CorrigeVal(grilleDeJeu G, int pos[],tuile T){
     if ((T.orientation==0)||(T.orientation==2)){
        if(pos[0]<0){pos[0]=0;}
        if(pos[0]>G.taille-2){pos[0]=G.taille-2;}
        if(pos[1]<0){pos[1]=0;}
        if(pos[1]>G.taille-3){pos[1]=G.taille-3;}
    }else{
        if(pos[0]<0){pos[0]=0;}
        if(pos[0]>G.taille-3){pos[0]=G.taille-3;}
        if(pos[1]<0){pos[1]=0;}
        if(pos[1]>G.taille-2){pos[1]=G.taille-2;}
    }
}
int verifSiPossible(grilleDeJeu G, tuile T, int X, int Y){
    int result = 0;
    if(neRecouvrePasTotalementUneTuile(G,T,X,Y)&&verifRecouvreUneTuile(G,T,X,Y)&&verifLac(G,T,X,Y)){
        result=1;}
    return result;
}
void afficeSiPossible(SDL_Surface *ecran, grilleDeJeu G, tuile T, int X, int Y){
    /*void AfficheRectTuile(SDL_Surface *ecran,int X, int Y, int Color, int orientation){ */
    /* color : 1 vert, 2 bleu, 3 rouge */
    /* orientation 0 : Vertivale, 1 Horizontale */
    int color, orientation;

    if (verifSiPossible(G,T,X,Y)){color=1;}else{color=3;}
    if((T.orientation==0)||(T.orientation==2)){orientation=0;}else{orientation=1;}
    AfficheRectTuile(ecran,10+(X*44),10+(Y*44),color,orientation);
}
int VerifieDerniereTuile(Deck D, tuilePosee *Historique){
	int i;
	int nbRestant = 0;
	int id = -1;
	/* On test s'il reste des tuiles non posées dans le deck */
	for(i = 0; i < D.tailleDeck; i++) {
		
        if(Historique[D.deckTuiles[i]].X == -1){
			id = i;
			nbRestant++;
			if (nbRestant > 1){
				id=-1;
			}
			
		}
	}
	return id;
}
void gereOrientation(grilleDeJeu G, tuile T,int Coord[]){
    /*Coor[0] = x, coor[1] = Y */
    if ((T.orientation==0)||(T.orientation==2)){
        /*Vertical a Horizontal */
        if (Coord[0]>G.taille-3){
            Coord[0]=G.taille-3;
        }
    }else{
        if(Coord[1]>G.taille-3){
            Coord[1]=G.taille-3;
        }
    }
}
void afficheGrilleD(SDL_Surface *ecran, grilleDeJeu G){
    SDL_Surface *IMGlac =NULL, *IMGmaison =NULL, *IMGForet = NULL;
    SDL_Surface *IMGPrairie = NULL, *IMGUsine=NULL, *IMGRessource=NULL, *fondJeu=NULL, *CaseClaire=NULL, *CaseSombre =NULL;
    SDL_Rect position;
  
  
    IMGlac=Texture[texture_lac];//IMG_Load("bin/lac.png");
    IMGmaison=Texture[texture_maison]; //IMG_Load("bin/maison.png");
    IMGForet=Texture[texture_foret];//IMG_Load("bin/foret.png");
    IMGPrairie=Texture[texture_prairie];//IMG_Load("bin/prairie.png");
    IMGUsine=Texture[texture_usine];//IMG_Load("bin/usine.png");
    IMGRessource=Texture[texture_ressource];//IMG_Load("bin/ressource.png");
    fondJeu=Texture[texture_fondJeu];//IMG_Load("bin/fondJeu.png");
    CaseClaire=Texture[texture_caseClaire]; //IMG_Load("bin/caseClaire.png");
    CaseSombre=Texture[texture_caseSombre];//IMG_Load("bin/caseSombre.png");
    position.x = 0;
    position.y = 0;
    SDL_BlitSurface(fondJeu, NULL, ecran, &position);
    int i,j,k;
    k=0;
    for(j=0;j<G.taille;j++){
        for(i=0;i<G.taille;i++){
            position.x=10+(i*44);
            position.y=10+(j*44);
            switch(k){
                case 0:
                    k=1;
                    SDL_BlitSurface(CaseSombre, NULL, ecran, &position);
                    break;
                case 1:
                    k=0;
                    SDL_BlitSurface(CaseClaire, NULL, ecran, &position);
                    break;
            }
        }
        if(j%2==0){k=1;}else{k=0;}
    }
     int x, y;
    for (x=0; x<G.taille; x++){
        for (y=0; y<G.taille; y++){
            position.x = 14+(x*44);
            position.y= 14+(y*44);
            switch(lireCaseType (x, y, G)){
                case 'P':
                    SDL_BlitSurface(IMGPrairie, NULL, ecran, &position);
                    break;
                case 'F':
                    SDL_BlitSurface(IMGForet, NULL, ecran, &position);
                    break;
                case 'L':
                    SDL_BlitSurface(IMGlac, NULL, ecran, &position);
                    break;
                case 'V':
                    SDL_BlitSurface(IMGmaison, NULL, ecran, &position);
                    break;
                case 'U':
                    SDL_BlitSurface(IMGUsine, NULL, ecran, &position);
                    break;
                case 'R':
                    SDL_BlitSurface(IMGRessource, NULL, ecran, &position); 
                case 'E':
                    break;
            }
        }
    }

}
void FindePartie(SDL_Surface *ecran, int score){
    SDL_Surface *fond=NULL, *txtFinPartie=NULL;
    fond=IMG_Load("bin/finPartie.png");
    SDL_Color couleurRouge = {255, 0, 0, 255};
    TTF_Font *police = NULL;
    char txt[20];
    SDL_Rect position;
    position.x=0;
    position.y=0;
    SDL_BlitSurface(fond,NULL,ecran,&position);
    police = TTF_OpenFont("bin/orange_juice.ttf", 65);
    sprintf(txt,"Score : %d",score);
    txtFinPartie = TTF_RenderText_Blended(police, txt, couleurRouge);
    position.x = 400;
    position.y=650;
    SDL_BlitSurface(txtFinPartie, NULL, ecran, &position); 
    SDL_FreeSurface(txtFinPartie);
    SDL_FreeSurface(fond);
}

void sourisDansGrille(int pos[], grilleDeJeu G){
    int xmax;
    xmax = 10+G.taille*44;
    if((pos[0]>10)&&(pos[1]>10)&&(pos[0]<xmax)&&(pos[1]<xmax)){
    /*je suis bien dans la grille*/
    pos[0]=(pos[0]-10)/44;
    pos[1]=(pos[1]-10)/44;
    }else{
        pos[0]=-1;
    }
}

void mainSDL(){
    tempsMouse=0;
    int vie = 3;
    SDL_Surface *ecran = NULL;
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    load_Texture();
    policeLCD = TTF_OpenFont("bin/LCD.ttf", 36);
    policePrototype= TTF_OpenFont("bin/Prototype.ttf", 18);
    int action;
    ecran = SDL_SetVideoMode(1024, 900, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Honshu by StrangerC", NULL);
   // affiche_grilleSDL(ecran);
    SDL_WM_SetCaption("SDL_Mixer", NULL);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    Mix_Music *musique;
    musique = Mix_LoadMUS("bin/Chill.mp3");
    Mix_PlayMusic(musique, -1);
    action = EcranTitre(ecran);
  
    if (action == 1){
        tuilePosee *Historique ;
        dicoTuiles Dico = tuile_init_fichier("./sauvegardes/Tuiles.txt");
        Historique = (tuilePosee *)malloc(Dico.taille*sizeof(tuilePosee));
        int i;
        for (i=0; i<Dico.taille; i++){
            Historique[i].X = -1; /* On initialise X à -1 : cela signifie que la tuile numéro i n'a pas été posée sur la grille */
        }
        grilleDeJeu G;
        int choixPartie[3];
        menuDebutPartie(ecran,choixPartie);
        Deck D;
     
        tuile T;
        switch(choixPartie[0]){
            case 1:
                /*partie aleatoire
                choixPartie[1]= taille Grille
                choixPartie[2]= taille deck
                */
                D = deckRandomDico(Dico, choixPartie[2]);
                G.taille = choixPartie[1];
                grille_create(&G, D.tailleDeck);
                T = Dico.leDico[D.id_depart];
                tuile_rotation(&T);
                PoserTuile(G, T, (G.taille)/2, (G.taille)/2);
                break;
            case 2:
                /*partie chargé*/
                D = Jeu_init_fichier("./sauvegardes/Partie3.txt", &G);
                T = Dico.leDico[D.id_depart];
                tuile_rotation(&T);
                PoserTuile(G, T, (G.taille)/2, (G.taille)/2);
                break;
        }
        int status = 0;
        int result;
        int continuer  = 1;
        int X,Y;
        X = 0;
        Y = 0;
        int pos[2];
        pos[0]=0;
        pos[1]=0;
        int idIndex = 0; // Ajout Kevin
        tuile Current = Dico.leDico[0];
        while(continuer){
            
            /* Test de fin de partie */
            if (test_fin(D, G, Dico, Historique)==0){
               
                status=3;              
            } 
            //Affiche_Deck(Dico,D,Historique);
            afficheGrilleD(ecran, G);
            afficheDeckSDL(ecran, Dico, D, Historique,idIndex);
            afficheTxt(ecran,G, vie, status);
            AfficheVoyant(ecran, G, Current,X,Y,status);
            //AfficheRectTuile(ecran,X,Y,1,1);
            afficheTraitDelimitation(ecran);
            if (status ==1){
                afficheTuileSDL(ecran,(14+(X*44)),14+(Y*44),Current);
                afficeSiPossible(ecran,G,Current,X,Y);    
                }
            if (status ==2){
                afficheDeckPleinEcran(ecran,D,Dico,Historique);
            }
           if (status ==3){
                 FindePartie(ecran,calculScore(G));
                free(Historique);
           }
            SDL_Flip(ecran);
  
            result = pause(pos);
            int coord[2];
            switch(status){
                
                /*FB 1, FH 2,Enter 3, FG 4, FD 5, H 6,D 7,O 8, R 9*/
                case 0:
                    /*Choix Tuile */
                    switch(result){
                        case 3:
                            status=1;
                            Current = Dico.leDico[D.deckTuiles[idIndex]];
                            break;
                        case 4:
                            if (PremierCarteDeck(D,Historique,idIndex)==0){
                                idIndex=premiereCarteAvant(D,Historique,idIndex);
                            }
                            break;
                        case 5:
                            
                            if(DerniereCarteDeck(D,Historique,idIndex)==0){
                                idIndex=premiereCarteApres(D,Historique,idIndex);
                             }
                            break;
                        case 6:
                            if(vie >= 1){
                                vie--;
                                solveurMaxTypeTerrain(&G,D,Dico,Historique);
                                afficheTxt(ecran, G, vie, status);
                            }
                            break;
                        case 7:
                            status = 2;
                            break;
                        case 10:
                            switch(locationSouris(pos)){
                                case 1:
                                    /*Fleche gauche */ 
                                    if (PremierCarteDeck(D,Historique,idIndex)==0){
                                        idIndex=premiereCarteAvant(D,Historique,idIndex);
                                    }
                                    break;
                                case 2:
                                    if(DerniereCarteDeck(D,Historique,idIndex)==0){
                                        idIndex=premiereCarteApres(D,Historique,idIndex);
                                    }
                                    /*Fleche Droite */
                                    break;
                                case 3:
                                    
                                    status=1;
                                    Current = Dico.leDico[D.deckTuiles[idIndex]];
                                    /* clic sur la tuile*/
                                    break;
                            }       
                            break;
                        case -1: 

                            continuer=0;
                            break;
                    }
                    break;
                case 1:
                    /*pose tuile sur grille 
                    void afficeSiPossible(SDL_Surface *ecran, grilleDeJeu G, tuile T, int X, int Y){
                    */
                    
                        switch(result){
                            case 1:
                                if(RentreDansLaGrille(G,X,Y+1,Current)){
                                    Y ++;
                                }
                                break;
                            case 2:
                                if(RentreDansLaGrille(G,X,Y-1,Current)){
                                    Y --;
                                }
                                break;
                            case 3:
                            /*verifSiPossible(grilleDeJeu G, tuile T, int X, int Y) */
                                if(verifSiPossible(G,Current,X,Y)){
                                    PoserTuileAvecTest(&G,Current,X,Y, Historique);
                                    if (VerifieDerniereTuile(D,Historique)==-1){
                                        if (PremierCarteDeck(D,Historique,idIndex)){
                                                idIndex=premiereCarteApres(D,Historique,idIndex);
                                            }
                                            else{
                                                
                                                idIndex=premiereCarteAvant(D,Historique,idIndex);
                                             
                                            }
                                        }else{
                                            
                                            idIndex=VerifieDerniereTuile(D,Historique);
                                           
                                        }
                                        status=0;
                                    }
                                break;
                            case 4:
                                if(RentreDansLaGrille(G,X-1,Y,Current)){
                                    X --;
                                }
                                break;
                            case 5:
                                if(RentreDansLaGrille(G,X+1,Y,Current)){
                                    X ++;
                                }
                                break;
                            case 8:
                                coord[0]=X;
                                coord[1]=Y;
                                gereOrientation(G,Current,coord);
                                X=coord[0];
                                Y=coord[1];
                               
                                tuile_rotation(&Current);
                                break;
                            case 10:
                               sourisDansGrille(pos,G);
                                if (pos[0]!=-1){
                                    CorrigeVal(G,pos,Current);
                                    X=pos[0];
                                    Y=pos[1];
                                    if(verifSiPossible(G,Current,X,Y)){
                                        PoserTuileAvecTest(&G,Current,X,Y, Historique);
                                    if (VerifieDerniereTuile(D,Historique)==-1){
                                        if (PremierCarteDeck(D,Historique,idIndex)){
                                                idIndex=premiereCarteApres(D,Historique,idIndex);
                                            }
                                            else{    
                                                idIndex=premiereCarteAvant(D,Historique,idIndex);
                                            }
                                        }else{
                                            idIndex=VerifieDerniereTuile(D,Historique);
                                            
                                        }
                                        status=0;
                                    }
                                }
                                break;
                            case 11:
                                sourisDansGrille(pos,G);
                                if (pos[0]!=-1){
                                    CorrigeVal(G,pos,Current);
                                    X=pos[0];
                                    Y=pos[1];}
                              
                                break;
                            case -1: 
                                continuer=0;
                                break;
                        }

                    break;
                case 2:
                    /*Affichage plein écran du deck */
                    status = 0;
                    break;
                case 3:
                    continuer=0; 
                    break;
                default:
                    break;
            }
          
        }
        Mix_FreeMusic(musique);

        /* LES FREES */
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

        quitSDL(); 
    
    }else{
        Mix_FreeMusic(musique);
        quitSDL();
    }
}