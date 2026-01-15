#ifndef JEU_H
#define JEU_H

#include "types.h"

int deplacerSerpent(Jeu* jeu, char direction);
void initialiserJeu(Jeu* jeu, const char* nomCarte);
void libererJeu(Jeu* jeu);

#endif