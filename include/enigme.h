#ifndef ENIGMA_H
#define ENIGMA_H

#include <SDL/SDL.h>

typedef struct enigme
{
    char question[100];
    char reponse1[50];
    char reponse2[50];
    char reponse3[50];
    int correct_answer;
    SDL_Surface *enigme_surf;
    SDL_Rect enigme_pos;
} enigme;

typedef struct personne
{
    char nom[20];
    int score;
} personne;

typedef struct background
{
    SDL_Surface *bg_surf;
    SDL_Rect bg_pos;
} background;

typedef struct puzzle
{
    char question[100];
    char reponse1[50];
    char reponse2[50];
    char reponse3[50];
} puzzle;

void afficherEnigme(enigme e, SDL_Surface *screen);
/* This function displays the puzzle on the given screen surface. */

void genererEnigme(puzzle *p, char *nomfichier);
/* This function randomly generates a puzzle by selecting a line from the given file as the question and 
   three other random lines as the possible answers, with the correct answer also chosen randomly. */

void sauvegarder(personne p, background b, char *filename);
/* This function saves the current game state, including the player's name and score and the background image, 
   to the given file. */

void charger(personne *p, background *b, char *filename);
/* This function loads the game state from the given file, updating the player's name and score and the background image. */

void animerEnigme(enigme *e);
/* This function animates the puzzle by swapping its surface's red and blue color channels. */

#endif /* ENIGMA_H */
