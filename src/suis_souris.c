#include "../lib/suis_souris.h"

void TestSouris(){

    //Initialisation des variables
    SDL_Window *pWindow=NULL;
    SDL_Surface *pSurfaceImg=NULL;
    SDL_Renderer *pRenderer=NULL;
    SDL_Rect ImgRectF, ImgRectP;
    SDL_Texture *pTextureImgF=NULL, *pTextureImgP=NULL;
    SDL_Event event;
    SDL_bool program_launched = 1;

    int suis_souris_bool = 0;
    //int souris_pos_x,souris_pos_y; 

    //Création de la fenêtre
    pWindow = SDL_CreateWindow("Test d'affichage Pikachu",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, 720, 720, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);

    if(!pWindow){
        printf("Erreur à la création de la fenêtre : (%s)\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    //Création du rendu
    pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
    if(pRenderer == NULL){
        printf("Erreur à la création du rendu : (%s)\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    //Image Fond
    //Chargement de l'image version Lucie
    pSurfaceImg=IMG_Load("src/img/fond.png");
    if(!pSurfaceImg){
        printf("Erreur au chargement de l'image : (%s)\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    //Application de l'image à la texture
    pTextureImgF=SDL_CreateTextureFromSurface(pRenderer,pSurfaceImg);
    if(!pTextureImgF){
        printf("Erreur à la création de la texture : (%s)\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_FreeSurface(pSurfaceImg);


    //Positionnement du rectangle pour l'image
    ImgRectF.x=0;
    ImgRectF.y=0;
    ImgRectF.h=720;
    ImgRectF.w=720;

    //Ajout de l'image de l'image
    SDL_QueryTexture(pTextureImgF, NULL, NULL, &(ImgRectF.w), &(ImgRectF.h));
    SDL_RenderCopy(pRenderer,pTextureImgF,NULL,&ImgRectF);

    //Image Pikachu
    //Chargement de l'image version Lucie
    pSurfaceImg=IMG_Load("src/img/pika.png");
    if(!pSurfaceImg){
        printf("Erreur au chargement de l'image : (%s)\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    //Application de l'image à la texture
    pTextureImgP=SDL_CreateTextureFromSurface(pRenderer,pSurfaceImg);
    if(!pTextureImgP){
        printf("Erreur à la création de la texture : (%s)\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_FreeSurface(pSurfaceImg);


    //Positionnement du rectangle pour l'image
    ImgRectP.x=100;
    ImgRectP.y=100;

    //Ajout de l'image de l'image
    SDL_QueryTexture(pTextureImgP, NULL, NULL, &(ImgRectP.w), &(ImgRectP.h));
    ImgRectP.h=100;
    ImgRectP.w=100;
    SDL_RenderCopy(pRenderer,pTextureImgP,NULL,&ImgRectP);

    //Création de la boucle d'évènement
    while(program_launched){
        while(SDL_PollEvent(&event)){

            SDL_RenderClear(pRenderer);
            SDL_RenderCopy(pRenderer,pTextureImgF,NULL,&ImgRectF); 
            SDL_RenderCopy(pRenderer,pTextureImgP,NULL,&ImgRectP);
        
            switch(event.type){
                
                case SDL_QUIT :
                    SDL_Quit();
                    return(NULL);
                    break;

                case SDL_MOUSEBUTTONDOWN :
                    switch(event.button.button){

                        case SDL_BUTTON_LEFT :
                        if(event.button.x>ImgRectP.x && event.button.x<ImgRectP.x+ImgRectP.w && event.button.y>ImgRectP.y && event.button.y<ImgRectP.y+ImgRectP.h){
                            suis_souris_bool=1;
                            //souris_pos_x=event.button.x;
                            //souris_pos_y=event.button.y;
                        }
                        break;
                        
                        default : break;

                    }
                    break;

                case SDL_MOUSEMOTION :
                    if (suis_souris_bool) {

                        ImgRectP.x=ImgRectP.x+event.motion.xrel;//-souris_pos_x;
                        ImgRectP.y=ImgRectP.y+event.motion.yrel;//-souris_pos_y;
                        //souris_pos_x=event.motion.x;
                        //souris_pos_y=event.motion.y;

                    }

                    break;
                
                case SDL_MOUSEBUTTONUP :
                    switch(event.button.button){

                        case SDL_BUTTON_LEFT :
                                suis_souris_bool=0;
                                break;

                        default : break;

                    }
                break;
            }


        //Affichage du rendu à l'utilisateur
        //SDL_Delay(5);
        SDL_RenderPresent(pRenderer);

        }
    }

}
