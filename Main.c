//
// Created by lucas on 02/02/16.
//

#include <stdio.h>
#include <stdlib.h>
#include "Main.h"

float TEMP_FROID = 0;
float TEMP_CHAUD = 256;
int taille=4;

int main(){
	float matrice[100][100];
	initialisation((float*)matrice);
	afficher((float*)matrice);
	return 0;
}

int initialisation(float *matrice) {

    int milieu = (1/8)*taille+1;
    printf("milieu: %d\n", milieu);
    for(int i=0; i<2;i++){
        for (int j=0; j<2;j++){
            matrice[(taille * (milieu+i)) + (milieu+j)]=TEMP_CHAUD;
            //matrice[(taille * ligne) + colonne]
        }
    }
    return 0;
}

void afficher(float *matrice){
	for(int i=0; i< taille ; i++){
		for(int j=0; j< taille ; j++){
			printf("--%f--", matrice[(taille*i)+j]);
		}	
		printf("\n");
	}
}