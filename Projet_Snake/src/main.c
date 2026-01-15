#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "../header/types.h"
#include "../header/carte.h"
#include "../header/serpent.h"
#include "../header/bonus.h"
#include "../header/jeu.h"
#include "../header/menu.h"

int main() {
    srand(time(NULL));
    
    int choix;
    char nomCarte[256];
    
    // Afficher le répertoire courant
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Répertoire courant: %s\n", cwd);
    }
    
    while (1) {
        afficherMenu();
        if (scanf("%d", &choix) != 1) {
            viderBuffer();
            printf("Entrée invalide!\n");
            continue;
        }
        viderBuffer();
        
        if (choix == 3) break;
        
        Jeu jeu;
        
        if (choix == 1) {
            printf("\nFichiers disponibles dans ce dossier:\n");
            system("ls -la *.txt 2>/dev/null || echo 'Aucun fichier .txt trouvé'");
            
            printf("\nNom du fichier carte (ex: carte.txt): ");
            if (scanf("%255s", nomCarte) != 1) {
                viderBuffer();
                printf("Erreur de lecture!\n");
                continue;
            }
            viderBuffer();
            
            initialiserJeu(&jeu, nomCarte);
            if (!jeu.carte.grille) {
                printf("Impossible de charger la carte. Appuyez sur Entrée...\n");
                getchar();
                continue;
            }
        } else if (choix == 2) {
            printf("Fonctionnalité de chargement pas encore implémentée.\n");
            printf("Appuyez sur Entrée...\n");
            getchar();
            continue;
        } else {
            printf("Choix invalide!\n");
            continue;
        }
        
        // Boucle de jeu
        while (!jeu.perdu) {
            afficherCarte(&jeu);
            
            char cmd;
            printf("\nCommande: ");
            if (scanf(" %c", &cmd) != 1) {
                viderBuffer();
                continue;
            }
            viderBuffer();
            
            if (cmd == 'q') {
                printf("Sauvegarder? (o/n): ");
                char rep;
                if (scanf(" %c", &rep) == 1 && rep == 'o') {
                    sauvegarderJeu(&jeu, "sauvegarde.txt");
                }
                viderBuffer();
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
