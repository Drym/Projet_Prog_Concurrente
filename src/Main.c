#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <time.h>
#include "Main.h"
#include "Affichage.h"
#include "Operation.h"

//Temperatures predefinies
float TEMP_FROID = 0;
float TEMP_CHAUD = 256;

//Taille de la matrice
int n;
int taille;


/**
 * Fonction main
 * Recupere les valeurs en entree en fonction de differentes options
 * Appel la fonction lancement
 * @author Lucas
 */
int main(int argc, char *argv[]) {

    //Variables des differentes options recupere en entree
    int *s = malloc (sizeof(int));
    int tailleS;
    int it = 10000;
    int *e = malloc (sizeof(int));
    int tailleE;
    int *t = malloc (sizeof(int));
    int tailleT;
    int m = 0 , a = 0; //Booleen a faux
    //Tableau de char pour decouper les options
    char tmp[1];

    //Variable pour recuperer les options
    int optch;
    extern char * optarg;
    extern int optind, opterr;

    //Recuperation des options
    while ((optch = getopt(argc, argv, "s:mai:e:t:")) != -1)
        switch (optch) {
            case 's':
                //On decoupe les differentes tailles de problemes
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
                //On decoupe les differentes etapes a executer
                tailleE = strlen(optarg);
                for(int i=0; i < tailleE; i++) {
                    *tmp = optarg[i];
                    e[i] = atoi(tmp);
                }
                break;
            case 't':
                //On decoupe les differents nombre de thread a executer
                tailleT = strlen(optarg);
                for(int i=0; i < tailleT; i++) {
                    *tmp = optarg[i];
                    t[i] = atoi(tmp);
                }
                break;
        }


    //On regarde si la recuperation c'est bien passee
        /*
       afficherTabInt(s, tailleS);
       printf("%d\n", m);
       printf("%d\n", a);
       printf("%d\n", it);
       afficherTabInt(e, tailleE);
       afficherTabInt(t, tailleT);
        */

    //Regarde dans l'option e quelles sont les programmes a executer
    for (int i= 0; i < tailleE; i++) {

        //Iteratif
        if(e[i] == 0) {

            //Appel de la fonction lancement
            lancement(tailleS, s, it, a, m);

        }

    }


	return 0;
}


/**
 * Fonction lancement
 * Lance les operations sur la matrice : chauffe le milieu et effectue la repartition de la chaleur
 * @author Lucas
 */
int lancement(int tailleS, int s[], int it, int a, int m) {

    //On gere l'option -s
    for (int i=0; i< tailleS; i++) {

        //Variable pour le calcul de temps
        float temps;
        clock_t t1, t2;
        t1 = clock();

        //Mise a jour de la taille
        n = 4 + s[i];
        taille = 2<<(n-1);

        //Matrice
        float matrice[taille][taille];

        //On initialise la matrice avec des 0
        miseAzero((float*)matrice, taille);

        //affiche la taille
        printf("Taille de : %d\n", taille);

        chaufferMilieu((float*)matrice, n, taille, TEMP_CHAUD);

        //Affiche le quart de la matrice (avant execution) si l'option a est utilise
        if(a) {
            afficherQuart((float*)matrice, taille);
        }

        for (int i=1; i <= it; i++) {
            uneIteration((float*)matrice, taille, TEMP_FROID);
            //On remet le centre chaud
            chaufferMilieu((float*)matrice, n, taille, TEMP_CHAUD);
        }

        //Affiche le quart de la matrice (apres execution) si l'option a est utilise
        if(a) {
            afficherQuart((float*)matrice, taille);
        }


        //afficherQuart((float*)matrice, taille);
        //afficher((float*)matrice, taille);

        //Pour calculer le temps
        t2 = clock();
        //On gere l'option m
        if(m) {
            temps = (float) (t2 - t1) / CLOCKS_PER_SEC;
            printf("Done. Temps = %fs\n", temps);
        } else printf("Done\n");
    }

    return 0;
}