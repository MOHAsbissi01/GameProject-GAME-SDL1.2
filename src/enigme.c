#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "enigma.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define ENIGME_WIDTH 400
#define ENIGME_HEIGHT 300
#define ANSWER_WIDTH 200
#define ANSWER_HEIGHT 50
#define FONT_SIZE 24

void afficherEnigme(enigme e, SDL_Surface *screen)
{
    // Load the puzzle surface
    SDL_Surface *puzzle_surf = e.enigme_surf;
    
    // Set the position of the puzzle surface on the screen
    SDL_Rect puzzle_pos;
    puzzle_pos.x = e.enigme_pos.x;
    puzzle_pos.y = e.enigme_pos.y;
    
    // Blit the puzzle surface onto the screen
    SDL_BlitSurface(puzzle_surf, NULL, screen, &puzzle_pos);
    
    // Update the screen
    SDL_Flip(screen);
}

void genererEnigme(puzzle *p, char *nomfichier)
{
    // Open the file for reading
    FILE *f = fopen(nomfichier, "r");
    if (f == NULL) {
        fprintf(stderr, "Error: failed to open file '%s'\n", nomfichier);
        exit(1);
    }
    
    // Count the number of lines in the file
    int num_lines = 0;
    char ch;
    while (!feof(f)) {
        ch = fgetc(f);
        if (ch == '\n') {
            num_lines++;
        }
    }
    rewind(f);
    
    // Select a random line as the question
    int question_line = rand() % num_lines;
    for (int i = 0; i < question_line; i++) {
        fgets(p->question, sizeof(p->question), f);
    }
    fgets(p->question, sizeof(p->question), f);
    if (p->question[strlen(p->question)-1] == '\n') {
        p->question[strlen(p->question)-1] = '\0';
    }
    
    // Select three random lines as the possible answers
    int answer_lines[3];
    answer_lines[0] = rand() % num_lines;
    answer_lines[1] = rand() % num_lines;
    answer_lines[2] = rand() % num_lines;
    while (answer_lines[0] == question_line || answer_lines[1] == question_line || answer_lines[2] == question_line ||
           answer_lines[0] == answer_lines[1] || answer_lines[0] == answer_lines[2] || answer_lines[1] == answer_lines[2]) {
        answer_lines[0] = rand() % num_lines;
        answer_lines[1] = rand() % num_lines;
        answer_lines[2] = rand() % num_lines;
    }
    rewind(f); // Reset the file pointer ; why? ,because we need to read the file from the beginning
    for (int i = 0; i < answer_lines[0]; i++) {
        fgets(p->reponse1, sizeof(p->reponse1), f);
    }
    fgets(p->reponse1, sizeof(p->reponse1), f);
    if (p->reponse1[strlen(p->reponse1)-1] == '\n') {
        p->reponse1[strlen(p->reponse1)-1] = '\0';
    }
    for (int i = 0; i < answer_lines[1]; i++) {
        fgets(p->reponse2, sizeof(p->reponse2), f);
    }
    fgets(p->reponse2, sizeof(p->reponse2), f);
    if (p->reponse2[strlen(p->reponse2)-1] == '\n') {
        p->reponse2[strlen(p->reponse2)-1] = '\0';
    }
    for (int i = 0; i < answer_lines[2]; i++) {
        fgets(p->reponse3, sizeof(p->reponse3), f);
    }
    fgets(p->reponse3, sizeof(p->reponse3), f);
    if (p->reponse3[strlen(p->reponse3)-1] == '\n') {
        p->reponse3[strlen(p->reponse3)-1] = '\0';
    }
    
    // Close the file
    fclose(f);
    
        // Randomly shuffle the answers
    char *answers[3] = { p->reponse1, p->reponse2, p->reponse3 };
    for (int i = 2; i >= 0; i--) {
        int j = rand() % (i+1);
        char *temp = answers[i];
        answers[i] = answers[j];
        answers[j] = temp;
    }
    strcpy(p->reponse1, answers[0]);
    strcpy(p->reponse2, answers[1]);
    strcpy(p->reponse3, answers[2]);
        // Select a random line for the question and correct answer
    num_lines = count_lines(nomfichier);
    question_line = rand() % num_lines + 1;
    int answer_line = rand() % num_lines + 1;
    while (answer_line == question_line) {
        answer_line = rand() % num_lines + 1;
    }
    
    // Extract the question and correct answer from the selected lines
    FILE *file = fopen(nomfichier, "r");
    char line[100];
    int current_line = 0;
    while (fgets(line, sizeof(line), file)) {
        current_line++;
        if (current_line == question_line) {
            strcpy(p->question, line);
            strtok(p->question, "\n"); // remove trailing newline
            
        }
        if (current_line == answer_line) {
            strcpy(p->reponse_correcte, line);
            strtok(p->reponse_correcte, "\n"); // remove trailing newline
        }
        if (current_line == num_lines) {
            break; // stop reading the file after the last line
        }
    }
    fclose(file);

}