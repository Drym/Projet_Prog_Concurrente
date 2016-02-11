#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Affichage.h"

/**
 * Fonction afficher
 * Affiche l'intégralité de la matrice
 * @author Chloé
 */
int afficher(float *matrice, int taille){
    for(int i=0; i< taille ; i++){
        for(int j=0; j< taille ; j++){
            printf("-%.2f-", matrice[(taille*i)+j]);
        }
        printf("\n");
    }
    return 0;
}


/**
 * Fonction afficherQuart
 * Affiche un quart de la matrice
 * @author Chloé
 */
int afficherQuart(float *matrice, int taille){
    for(int i=0; i< taille/2 ; i++){
        for(int j=0; j< taille/2 ; j++){
            printf("-%.2f-", matrice[(taille*i)+j]);
        }
        printf("\n");
    }
    return 0;
}

/**
 * Fonction afficherTabInt
 * Affiche un tableau de int (utilité nottament pour vérifier si les paramètres en entrée ont bien été récupéré)
 * @author Lucas
 */
int afficherTabInt(int tab[], int taille) {

    for(int i=0; i < taille; i++) {
        printf("%d", tab[i]);
    }
    printf("\n");

    return 0;
}
