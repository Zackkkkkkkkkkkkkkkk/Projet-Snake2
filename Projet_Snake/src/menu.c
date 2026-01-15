#include <stdio.h>
#include "../header/menu.h"
#include "../header/serpent.h"

void viderBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void afficherMenu() {
    printf("\n=== MENU SNAKE ===\n");
    printf("1. Nouvelle partie\n");
    printf("2. Charger partie\n");
    printf("3. Quitter\n");
    printf("Choix: ");
}

void sauvegarderJeu(Jeu* jeu, const char* nomFichier) {
    FILE* f = fopen(nomFichier, "w");
    if (!f) {
        printf("Erreur de sauvegarde\n");
        return;
    }
    
    fprintf(f, "%d %d\n", jeu->score, jeu->serpent.longueur);
    
    Cellule* current = jeu->serpent.tete;
    while (current) {
        fprintf(f, "%d %d %c\n", current->x, current->y, current->lettre);
        current = current->suivant;
    }
    
    fprintf(f, "%d %d %d %c %d\n", jeu->bonus.actif, jeu->bonus.x, 
            jeu->bonus.y, jeu->bonus.lettre, jeu->bonus.vie);
    
    fclose(f);
    printf("Partie sauvegardée!\n");
}