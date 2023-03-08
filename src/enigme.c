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
//--------------------------------------------------------
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

//--------------------------------------------------------

void afficherEnigme(enigme e, SDL_Surface *screen)
{
    // load font
    TTF_Font *font = TTF_OpenFont("font.ttf", FONT_SIZE);
    if (font == NULL)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        return; // Exit the function if font loading fails
    }

    // load enigmebackground
    SDL_Surface *enigmebackground = IMG_Load("enigmebackground.png");
    if (enigmebackground == NULL)
    {
        printf("IMG_Load: %s\n", IMG_GetError());
        TTF_CloseFont(font); // Free the loaded font before exiting the function
        return; // Exit the function if image loading fails
    }

    // load question
    SDL_Color textColor = { e.color.r, e.color.g, e.color.b }; // Convert enigma color to SDL_Color
    SDL_Surface *question = TTF_RenderText_Solid(font, e.question, textColor);
    if (question == NULL)
    {
        printf("TTF_RenderText_Solid: %s\n", TTF_GetError());
        SDL_FreeSurface(enigmebackground); // Free loaded surfaces before exiting the function
        TTF_CloseFont(font);
        return; // Exit the function if question loading fails
    }

    // load answer1
    SDL_Surface *reponse1 = TTF_RenderText_Solid(font, e.reponse1, textColor);
    if (reponse1 == NULL)
    {
        printf("TTF_RenderText_Solid: %s\n", TTF_GetError());
        SDL_FreeSurface(enigmebackground);
        SDL_FreeSurface(question); // Free previously loaded surfaces before exiting the function
        TTF_CloseFont(font);
        return; // Exit the function if answer1 loading fails
    }

    // load answer2
    SDL_Surface *reponse2 = TTF_RenderText_Solid(font, e.reponse2, textColor);
    if (reponse2 == NULL)
    {
        printf("TTF_RenderText_Solid: %s\n", TTF_GetError());
        SDL_FreeSurface(enigmebackground);
        SDL_FreeSurface(question);
        SDL_FreeSurface(reponse1); // Free previously loaded surfaces before exiting the function
        TTF_CloseFont(font);
        return; // Exit the function if answer2 loading fails
    }

    // load answer3
    SDL_Surface *reponse3 = TTF_RenderText_Solid(font, e.reponse3, textColor);
    if (reponse3 == NULL)
    {
        printf("TTF_RenderText_Solid: %s\n", TTF_GetError());
        SDL_FreeSurface(enigmebackground);
        SDL_FreeSurface(question);
        SDL_FreeSurface(reponse1);
        SDL_FreeSurface(reponse2); // Free previously loaded surfaces before exiting the function
        TTF_CloseFont(font);
        return; // Exit the function if answer3 loading fails
    }

    // draw enigmebackground
    SDL_Rect position_enigmebackground;
    position_enigmebackground.x = (screen->w - ENIGME_WIDTH) / 2;
    position_enigmebackground.y = (screen->h - ENIGME_HEIGHT) / 2;
    SDL_BlitSurface(enigmebackground, NULL, screen, &position_enigmebackground);

    // draw question
    SDL_Rect position_question;
    position_question.x = (screen->w - question->w) / 2;
    position_question.y = (screen->h - question->h) / 2 - 200;
    SDL_BlitSurface(question, NULL, screen, &position_question);

    // draw answer1
    SDL_Rect position_reponse1;
    position_reponse1.x = (screen->w - reponse1->w) / 2;
    position_reponse1.y = (screen->h - reponse1->h) / 2 - 100;
    SDL_BlitSurface(reponse1, NULL, screen, &position_reponse1);

    // draw answer2
    SDL_Rect position_reponse2;
    position_reponse2.x = (screen->w - reponse2->w) / 2;
    position_reponse2.y = (screen->h - reponse2->h) / 2;
    SDL_BlitSurface(reponse2, NULL, screen, &position_reponse2);

    // draw answer3
    SDL_Rect position_reponse3;
    position_reponse3.x = (screen->w - reponse3->w) / 2;
    position_reponse3.y = (screen->h - reponse3->h) / 2 + 100;
    SDL_BlitSurface(reponse3, NULL, screen, &position_reponse3);

    // free surfaces
    SDL_FreeSurface(enigmebackground);
    SDL_FreeSurface(question);
    SDL_FreeSurface(reponse1);
    SDL_FreeSurface(reponse2);
    SDL_FreeSurface(reponse3);
    TTF_CloseFont(font);
}


