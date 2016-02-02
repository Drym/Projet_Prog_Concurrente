//
// Created by lucas on 02/02/16.
//

#include <stdio.h>
#include "Main.h"

int taille = 4;
int matrice[taille][taille];
int matrice2[taille][taille];
int TEMP_FROID = 0;
int TEMP_CHAUD = 256;



int main(){
	demander_param();
	return 0;
}

int demander_param(){
	int c;
    
    printf("Veuillez taper un entier : ");
    c = getc(stdin);

    printf("Vous avez tape : ");
    putc(c, stdout);

    return 0;
}


int initialisation() {

    int milieu = (1/8)*taille;

    for(i=0; i < taille; i++)
    {
        for(j=0; j < taille; j++)
        {
            t[i][j]=TEMP_FROID;
        }
    }

    return 0;
}