#include <stdlib.h>
#include "../header/serpent.h"

Serpent creerSerpent(int x, int y) {
    Serpent serpent;
    serpent.tete = (Cellule*)malloc(sizeof(Cellule));
    serpent.tete->x = x;
    serpent.tete->y = y;
    serpent.tete->lettre = 'z';
    serpent.tete->suivant = NULL;
    serpent.longueur = 1;
    return serpent;
}

void ajouterTete(Serpent* serpent, int x, int y, char lettre) {
    Cellule* nouvelleTete = (Cellule*)malloc(sizeof(Cellule));
    nouvelleTete->x = x;
    nouvelleTete->y = y;
    nouvelleTete->lettre = lettre;
    nouvelleTete->suivant = serpent->tete;
    serpent->tete = nouvelleTete;
    serpent->longueur++;
}

void supprimerQueue(Serpent* serpent) {
    if (serpent->longueur <= 1) return;
    
    Cellule* avant = serpent->tete;
    while (avant->suivant && avant->suivant->suivant) {
        avant = avant->suivant;
    }
    
    if (avant->suivant) {
        free(avant->suivant);
        avant->suivant = NULL;
        serpent->longueur--;
    }
}

void libererSerpent(Serpent* serpent) {
    Cellule* current = serpent->tete;
    while (current) {
        Cellule* temp = current;
        current = current->suivant;
        free(temp);
    }
    serpent->tete = NULL;
    serpent->longueur = 0;
}

int verifierCollision(Serpent* serpent, int x, int y) {
    Cellule* current = serpent->tete;
    while (current) {
        if (current->x == x && current->y == y) {
            return 1;
        }
        current = current->suivant;
    }
    return 0;
}
