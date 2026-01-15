#include <stdlib.h>
#include <ctype.h>
#include "../header/bonus.h"
#include "../header/serpent.h"

int estVoyelle(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

void genererBonus(Jeu* jeu) {
    int tentatives = 0;
    int x, y;
    
    do {
        x = rand() % jeu->carte.lignes;
        y = rand() % jeu->carte.colonnes;
        tentatives++;
        
        if (tentatives > 1000) return;
        
        int occupe = 0;
        if (jeu->carte.grille[x][y] != ' ') occupe = 1;
        
        if (verifierCollision(&jeu->serpent, x, y)) occupe = 1;
        
        if (!occupe) break;
    } while (1);
    
    jeu->bonus.x = x;
    jeu->bonus.y = y;
    jeu->bonus.lettre = 'a' + (rand() % 26);
    jeu->bonus.vie = MAX_BONUS_LIFE;
    jeu->bonus.actif = 1;
}

void decrementerVieBonus(Jeu* jeu) {
    if (jeu->bonus.actif) {
        jeu->bonus.vie--;
        if (jeu->bonus.vie <= 0) {
            jeu->bonus.actif = 0;
            genererBonus(jeu);
        }
    }
}