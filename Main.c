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
    int it;
    int *e = malloc (sizeof(int));
    int *t = malloc (sizeof(int));
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
                for(int i=0; i < sizeof(optarg); i++) {
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
                for(int i=0; i < sizeof(optarg); i++) {
                    *tmp = optarg[i];
                    e[i] = atoi(tmp);
                }
                break;
            case 't':
                for(int i=0; i < sizeof(optarg); i++) {
                    *tmp = optarg[i];
                    t[i] = atoi(tmp);
                }
                break;
        }


    /*
    afficherTabInt(s);
    printf("%d\n", m);
    printf("%d\n", a);
    printf("%d\n", it);
    afficherTabInt(e);
    afficherTabInt(t);
    */

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

void afficherTabInt(int tab[]) {

    for(int i=0; i <  sizeof(tab); i++) {
        printf("%d", tab[i]);
    }
    printf("\n");
}