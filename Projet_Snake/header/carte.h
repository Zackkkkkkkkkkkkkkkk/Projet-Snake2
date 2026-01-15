#ifndef CARTE_H
#define CARTE_H

#include "types.h"

Carte chargerCarte(const char* nomFichier);
void libererCarte(Carte* carte);
void afficherCarte(Jeu* jeu);

#endif
