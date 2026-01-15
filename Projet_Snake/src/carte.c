#include <stdio.h>
#include <stdlib.h>
#include "../header/carte.h"
#include "../header/serpent.h"

Carte chargerCarte(const char* nomFichier) {
    Carte carte;
    FILE* fichier = fopen(nomFichier, "r");
    
    if (!fichier) {
        printf("Erreur: impossible d'ouvrir %s\n", nomFichier);
        carte.grille = NULL;
        carte.lignes = 0;
        carte.colonnes = 0;
        return carte;
    }
    
    fscanf(fichier, "%d %d", &carte.lignes, &carte.colonnes);
    
    // Allocation dynamique de la matrice
    carte.grille = (char**)malloc(carte.lignes * sizeof(char*));
    for (int i = 0; i < carte.lignes; i++) {
        carte.grille[i] = (char*)malloc(carte.colonnes * sizeof(char));
    }
    
    // Lecture de la carte
    for (int i = 0; i < carte.lignes; i++) {
        for (int j = 0; j < carte.colonnes; j++) {
            char c;
            do {
                fscanf(fichier, " %c", &c);
            } while (c == '\n' || c == '\r');
            carte.grille[i][j] = c;
        }
    }
    
    fclose(fichier);
    return carte;
}

void libererCarte(Carte* carte) {
    if (carte->grille) {
        for (int i = 0; i < carte->lignes; i++) {
            free(carte->grille[i]);
        }
        free(carte->grille);
        carte->grille = NULL;
    }
}

void afficherCarte(Jeu* jeu) {
    system("clear");
    
    printf("\n=== SNAKE GAME ===\n");
    printf("Score: %d\n\n", jeu->score);
    
    for (int i = 0; i < jeu->carte.lignes; i++) {
        for (int j = 0; j < jeu->carte.colonnes; j++) {
            int estSerpent = 0;
            
            // Vérifier si c'est une partie du serpent
            Cellule* current = jeu->serpent.tete;
            while (current) {
                if (current->x == i && current->y == j) {
                    printf("%c ", current->lettre);
                    estSerpent = 1;
                    break;
                }
                current = current->suivant;
            }
            
            if (!estSerpent) {
                // Vérifier si c'est le bonus
                if (jeu->bonus.actif && jeu->bonus.x == i && jeu->bonus.y == j) {
                    printf("%c ", jeu->bonus.lettre);
                } else {
                    printf("%c ", jeu->carte.grille[i][j]);
                }
            }
        }
        printf("\n");
    }
    
    printf("\nCommandes: o=haut, l=bas, k=gauche, m=droite, q=quitter\n");
    if (jeu->bonus.actif) {
        printf("Bonus actif: %c (vie: %d)\n", jeu->bonus.lettre, jeu->bonus.vie);
    }
}