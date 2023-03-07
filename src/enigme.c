#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "enigme.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define ENIGME_WIDTH 400
#define ENIGME_HEIGHT 300
#define ANSWER_WIDTH 200
#define ANSWER_HEIGHT 50
#define FONT_SIZE 24


// each text file have 10 lines  print random lines (four text files one for question and three for answers(were answer 1 is correct and have the same line number of question text file and answer2 and 3 are false  )) and one for the enigmebackground
void afficherEnigme(enigme e, SDL_Surface *screen)
{
   // load font 
    TTF_Font *font = TTF_OpenFont("font.ttf", FONT_SIZE);
    if (font == NULL)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }
    // load enigmebackground
    SDL_Surface *enigmebackground = IMG_Load("enigmebackground.png");
    if (enigmebackground == NULL)
    {
        printf("IMG_Load: %s\n", IMG_GetError());
    }
    // load question
    SDL_Surface *question = TTF_RenderText_Solid(font, e.question, e.color);
    if (question == NULL)
    {
        printf("TTF_RenderText_Solid: %s\n", TTF_GetError());
    }
    // load answer1
    SDL_Surface *reponse1 = TTF_RenderText_Solid(font, e.reponse1, e.color);
    if (reponse1 == NULL)
    {
        printf("TTF_RenderText_Solid: %s\n", TTF_GetError());
    }
    // load answer2
    SDL_Surface *reponse2 = TTF_RenderText_Solid(font, e.reponse2, e.color);
    if (reponse2 == NULL)
    {
        printf("TTF_RenderText_Solid: %s\n", TTF_GetError());
    }
    // load answer3
    SDL_Surface *reponse3 = TTF_RenderText_Solid(font, e.reponse3, e.color);
    if (reponse3 == NULL)
    {
        printf("TTF_RenderText_Solid: %s\n", TTF_GetError());
    }
    // draw enigmebackground
    SDL_Rect position_enigmebackground;
    position_enigmebackground.x = (SCREEN_WIDTH - ENIGME_WIDTH) / 2;
    position_enigmebackground.y = (SCREEN_HEIGHT - ENIGME_HEIGHT) / 2;
    SDL_BlitSurface(enigmebackground, NULL, screen, &position_enigmebackground);
    // draw question
    SDL_Rect position_question;
    position_question.x = (SCREEN_WIDTH - ENIGME_WIDTH) / 2;
    position_question.y = (SCREEN_HEIGHT - ENIGME_HEIGHT) / 2;
    SDL_BlitSurface(question, NULL, screen, &position_question);
    // draw answer1
    SDL_Rect position_reponse1;
    position_reponse1.x = (SCREEN_WIDTH - ANSWER_WIDTH) / 2;
    position_reponse1.y = (SCREEN_HEIGHT - ANSWER_HEIGHT) / 2 + 100;
    SDL_BlitSurface(reponse1, NULL, screen, &position_reponse1);
    // draw answer2
    SDL_Rect position_reponse2;
    position_reponse2.x = (SCREEN_WIDTH - ANSWER_WIDTH) / 2;
    position_reponse2.y = (SCREEN_HEIGHT - ANSWER_HEIGHT) / 2 + 150;
    SDL_BlitSurface(reponse2, NULL, screen, &position_reponse2);
    // draw answer3
    SDL_Rect position_reponse3;
    position_reponse3.x = (SCREEN_WIDTH - ANSWER_WIDTH) / 2;
    position_reponse3.y = (SCREEN_HEIGHT - ANSWER_HEIGHT) / 2 + 200;
    SDL_BlitSurface(reponse3, NULL, screen, &position_reponse3);
    // free surfaces
    SDL_FreeSurface(enigmebackground);
    SDL_FreeSurface(question);
    SDL_FreeSurface(reponse1);
    SDL_FreeSurface(reponse2);
    SDL_FreeSurface(reponse3);
    // free font
    TTF_CloseFont(font);
}

void genererEnigme(enigme *e, char *filename_question, char *filename_reponse1, char *filename_reponse2, char *filename_reponse3)
{ 
    srand(time(NULL));
    int random = rand() % 10;
    FILE *fq = NULL, *fr1 = NULL, *fr2 = NULL, *fr3 = NULL;
    fq = fopen(filename_question, "r");
    fr1 = fopen(filename_reponse1, "r");
    fr2 = fopen(filename_reponse2, "r");
    fr3 = fopen(filename_reponse3, "r");
    if (fq != NULL && fr1 != NULL && fr2 != NULL && fr3 != NULL)
    {
        char line[255];
        int i = 0;
        while (fgets(line, 255, fq) != NULL)
        {
            if (i == random)
            {
                strcpy(e->question, line);
            }
            i++;
        }
        i = 0;
        while (fgets(line, 255, fr1) != NULL)
        {
            if (i == random)
            {
                strcpy(e->reponse1, line);
            }
            i++;
        }
        i = 0;
        while (fgets(line, 255, fr2) != NULL)
        {
            if (i == random)
            {
                strcpy(e->reponse2, line);
            }
            i++;
        }
        i = 0;
        while (fgets(line, 255, fr3) != NULL)
        {
            if (i == random)
            {
                strcpy(e->reponse3, line);
            }
            i++;
        }
        fclose(fq);
        fclose(fr1);
        fclose(fr2);
        fclose(fr3);
    }
}

// save and load enigma submenu

void sauvegarder(personne p, background b, char *filename)
{ 
    FILE *f = NULL;
    f = fopen(filename, "w");
    if (f != NULL)
    {
        fprintf(f

    }

}

void charger(personne *p, background *b, char *filename)
{

}





