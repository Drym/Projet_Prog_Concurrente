#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <math.h>
#include "Main.h"

//Températures prédéfinies
float TEMP_FROID = 0;
float TEMP_CHAUD = 256;
int n=4;
int taille;

int main(int argc, char *argv[]) {
    //Matrice
    float matrice[100][100];
    taille= 2<<(n-1);

    //Variables des différentes options
    int *s = malloc (sizeof(int));
    int tailleS;
    int it = 10000;
    int *e = malloc (sizeof(int));
    int tailleE;
    int *t = malloc (sizeof(int));
    int tailleT;
    int m = 0 , a = 0; //Booléen à faux
    //pour découper les options
    char tmp[1];

    //Variable pour récupérer les options
    int optch;
    extern char * optarg;
    extern int optind, opterr;

    //Récupération des options
    while ((optch = getopt(argc, argv, "s:mai:e:t:")) != -1)
        switch (optch) {
            case 's':
                tailleS = strlen(optarg);
                for(int i=0; i < tailleS; i++) {
                    *tmp = optarg[i];
                    s[i] = atoi(tmp);
                }
                break;
            case 'm':
                m = 1;
                break;
            case 'a':
                a = 1;
                break;
            case 'i':
                it = atoi(optarg);
                break;
            case 'e':
                tailleE = strlen(optarg);
                for(int i=0; i < tailleE; i++) {
                    *tmp = optarg[i];
                    e[i] = atoi(tmp);
                }
                break;
            case 't':
                tailleT = strlen(optarg);
                for(int i=0; i < tailleT; i++) {
                    *tmp = optarg[i];
                    t[i] = atoi(tmp);
                }
                break;
        }
    /*
   afficherTabInt(s, tailleS);
   printf("%d\n", m);
   printf("%d\n", a);
   printf("%d\n", it);
   afficherTabInt(e, tailleE);
   afficherTabInt(t, tailleT);
   */

    lancement((float*)matrice, tailleS, s, it);


	return 0;
}


int chaufferMilieu(float *matrice) {
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

void afficher(float *matrice){
	for(int i=0; i< taille ; i++){
		for(int j=0; j< taille ; j++){
			printf("-%.2f-", matrice[(taille*i)+j]);
		}	
		printf("\n");
	}
}

void afficherQuart(float *matrice){
    for(int i=0; i< taille/2 ; i++){
        for(int j=0; j< taille/2 ; j++){
            printf("-%.2f-", matrice[(taille*i)+j]);
        }   
        printf("\n");
    }
}

void afficherTabInt(int tab[], int taille) {

    for(int i=0; i < taille; i++) {
        printf("%d", tab[i]);
    }
    printf("\n");
}

void uneIteration(float *matrice) {

    //Matrice temporaire
    float tmp[100][100];

    //Copie de la matrice
    for(int i=0; i< taille ; i++){
        for(int j=0; j< taille ; j++) {
           tmp[i][j] =  matrice[(taille*i)+j];

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
                //Cas hors matrice négatif sur i
                if(i-1 < 0) {
                    //On ne fait que les j, les i+1 et le milieu
                    tmp[i + 1][j] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i][j - 1] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i][j + 1] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i + 1][j + 1] += ((matrice[(taille * i) + j]) / 36);
                    tmp[i + 1][j - 1] += ((matrice[(taille * i) + j]) / 36);
                    tmp[i][j] += ((matrice[(taille * i) + j]) / 36) * 16;

                }
                //Cas hors matrice négatif sur j
                if(j-1 < 0) {
                    //On ne fait que les i, les j+1 et le milieu
                    tmp[i - 1][j] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i + 1][j] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i][j + 1] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i + 1][j + 1] += ((matrice[(taille * i) + j]) / 36);
                    tmp[i - 1][j + 1] += ((matrice[(taille * i) + j]) / 36);
                    tmp[i][j] += ((matrice[(taille * i) + j]) / 36) * 16;

                }
                //Cas hors matrice négatif sur i et j
                if(i-1 < 0 || j-1 < 0) {
                    //On ne fait que le milieu et les +
                    tmp[i + 1][j] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i][j + 1] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i + 1][j + 1] += ((matrice[(taille * i) + j]) / 36);
                    tmp[i][j] += ((matrice[(taille * i) + j]) / 36) * 16;


                }
                //Cas positif hors matrice sur i
                if(i+1 > taille*taille) {
                    //On ne fait que les j, les i-1 et le milieu
                    tmp[i - 1][j] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i][j - 1] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i][j + 1] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i - 1][j - 1] += ((matrice[(taille * i) + j]) / 36);
                    tmp[i - 1][j + 1] += ((matrice[(taille * i) + j]) / 36);
                    tmp[i][j] += ((matrice[(taille * i) + j]) / 36) * 16;


                }
                //Cas positif hors matrice sur j
                if(j+1 > taille*taille) {
                    //On ne fait que les i, les j-1 et le milieu
                    tmp[i - 1][j] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i + 1][j] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i][j - 1] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i - 1][j - 1] += ((matrice[(taille * i) + j]) / 36);
                    tmp[i + 1][j - 1] += ((matrice[(taille * i) + j]) / 36);
                    tmp[i][j] += ((matrice[(taille * i) + j]) / 36) * 16;

                }
                //Cas positif hors matrice sur i et j
                if(i+1 > taille*taille || j+1 > taille*taille) {
                    //On ne fait que le milieu et les -
                    tmp[i - 1][j] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i][j - 1] += ((matrice[(taille * i) + j]) / 36) * 4;
                    tmp[i - 1][j - 1] += ((matrice[(taille * i) + j]) / 36);
                    tmp[i][j] += ((matrice[(taille * i) + j]) / 36) * 16;

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
                    tmp[i][j] += ((matrice[(taille * i) + j]) / 36) * 16;
                }
            }
        }
    }
    //Copie de la matrice
    for(int i=0; i< taille ; i++){
        for(int j=0; j< taille ; j++) {
            matrice[(taille*i)+j] = tmp[i][j];
        }
    }
    //On remet le centre chaud
    chaufferMilieu((float*)matrice);
}

void lancement(float *matrice, int tailleS, int s[], int it) {

    //for (int i=0; i< tailleS; i++) {
    //taille = 2<<(s[i]+4);

    chaufferMilieu((float*)matrice);

    for (int i=0; i <= it; i++) {
        uneIteration((float*)matrice);
        //afficher((float*)matrice);
    }
    printf("\nTaille : %d\n", taille);
    printf("\n");
    afficherQuart((float*)matrice);

    //}

}