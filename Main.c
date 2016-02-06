#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "Main.h"

//Températures prédéfinies
float TEMP_FROID = 0;
float TEMP_CHAUD = 256;
int taille=4;

int main(int argc, char *argv[]) {
    //Matrice
	float matrice[100][100];

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

	initialisation((float*)matrice);
	afficher((float*)matrice);

    //test d'une itération
    uneIteration((float*)matrice);
    //On remet de centre chaud
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
            }
        }
    }

    //Copie de la matrice
    for(int i=0; i< taille ; i++){
        for(int j=0; j< taille ; j++) {
            matrice[(taille*i)+j] = tmp[i][j];
        }
    }


}