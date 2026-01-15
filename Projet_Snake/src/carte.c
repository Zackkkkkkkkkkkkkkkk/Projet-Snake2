#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/carte.h"
#include "../header/serpent.h"

Carte chargerCarte(const char* nomFichier) {
    Carte carte;
    carte.grille = NULL;
    carte.lignes = 0;
    carte.colonnes = 0;
    
    FILE* fichier = fopen(nomFichier, "r");
    
    if (!fichier) {
        printf("Erreur: impossible d'ouvrir '%s'\n", nomFichier);
        printf("Vérifiez que le fichier existe.\n");
        return carte;
    }
    
    // Lecture des dimensions
    if (fscanf(fichier, "%d %d", &carte.lignes, &carte.colonnes) != 2) {
        printf("Erreur: impossible de lire les dimensions.\n");
        fclose(fichier);
        return carte;
    }
    
    printf("Dimensions lues: %d lignes x %d colonnes\n", carte.lignes, carte.colonnes);
    
    // Consommer le retour à la ligne après les dimensions
    char c;
    while ((c = fgetc(fichier)) != '\n' && c != EOF);
    
    // Allocation dynamique de la matrice
    carte.grille = (char**)malloc(carte.lignes * sizeof(char*));
    if (!carte.grille) {
        printf("Erreur d'allocation mémoire\n");
        fclose(fichier);
        return carte;
    }
    
    for (int i = 0; i < carte.lignes; i++) {
        carte.grille[i] = (char*)malloc(carte.colonnes * sizeof(char));
        if (!carte.grille[i]) {
            printf("Erreur d'allocation mémoire ligne %d\n", i);
            for (int j = 0; j < i; j++) {
                free(carte.grille[j]);
            }
            free(carte.grille);
            carte.grille = NULL;
            fclose(fichier);
            return carte;
        }
    }
    
    // Lecture ligne par ligne
    for (int i = 0; i < carte.lignes; i++) {
        char ligne[1000];
        if (fgets(ligne, sizeof(ligne), fichier) == NULL) {
            printf("Erreur: ligne %d manquante\n", i);
            libererCarte(&carte);
            fclose(fichier);
            return carte;
        }
        
        // Enlever le \n à la fin
        int len = strlen(ligne);
        if (len > 0 && ligne[len-1] == '\n') {
            ligne[len-1] = '\0';
            len--;
        }
        
        printf("Ligne %d lue: '%s' (longueur: %d)\n", i, ligne, len);
        
        // Copier les caractères
        for (int j = 0; j < carte.colonnes; j++) {
            if (j < len) {
                carte.grille[i][j] = ligne[j];
            } else {
                carte.grille[i][j] = ' '; // Remplir avec des espaces si ligne trop courte
            }
        }
    }
    
    fclose(fichier);
    printf("Carte chargée avec succès!\n\n");
    return carte;
}

void libererCarte(Carte* carte) {
    if (carte->grille) {
        for (int i = 0; i < carte->lignes; i++) {
            if (carte->grille[i]) {
                free(carte->grille[i]);
            }
        }
        free(carte->grille);
        carte->grille = NULL;
    }
    carte->lignes = 0;
    carte->colonnes = 0;
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
                    printf("%c", current->lettre);
                    estSerpent = 1;
                    break;
                }
                current = current->suivant;
            }
            
            if (!estSerpent) {
                // Vérifier si c'est le bonus
                if (jeu->bonus.actif && jeu->bonus.x == i && jeu->bonus.y == j) {
                    printf("%c", jeu->bonus.lettre);
                } else {
                    printf("%c", jeu->carte.grille[i][j]);
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
