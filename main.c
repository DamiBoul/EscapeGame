#include "../__BIBLIOTHEQUE/gen.h"
#define SCREEN_HW 700

int main (void){
    SDL_Window * window = NULL ;
    SDL_Renderer * renderer = NULL ;

    if (SDL_Initialisation(&window, &renderer, SCREEN_HW) != 0){
        return 1 ;
    }

    SDL_Quit();
    return 0;
}