#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
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
    int it;
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

	chaufferMilieu((float*)matrice);
	afficherQuart((float*)matrice);

    //test d'une itération
    uneIteration((float*)matrice);
    afficherQuart((float*)matrice);
    uneIteration((float*)matrice);
    afficherQuart((float*)matrice);
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
            printf("Ajout chaud à [%d][%d] \n", i, j);
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
    memcpy(tmp, matrice, sizeof tmp);

    for(int i=0; i< taille ; i++){
        for(int j=0; j< taille ; j++){

            //Température de 0
            if( matrice[(taille*i)+j] <= TEMP_FROID ) {
                //Go next
            }
            else {
                
                //Todo cas négatif et débordement
                //Répartition de la chaleur
                tmp[i-1][j] += ( (matrice[(taille*i)+j])/36 )* 4;
                tmp[i+1][j] += ( (matrice[(taille*i)+j])/36 )* 4;
                tmp[i][j-1] += ( (matrice[(taille*i)+j])/36 )* 4;
                tmp[i][j+1] += ( (matrice[(taille*i)+j])/36 )* 4;
                tmp[i-1][j-1] += ( (matrice[(taille*i)+j])/36);
                tmp[i+1][j+1] += ( (matrice[(taille*i)+j])/36);
                tmp[i-1][j+1] += ( (matrice[(taille*i)+j])/36);
                tmp[i+1][j-1] += ( (matrice[(taille*i)+j])/36);
                tmp[i][j] += ( (matrice[(taille*i)+j])/36)*16;
            }
        }
    }
    //Copie de la matrice
    for(int i=0; i< taille ; i++){
        for(int j=0; j< taille ; j++) {
            matrice[(taille*i)+j] = tmp[i][j];
        }
    }
    //On remet de centre chaud
    chaufferMilieu((float*)matrice);
}