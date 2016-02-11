#include <stdio.h>
#include <math.h>
#include "Operation.h"

/**
 * Fonction chaufferMilieu
 * Chauffe le milieu de la matrice
 * @author Chloé
 */
int chaufferMilieu(float *matrice, int n, int taille, float TEMP_CHAUD) {
    int dep_chaud=(2<<(n-2))-(2<<(n-5));
    int fin_chaud=(2<<(n-2))+(2<<(n-5));
    if(n==4){ //car 2<<0=0 alors que 2^0=1
        dep_chaud=7;
        fin_chaud=9;
    }
    for(int i=dep_chaud; i<fin_chaud;i++){
        for (int j=dep_chaud; j<fin_chaud;j++){
            //printf("Ajout chaud à [%d][%d] \n", i, j);
            matrice[taille * (i) + (j)]=TEMP_CHAUD;
            //matrice[(taille * ligne) + colonne]
        }
    }
    return 0;
}

/**
 * Fonction uneIteration
 * Effectue la répartition de la chaleur pour une itération
 * @author Lucas
 */
int uneIteration(float *matrice, int taille, float TEMP_FROID) {

    //Matrice temporaire
    float tmp[100][100];
    float tmp2[100][100];

    //Copie de la matrice dans tmp
    for(int i=0; i< taille ; i++){
        for(int j=0; j< taille ; j++) {
            tmp[i][j] =  matrice[(taille*i)+j];
            tmp2[i][j] =  matrice[(taille*i)+j];
        }
    }

    //Boucle pour répartir la chaleur
    for(int i=0; i< taille ; i++){
        for(int j=0; j< taille ; j++){

            //Température de 0
            if( matrice[(taille*i)+j] <= TEMP_FROID ) {
                //Rien à faire
            }
                //Température > 0
            else {
                //Ici il ne faut pas répartir la chaleur en dehors de la matrice
                //Cas hors matrice négatif sur i
                if(i-1 < 0) {
                    //On ne fait que les j, les i+1 et le milieu
                    tmp[i + 1][j] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i][j - 1] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i][j + 1] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i + 1][j + 1] += ((matrice[(taille * i) + j]) / 36);
                    tmp[i + 1][j - 1] += ((matrice[(taille * i) + j]) / 36);
                    tmp[i][j] += (((matrice[(taille * i) + j]) / 36) * 16) - ((matrice[(taille * i) + j]));

                }
                //Cas hors matrice négatif sur j
                else if(j-1 < 0) {
                    //On ne fait que les i, les j+1 et le milieu
                    tmp[i - 1][j] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i + 1][j] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i][j + 1] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i + 1][j + 1] += ((matrice[(taille * i) + j]) / 36);
                    tmp[i - 1][j + 1] += ((matrice[(taille * i) + j]) / 36);
                    tmp[i][j] += (((matrice[(taille * i) + j]) / 36) * 16) - ((matrice[(taille * i) + j]));

                }
                //Cas hors matrice négatif sur i et j
                else if(i-1 < 0 || j-1 < 0) {
                    //On ne fait que le milieu et les +
                    tmp[i + 1][j] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i][j + 1] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i + 1][j + 1] += ((matrice[(taille * i) + j]) / 36);
                    tmp[i][j] += (((matrice[(taille * i) + j]) / 36) * 16) - ((matrice[(taille * i) + j]));


                }
                //Cas positif hors matrice sur i
                else if(i+1 > taille*taille) {
                    //On ne fait que les j, les i-1 et le milieu
                    tmp[i - 1][j] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i][j - 1] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i][j + 1] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i - 1][j - 1] += ((matrice[(taille * i) + j]) / 36);
                    tmp[i - 1][j + 1] += ((matrice[(taille * i) + j]) / 36);
                    tmp[i][j] += (((matrice[(taille * i) + j]) / 36) * 16) - ((matrice[(taille * i) + j]));


                }
                //Cas positif hors matrice sur j
                else if(j+1 > taille*taille) {
                    //On ne fait que les i, les j-1 et le milieu
                    tmp[i - 1][j] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i + 1][j] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i][j - 1] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i - 1][j - 1] += ((matrice[(taille * i) + j]) / 36);
                    tmp[i + 1][j - 1] += ((matrice[(taille * i) + j]) / 36);
                    tmp[i][j] += (((matrice[(taille * i) + j]) / 36) * 16) - ((matrice[(taille * i) + j]));

                }
                //Cas positif hors matrice sur i et j
                else if(i+1 > taille*taille || j+1 > taille*taille) {
                    //On ne fait que le milieu et les -
                    tmp[i - 1][j] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i][j - 1] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i - 1][j - 1] += ((matrice[(taille * i) + j]) / 36);
                    tmp[i][j] += (((matrice[(taille * i) + j]) / 36) * 16) - ((matrice[(taille * i) + j]));

                }
                else {
                    //On fait tout
                    tmp[i - 1][j] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i + 1][j] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i][j - 1] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i][j + 1] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i - 1][j - 1] += ((matrice[(taille * i) + j]) / 36);
                    tmp[i + 1][j + 1] += ((matrice[(taille * i) + j]) / 36);
                    tmp[i - 1][j + 1] += ((matrice[(taille * i) + j]) / 36);
                    tmp[i + 1][j - 1] += ((matrice[(taille * i) + j]) / 36);
                    tmp[i][j] += (((matrice[(taille * i) + j]) / 36) * 16) - ((matrice[(taille * i) + j]));

                }
            }
        }
    }

    //Copie de la matrice tmp dans celle finale
    for(int i=0; i< taille ; i++){
        for(int j=0; j< taille ; j++) {
            matrice[(taille*i)+j] = tmp[i][j];
        }
    }
    return 0;
}
