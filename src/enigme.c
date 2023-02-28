#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "../include/enigme.h"
void afficherEnigme(enigme e, SDL_Surface * screen)			
{
    SDL_Surface * image = NULL;
    SDL_Rect position;
    position.x = 0;
    position.y = 0;
    image = SDL_LoadBMP(e.filename);
    SDL_BlitSurface(image, NULL, screen, &position);
    SDL_Flip(screen);
    SDL_FreeSurface(image);
}
void sauvegarder (personne p, background b, char * filename;)
{
    FILE * f;
    f = fopen(filename, "w");  
    if (f != NULL)
    { 



    
					
