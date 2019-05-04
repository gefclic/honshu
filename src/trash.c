  position.x = 14+(4*44);
    position.y= 14+(3*44);
    SDL_BlitSurface(IMGmaison, NULL, ecran, &position);
    position.x = 14+(5*44);
    position.y= 14+(3*44);
    SDL_BlitSurface(IMGForet, NULL, ecran, &position);
        position.x = 14+(4*44);
    position.y= 14+(4*44);
    SDL_BlitSurface(IMGlac, NULL, ecran, &position); 
        position.x = 14+(5*44);
    position.y= 14+(4*44);
    SDL_BlitSurface(IMGPrairie, NULL, ecran, &position); 
        position.x = 14+(4*44);
    position.y= 14+(5*44);
    SDL_BlitSurface(IMGUsine, NULL, ecran, &position);   
    SDL_Flip(ecran);

    int pause(){
    int continuer = 1;
    int result =0;
    SDL_Event event;
    while (continuer){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                continuer = 0;
                result=-1;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym){
                    case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
                        continuer = 0;
                        result = -1; 
                        break;
                    case SDLK_DOWN:
                        result=1;
                        continuer = 0;
                        break;
                    case SDLK_UP:
                        result = 2;
                        continuer = 0;
                        break;
                    case SDLK_RETURN:
                        result = 3;
                        continuer = 0;
                        break;
                    default:    
                    continue;
                }
            }
        }
    return result;
    }
void afficheTuileSDL(SDL_Surface *ecran, int x, int y, tuile T){
    SDL_Surface *IMGlac =NULL, *IMGmaison =NULL, *IMGForet = NULL, *IMGPrairie = NULL, *IMGUsine=NULL, *IMGRessource=NULL;
    IMGlac=IMG_Load("bin/lac.png");
    IMGmaison=IMG_Load("bin/maison.png");
    IMGForet=IMG_Load("bin/foret.png");
    IMGPrairie=IMG_Load("bin/prairie.png");
    IMGUsine=IMG_Load("bin/usine.png");
    IMGRessource=IMG_Load("bin/ressource.png");

    SDL_Rect pos_tuile;
    int i, j;
    for (i=0; i<2; i++){
        for (j=0; j<3; j++){
            pos_tuile.x = 14+((x+i)*44);
            pos_tuile.y = 14+((y+j)*44);
            switch(T.contenu[i][j]){
                case 'P':
                    SDL_BlitSurface(IMGPrairie, NULL, ecran, &pos_tuile);
                    break;
                case 'F':
                    SDL_BlitSurface(IMGForet, NULL, ecran, &pos_tuile);
                    break;
                case 'L':
                    SDL_BlitSurface(IMGlac, NULL, ecran, &pos_tuile);
                    break;
                case 'V':
                    SDL_BlitSurface(IMGmaison, NULL, ecran, &pos_tuile);
                    break;
                case 'U':
                    SDL_BlitSurface(IMGUsine, NULL, ecran, &pos_tuile);
                    break;
                case 'R':
                    SDL_BlitSurface(IMGRessource, NULL, ecran, &pos_tuile); /* A METTRE EN RESSOURCE */
                default : 
                    break;
            }
        }
    }


}
