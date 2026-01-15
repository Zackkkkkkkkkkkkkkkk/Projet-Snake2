#include "../header/jeu.h"
#include "../header/carte.h"
#include "../header/serpent.h"
#include "../header/bonus.h"

void initialiserJeu(Jeu* jeu, const char* nomCarte) {
    jeu->carte = chargerCarte(nomCarte);
    jeu->serpent = creerSerpent(1, 1);
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
        ajouterTete(&jeu->serpent, nouveauX, nouveauY, jeu->serpent.tete->suivant->lettre);
        supprimerQueue(&jeu->serpent);
    }
    
    decrementerVieBonus(jeu);
    
    return 1;
}