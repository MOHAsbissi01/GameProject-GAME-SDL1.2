#ifndef ENIGME_H
#define ENIGME_H

typedef struct
{
    char * filename;
    
}enigme ;

void afficherEnigme(enigme e, SDL_Surface * screen)		;	
void sauvegarder (personne p, background b, char * filename;) ;
void charger ( personne * p, background *b , char * filename;)	;						

#endif