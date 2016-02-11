#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "Main.h"
#include "Affichage.h"
#include "Operation.h"

//Températures prédéfinies
float TEMP_FROID = 0;
float TEMP_CHAUD = 256;

//Taille de la matrice
int n=4;
int taille;


/**
 * Fonction main
 * Récupère les valeurs en entrée en fonction de différentes options
 * Appel la fonction lancement
 * @author Lucas
 */
int main(int argc, char *argv[]) {
    //Matrice
    float matrice[100][100];
    taille = 2<<(n-1);

    //Variables des différentes options récupéré en entrée
    int *s = malloc (sizeof(int));
    int tailleS;
    int it = 10000;
    int *e = malloc (sizeof(int));
    int tailleE;
    int *t = malloc (sizeof(int));
    int tailleT;
    int m = 0 , a = 0; //Booléen à faux
    //Tableau de char pour découper les options
    char tmp[1];

    //Variable pour récupérer les options
    int optch;
    extern char * optarg;
    extern int optind, opterr;

    //Récupération des options
    while ((optch = getopt(argc, argv, "s:mai:e:t:")) != -1)
        switch (optch) {
            case 's':
                //On découpe les différentes tailles de problèmes
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
                //On découpe les différentes étapes a exécuter
                tailleE = strlen(optarg);
                for(int i=0; i < tailleE; i++) {
                    *tmp = optarg[i];
                    e[i] = atoi(tmp);
                }
                break;
            case 't':
                //On découpe les différents nombre de thread a exécuter
                tailleT = strlen(optarg);
                for(int i=0; i < tailleT; i++) {
                    *tmp = optarg[i];
                    t[i] = atoi(tmp);
                }
                break;
        }
    //On regarde si la récupération c'est bien passée
    /*
   afficherTabInt(s, tailleS);
   printf("%d\n", m);
   printf("%d\n", a);
   printf("%d\n", it);
   afficherTabInt(e, tailleE);
   afficherTabInt(t, tailleT);
   */

    //Appel de la fonction lancement
    lancement((float*)matrice, tailleS, s, it);

	return 0;
}


/**
 * Fonction lancement
 * Lance les opérations sur la matrice : chauffe le milieu et effectue la répartition de la chaleur
 * @author Lucas
 */
int lancement(float *matrice, int tailleS, int s[], int it) {

    //for (int i=0; i< tailleS; i++) {
    //taille = 2<<(s[i]+4);

    chaufferMilieu((float*)matrice, n, taille, TEMP_CHAUD);

    for (int i=0; i <= it; i++) {
        uneIteration((float*)matrice, taille, TEMP_FROID);
        //On remet le centre chaud
        chaufferMilieu((float*)matrice, n, taille, TEMP_CHAUD);
    }

    //afficherQuart((float*)matrice, taille);
    afficher((float*)matrice, taille);

    //}
    return 0;
}