///--------------------------------------------------------
#include "enigma.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

void genererEnigme(enigme *e, char *filename_question, char *filename_reponse1, char *filename_reponse2, char *filename_reponse3)
{
    // Seed the random number generator
    srand(time(NULL));

    // Open the files
    FILE *fp_question = fopen(filename_question, "r");
    FILE *fp_reponse1 = fopen(filename_reponse1, "r");
    FILE *fp_reponse2 = fopen(filename_reponse2, "r");
    FILE *fp_reponse3 = fopen(filename_reponse3, "r");

    // Check if files are open
    if (fp_question == NULL || fp_reponse1 == NULL || fp_reponse2 == NULL || fp_reponse3 == NULL)
    {
        fprintf(stderr, "Error opening files!\n");
        exit(1);
    }

    // Read lines from the files and store them in arrays
    char question[100], reponse1[50], reponse2[50], reponse3[50];
    char *questions[100], *reponses[3][50];
    int num_questions = 0, num_reponses = 0;

    while (fgets(question, 100, fp_question))
    {
        // Remove newline character from the end of the line
        question[strlen(question) - 1] = '\0';

        // Store question in array
        questions[num_questions++] = strdup(question);
    }

    while (fgets(reponse1, 50, fp_reponse1) &&
           fgets(reponse2, 50, fp_reponse2) &&
           fgets(reponse3, 50, fp_reponse3))
    {
        // Remove newline character from the end of the line
        reponse1[strlen(reponse1) - 1] = '\0';
        reponse2[strlen(reponse2) - 1] = '\0';
        reponse3[strlen(reponse3) - 1] = '\0';

        // Store responses in array
        reponses[0][num_reponses] = strdup(reponse1);
        reponses[1][num_reponses] = strdup(reponse2);
        reponses[2][num_reponses++] = strdup(reponse3);
    }

    // Choose a random question and its corresponding answers
    int index = rand() % num_questions;

    strcpy(e->question_text, questions[index]);
    strcpy(e->reponse1, reponses[0][index]);
    strcpy(e->reponse2, reponses[1][index]);
    strcpy(e->reponse3, reponses[2][index]);

    // Free the dynamically allocated memory
    for (int i = 0; i < num_questions; i++)
        free(questions[i]);

    for (int i = 0; i < num_reponses; i++)
    {
        free(reponses[0][i]);
        free(reponses[1][i]);
        free(reponses[2][i]);
    }

    // Close the files
    fclose(fp_question);
    fclose(fp_reponse1);
    fclose(fp_reponse2);
    fclose(fp_reponse3);
}

///--------------------------------------------------------

void animerEnigme(enigme *e) {
    int speed = 5;
    int max_x = 800;
    int min_x = -e->position_enigmebackground.w;

    int x = e->position_enigmebackground.x;
    int y = e->position_enigmebackground.y;

    SDL_Rect src_rect = {0, 0, e->position_enigmebackground.w, e->position_enigmebackground.h};
    SDL_Rect dest_rect = {x, y, e->position_enigmebackground.w, e->position_enigmebackground.h};

    Uint32 start_time = SDL_GetTicks();

    while (SDL_GetTicks() - start_time < 5000) { // animate for 5 seconds
        SDL_Delay(20); // add a small delay to control the speed of the animation

        // move the background
        x += speed;
        if (x > max_x) {
            x = min_x;
        }
        dest_rect.x = x;

        // clear the screen
        SDL_FillRect(SDL_GetVideoSurface(), NULL, SDL_MapRGB(SDL_GetVideoSurface()->format, 255, 255, 255));

        // draw the background and other surfaces
        SDL_BlitSurface(e->enigmebackground, &src_rect, SDL_GetVideoSurface(), &dest_rect);
        SDL_BlitSurface(e->question, NULL, SDL_GetVideoSurface(), &e->position_question);
        SDL_BlitSurface(e->reponse1, NULL, SDL_GetVideoSurface(), &e->position_reponse1);
        SDL_BlitSurface(e->reponse2, NULL, SDL_GetVideoSurface(), &e->position_reponse2);
        SDL_BlitSurface(e->reponse3, NULL, SDL_GetVideoSurface(), &e->position_reponse3);

        SDL_Flip(SDL_GetVideoSurface());
    }
}


