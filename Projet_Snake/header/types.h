#ifndef TYPES_H
#define TYPES_H

#define MAX_BONUS_LIFE 10

typedef struct Cellule {
    int x;
    int y;
    char lettre;
    struct Cellule* suivant;
} Cellule;

typedef struct {
    Cellule* tete;
    int longueur;
} Serpent;

typedef struct {
    char** grille;
    int lignes;
    int colonnes;
} Carte;

typedef struct {
    int x;
    int y;
    char lettre;
    int vie;
    int actif;
} Bonus;

typedef struct {
    Carte carte;
    Serpent serpent;
    Bonus bonus;
    int score;
    int perdu;
} Jeu;

#endif
