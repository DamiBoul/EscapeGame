#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, char** argv){

    //Initialisation des variables
    SDL_Window *pWindow=NULL;
    SDL_Surface *pSurfaceImg=NULL;
    SDL_Renderer *pRenderer=NULL;
    SDL_Rect ImgRectF, ImgRectP;
    SDL_Texture *pTextureImgF=NULL, *pTextureImgP=NULL;
    SDL_Event event;
    SDL_bool program_launched = 1;

    //Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("Echec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }

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
    pSurfaceImg=IMG_Load("fond.png");
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
    pSurfaceImg=IMG_Load("pika.png");
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
        
            switch(event.type){
                
                case SDL_QUIT :
                    SDL_Quit();
                    return(0);
                    break;

                case SDL_KEYDOWN :
                    switch(event.key.keysym.sym){

                        case SDLK_UP :
                            ImgRectP.y--;
                            SDL_RenderCopy(pRenderer,pTextureImgP,NULL,&ImgRectP);
                            break;

                        case SDLK_DOWN :
                            ImgRectP.y++;
                            SDL_RenderCopy(pRenderer,pTextureImgP,NULL,&ImgRectP);
                            break;

                        case SDLK_LEFT :
                            ImgRectP.x--;
                            SDL_RenderCopy(pRenderer,pTextureImgP,NULL,&ImgRectP);
                            break;

                        case SDLK_RIGHT :
                            ImgRectP.x++;
                            SDL_RenderCopy(pRenderer,pTextureImgP,NULL,&ImgRectP);
                            break;

                    }

                default :
                    SDL_RenderCopy(pRenderer,pTextureImgP,NULL,&ImgRectP);
                    break;
            }


        //Affichage du rendu à l'utilisateur
        SDL_Delay(5);
        SDL_RenderPresent(pRenderer);

        }
    }

    SDL_Quit();
    return(0);
}
