#ifndef MENU_H
#define MENU_H

#include "types.h"

void afficherMenu();
void sauvegarderJeu(Jeu* jeu, const char* nomFichier);
Jeu chargerJeu(const char* nomFichier);
void viderBuffer();

#endif