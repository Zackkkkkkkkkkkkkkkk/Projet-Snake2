#ifndef SERPENT_H
#define SERPENT_H

#include "types.h"

Serpent creerSerpent(int x, int y);
void ajouterTete(Serpent* serpent, int x, int y, char lettre);
void supprimerQueue(Serpent* serpent);
void libererSerpent(Serpent* serpent);
int verifierCollision(Serpent* serpent, int x, int y);

#endif