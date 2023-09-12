
#include "../lib/suis_souris.h"

void TestAffichage(){

    //Initialisation des variables
    SDL_Window *pWindow=NULL;
    SDL_Surface *pSurfaceImg=NULL;
    SDL_Renderer *pRenderer=NULL;
    SDL_Rect ImgRectF, ImgRectP;
    SDL_Texture *pTextureImgF=NULL, *pTextureImgP=NULL;
    SDL_Event event;
    SDL_bool program_launched = 1;

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
        
            switch(event.type){
                
                case SDL_QUIT :
                    SDL_Quit();
                    return(NULL);
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

}

void TestMatrice(){

    //Déclaration de variables
    char nom_fichier[60] = "src/img/encore.png";
    SDL_Surface *imageSurface;
    Uint32 *pixels;
    //Uint32 pixel;
    int width, height;
    Uint8 **rmatrix, **gmatrix, **bmatrix, **amatrix;

    //Chargement de l'image
    imageSurface = IMG_Load(nom_fichier);

    //Mise en lecture de pixel
    SDL_LockSurface(imageSurface);
    pixels = (Uint32*)imageSurface->pixels;
    width = imageSurface->w;
    height = imageSurface->h;

    //Initialisation des matrices
    rmatrix = malloc(height * width * sizeof(Uint8*));
    gmatrix = malloc(height * width * sizeof(Uint8*));
    bmatrix = malloc(height * width * sizeof(Uint8*));
    amatrix = malloc(height * width * sizeof(Uint8*));

    //Attribution des pixels aux matrices
    int i;
    for(i=0;i<width*height;i++){
        SDL_GetRGBA(pixels[i], imageSurface->format, rmatrix[i], gmatrix[i], bmatrix[i], amatrix[i]);
    }

    //Affichage des matrices
    for(i=0;i<width*height;i++){
        printf("Pixel Color -> R: %d,  G: %d,  B: %d,  A: %d\n", *(rmatrix[i]), *(gmatrix[i]), *(bmatrix[i]), *(amatrix[i]));
    }

    //Nettoyage memoire
    for(i=0;i<height*width;i++){
        free(rmatrix[i]);
        free(gmatrix[i]);
        free(bmatrix[i]);
        free(amatrix[i]);
    }
    free(rmatrix);
    free(gmatrix);
    free(bmatrix);
    free(amatrix);

//Ancienne méthode
/*
    //Initialisation de la matrice
    matrix = malloc(height * sizeof(Uint32*));
    
    int i;
    for(i=0;i<height;i++){
        matrix[i] = malloc(width * sizeof(Uint32));
        memcpy(matrix[i], pixels + i * width, width * sizeof(Uint32));
    }

    //Affichage de la matrice
    int j;
    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            pixel=matrix[i][j];
            printf("%08X | ", pixel);
        }
        printf("\n");
    }

    //Nettoyage memoire
    for(i=0;i<height;i++){
        free(matrix[i]);
    }
    free(matrix);
*/
    SDL_UnlockSurface(imageSurface);
    SDL_FreeSurface(imageSurface);


}


SDL_Color GetPixelColor(const SDL_Surface* pSurface, const int X, const int Y){

    // Bytes per pixel
    const Uint8 Bpp = pSurface->format->BytesPerPixel;

    /*
    Retrieve the address to a specific pixel
    pSurface->pixels	= an array containing the SDL_Surface' pixels
    pSurface->pitch		= the length of a row of pixels (in bytes)
    X and Y				= the offset on where on the image to retrieve the pixel, (0, 0) is in the upper left corner of the image
    */
    Uint8* pPixel = (Uint8*)pSurface->pixels + Y * pSurface->pitch + X * Bpp;

    Uint32 PixelData = *(Uint32*)pPixel;

    SDL_Color Color = {0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE};

    // Retrieve the RGB values of the specific pixel
    SDL_GetRGB(PixelData, pSurface->format, &Color.r, &Color.g, &Color.b);

    return Color;
}

void TestMatriceGuide(){
    
    SDL_Surface* pSurface = IMG_Load("src/img/t.png");
    int w, h, x, y;
    SDL_Color Color;

    SDL_LockSurface(pSurface);
    w = pSurface->w;
    h = pSurface->h;

    for(x=0;x<w;x++){
        for(y=0;y<h;y++){
            // Offset (x, y) in the image/surface
            Color = GetPixelColor(pSurface, x, y);

            
            printf("The pixel at (%i,%i) has r = %i, g = %i, b = %i \n",x,y,Color.r,Color.g,Color.b);
                
        }
    }

    SDL_UnlockSurface(pSurface);
    SDL_FreeSurface(pSurface);


}

void ImgToMatrix_1(int hauteur, int largeur, char nom_img[60]){
    
    SDL_Surface *pImg = IMG_Load(nom_img);
    SDL_Color Color;
    int mat[hauteur][largeur];
    int i,j,w,h;
    int r,g,b;

    SDL_LockSurface(pImg);
    w = pImg->w;
    h = pImg->h;

    //Création matrice
    for(i=0;i<w;i++){
        for(j=0;j<h;j++){
            
            // Offset (x, y) in the image/surface
            Color = GetPixelColor(pImg, i, j);
            
            r = Color.r; g = Color.g; b = Color.b;

            if((r == 0) && (g == 0) && (b == 0)){
                mat[j][i]=0;
            }
            else if((r == 255) && (g == 255) && (b == 255)){
                mat[j][i]=1;
            }
            else if((r == 255) && (g == 0) && (b == 0)){
                mat[j][i]=2;
            }
            else{
                mat[j][i]=-1;
            }

                
        }
    }

    //Affichage matrice
    for(i=0;i<h;i++){
        printf("| ");
        for(j=0;j<w;j++){
            printf(" %i ",mat[i][j]);
        }
        printf(" |\n");
    }

    SDL_UnlockSurface(pImg);
    SDL_FreeSurface(pImg);


}

void TestImgToMatrix(){
    ImgToMatrix_1(10,10,"src/img/t.png");
}

void ImgToMatrix_2(SDL_Surface *pSurface, int mat[pSurface->h][pSurface->w]){
    
    SDL_Color Color;
    int i,j,w,h;
    int r,g,b;

    w = pSurface->w;
    h = pSurface->h;

    //Création matrice
    for(i=0;i<w;i++){
        for(j=0;j<h;j++){
            
            // Offset (x, y) in the image/surface
            Color = GetPixelColor(pSurface, i, j);
            
            r = Color.r; g = Color.g; b = Color.b;

            if((r == 0) && (g == 0) && (b == 0)){
                mat[j][i]=0;
            }
            else if((r == 255) && (g == 255) && (b == 255)){
                mat[j][i]=1;
            }
            else if((r == 255) && (g == 0) && (b == 0)){
                mat[j][i]=2;
            }
            else{
                mat[j][i]=-1;
            }

                
        }
    }


}

void TestImgToMatrixVariable(){

    char nom_img[60];
    int w,h;
    int i,j;

    printf("Entrez l'emplacement du fichier image à traduire en matrice : ");
    scanf("%s",nom_img);

    SDL_Surface *pImg = IMG_Load(nom_img);
    SDL_LockSurface(pImg);
    w = pImg->w;
    h = pImg->h;

    int mat[h][w];

    ImgToMatrix_2(pImg,mat);

    //Affichage matrice
    for(i=0;i<h;i++){
        printf("| ");
        for(j=0;j<w;j++){
            printf(" %i ",mat[i][j]);
        }
        printf(" |\n");
    }

    SDL_UnlockSurface(pImg);
    SDL_FreeSurface(pImg);



}

int main(int argc, char** argv){

    
    //Initialisations
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    int action;

    printf("Quelle action voulez-vous faire ?\n1 - Affichage SDL\n2 -  test raté de .png to matrix\n3 - .png to color version copiée\n4 - .png to matrix\n5 - .png to matrix avec taille variable\n6 - Test image suis souris\n");
    scanf("%i",&action);

    switch(action){
        case 1:TestAffichage();break;
        case 2:TestMatrice();break;
        case 3:TestMatriceGuide();break;
        case 4:TestImgToMatrix();break;
        case 5:TestImgToMatrixVariable();break;
        case 6:TestSouris();break;
        default : printf("Erreur pas d'action correspondante");break;
    }

    IMG_Quit();
    SDL_Quit();

    return(0);
}
