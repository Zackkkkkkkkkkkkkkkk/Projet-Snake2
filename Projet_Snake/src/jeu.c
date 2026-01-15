#include "../header/jeu.h"
#include "../header/carte.h"
#include "../header/serpent.h"
#include "../header/bonus.h"

void initialiserJeu(Jeu* jeu, const char* nomCarte) {
    jeu->carte = chargerCarte(nomCarte);
    
    // Vérifier que la carte a été chargée correctement
    if (!jeu->carte.grille) {
        jeu->perdu = 1;
        return;
    }
    
    // Trouver une position valide pour le serpent
    int x = 1, y = 1;
    int trouve = 0;
    
    for (int i = 1; i < jeu->carte.lignes - 1 && !trouve; i++) {
        for (int j = 1; j < jeu->carte.colonnes - 1 && !trouve; j++) {
            if (jeu->carte.grille[i][j] == ' ') {
                x = i;
                y = j;
                trouve = 1;
            }
        }
    }
    
    jeu->serpent = creerSerpent(x, y);
    jeu->bonus.actif = 0;
    jeu->score = 0;
    jeu->perdu = 0;
    genererBonus(jeu);
}

void libererJeu(Jeu* jeu) {
    libererSerpent(&jeu->serpent);
    libererCarte(&jeu->carte);
}

int deplacerSerpent(Jeu* jeu, char direction) {
    int nouveauX = jeu->serpent.tete->x;
    int nouveauY = jeu->serpent.tete->y;
    
    switch (direction) {
        case 'o': nouveauX--; break;
        case 'l': nouveauX++; break;
        case 'k': nouveauY--; break;
        case 'm': nouveauY++; break;
        default: return 0;
    }
    
    // Vérifier les limites
    if (nouveauX < 0 || nouveauX >= jeu->carte.lignes || 
        nouveauY < 0 || nouveauY >= jeu->carte.colonnes) {
        jeu->perdu = 1;
        return 0;
    }
    
    // Vérifier obstacle
    if (jeu->carte.grille[nouveauX][nouveauY] == '#') {
        jeu->perdu = 1;
        return 0;
    }
    
    // Vérifier collision avec soi-même
    if (verifierCollision(&jeu->serpent, nouveauX, nouveauY)) {
        jeu->perdu = 1;
        return 0;
    }
    
    // Vérifier si on mange le bonus
    if (jeu->bonus.actif && jeu->bonus.x == nouveauX && jeu->bonus.y == nouveauY) {
        jeu->score += estVoyelle(jeu->bonus.lettre) ? 10 : 5;
        ajouterTete(&jeu->serpent, nouveauX, nouveauY, jeu->bonus.lettre);
        jeu->bonus.actif = 0;
        genererBonus(jeu);
    } else {
        // Pour un serpent d'une seule case, garder la même lettre
        char lettre = (jeu->serpent.longueur == 1) ? jeu->serpent.tete->lettre : jeu->serpent.tete->suivant->lettre;
        ajouterTete(&jeu->serpent, nouveauX, nouveauY, lettre);
        supprimerQueue(&jeu->serpent);
    }
    
    decrementerVieBonus(jeu);
    
    return 1;
}
