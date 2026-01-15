#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../header/types.h"
#include "../header/carte.h"
#include "../header/serpent.h"
#include "../header/bonus.h"
#include "../header/jeu.h"
#include "../header/menu.h"

int main() {
    srand(time(NULL));
    
    int choix;
    char nomCarte[100];
    
    while (1) {
        afficherMenu();
        scanf("%d", &choix);
        viderBuffer();
        
        if (choix == 3) break;
        
        Jeu jeu;
        
        if (choix == 1) {
            printf("Nom du fichier carte (ex: carte.txt): ");
            scanf("%s", nomCarte);
            viderBuffer();
            
            initialiserJeu(&jeu, nomCarte);
            if (!jeu.carte.grille) continue;
        }
        
        // Boucle de jeu
        while (!jeu.perdu) {
            afficherCarte(&jeu);
            
            char cmd;
            printf("\nCommande: ");
            scanf(" %c", &cmd);
            viderBuffer();
            
            if (cmd == 'q') {
                printf("Sauvegarder? (o/n): ");
                char rep;
                scanf(" %c", &rep);
                viderBuffer();
                
                if (rep == 'o') {
                    sauvegarderJeu(&jeu, "sauvegarde.txt");
                }
                break;
            }
            
            deplacerSerpent(&jeu, cmd);
        }
        
        if (jeu.perdu) {
            afficherCarte(&jeu);
            printf("\n*** GAME OVER ***\n");
            printf("Score final: %d\n", jeu.score);
            printf("Appuyez sur Entrée...");
            getchar();
        }
        
        libererJeu(&jeu);
    }
    
    printf("Merci d'avoir joué!\n");
    return 0;
}