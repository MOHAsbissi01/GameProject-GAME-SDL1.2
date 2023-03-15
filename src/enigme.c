#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "enigme.h"
#define MAX_LEN 18 

void afficherEnigme(Enigme e, SDL_Surface *screen) {
    SDL_BlitSurface(e.question_surf, NULL, screen, &e.question_pos);
    SDL_BlitSurface(e.reponse1_surf, NULL, screen, &e.reponse1_pos);
    SDL_BlitSurface(e.reponse2_surf, NULL, screen, &e.reponse2_pos);
    SDL_BlitSurface(e.reponse3_surf, NULL, screen, &e.reponse3_pos);
    SDL_Flip(screen);
}
void genererEnigme(Enigme *p, char *nomfichier) {
    // ouvrir le fichier en mode lecture
    FILE* fichier = fopen(nomfichier, "r");

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s.\n", nomfichier);
        exit(EXIT_FAILURE);
    }

    // compter le nombre de lignes dans le fichier
    int nb_lignes = 0;
    char c;
    while ((c = fgetc(fichier)) != EOF) {
        if (c == '\n') {
            nb_lignes++;
        }
    }

    // choisir aléatoirement une ligne pour l'énigme
    srand(time(NULL)); // initialiser le générateur de nombres aléatoires
    int ligne_aleatoire = rand() % (nb_lignes / 4) + 1;

    // se placer à la ligne correspondante dans le fichier
    fseek(fichier, (ligne_aleatoire - 1) * 4 * MAX_LEN, SEEK_SET);

    // lire les 4 lignes correspondant à l'énigme
    char question[MAX_LEN], reponse1[MAX_LEN], reponse2[MAX_LEN], reponse3[MAX_LEN];
    int numbr;
    fscanf(fichier, "question: %s\n", question);
    fscanf(fichier, "reponse1: %s\n", reponse1);
    fscanf(fichier, "reponse2: %s\n", reponse2);
    fscanf(fichier, "reponse3: %s\n", reponse3);
    fscanf(fichier, "numbr: %d\n", &numbr);

    // fermer le fichier
    fclose(fichier);

    // initialiser la structure Enigme
    p->question = question;
    p->reponse1 = reponse1;
    p->reponse2 = reponse2;
    p->reponse3 = reponse3;
    p->numbr = numbr;
    p->etat = 0; // non encore résolu
  
    // initialiser les positions des surfaces
    p->question_pos.x = 0;
    p->question_pos.y = 0;
    p->reponse1_pos.x = 0;
    p->reponse1_pos.y = 100;
    p->reponse2_pos.x = 0;
    p->reponse2_pos.y = 200;
    p->reponse3_pos.x = 0;
    p->reponse3_pos.y = 300;
    //white color
    p->question_color = (SDL_Color) { 255, 255, 255, 255 };
    p->reponse_color = (SDL_Color) { 255, 255, 255, 255 };
    p->reponse_color = (SDL_Color) { 255, 255, 255, 255 };
    p->reponse_color = (SDL_Color) { 255, 255, 255, 255 };

    /* Initialiser les surfaces de texte */
    p->question_surf = TTF_RenderText_Blended(p->font, p->question, p->question_color);
    p->reponse1_surf = TTF_RenderText_Blended(p->font, p->reponse1, p->reponse_color);
    p->reponse2_surf = TTF_RenderText_Blended(p->font, p->reponse2, p->reponse_color);
    p->reponse3_surf = TTF_RenderText_Blended(p->font, p->reponse3, p->reponse_color);

    /* Initialiser l'état de l'énigme */
        p->etat = 0;
}



s