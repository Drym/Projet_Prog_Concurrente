/**
 * Modelisation de l'evolution de la chaleur sur une plaque chauffante
 * 14/02/2016
 * Chole Guglielmi et Lucas Sauvage
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <time.h>
#include <sys/resource.h>
#include "Main.h"
#include "Affichage.h"
#include "Operation.h"

//Temperatures predefinies
float TEMP_FROID = 0;
float TEMP_CHAUD = 256;

//Taille de la matrice
int n;
int taille;

//Structure pour calculer la memoire utilise
struct rusage r_usage;


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

    //Regarde dans l'option e quels sont les programmes a executer
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
        float temps[10];

        //Mise a jour de la taille
        n = 4 + s[i];
        taille = 2<<(n-1);

        if(m){
            //on fait 10x la scenario pour avoir une moyenne du temps (on enleve les deux extremes)
            lancerUnScenario(taille, it, a, n, TEMP_FROID, TEMP_CHAUD, &temps[0]);
            float min=temps[0];
            float max=temps[0];
            for (int j=1; j<10; j++){
                lancerUnScenario(taille, it, 0,  n , TEMP_FROID, TEMP_CHAUD, &temps[j]);//a =0 car on ne veut pas l'afficher a chaque fois
                if (temps[j]>max)
                    max=temps[j];
                if (temps[j]<min)
                    min=temps[j];
            }
            //Calcul de la moyenne:
            float somme=0;
            int cmpt=0;
            for (int j = 0; j < 10; ++j){
                //printf("temps[i]: %f\n", temps[j]);
                if(temps[j]!=max && temps[j]!=min){
                    somme+=temps[j];
                    cmpt++;
                }
            }
            float f=somme/cmpt;
            printf("Temps moyen pour matrice de taille %d : %f s\n", taille, f);
        } else {
            lancerUnScenario(taille, it, a,  n ,TEMP_FROID, TEMP_CHAUD, &temps[0]);

        }

        //Recupere et affiche la memoire utilisee
        getrusage(RUSAGE_SELF, &r_usage);
        printf("Memoire utilisee (taille %d) : %ld ko\n",taille, r_usage.ru_maxrss);

    }
    return 0;
}

/* Fonction de lancement d'un seul scenario */
int lancerUnScenario(int taille, int it, int a, int n, float TEMP_FROID, float TEMP_CHAUD, float *temps){
    //Matrice
    float matrice[taille][taille];

    clock_t t1, t2;
    t1 = clock();//depart

    //On initialise la matrice avec des 0
    miseAzero((float*)matrice, taille);

    chaufferMilieu((float*)matrice, n, taille, TEMP_CHAUD);

    //Affiche le quart de la matrice (avant execution) si l'option a est utilisee
    if(a) {
        afficherQuart((float*)matrice, taille);
    }

    for (int i=1; i <= it; i++) {
        uneIteration((float*)matrice, taille, TEMP_FROID);
        //On remet le centre chaud
        chaufferMilieu((float*)matrice, n, taille, TEMP_CHAUD);
    }

    //Affiche le quart de la matrice (apres execution) si l'option a est utilisee
    if(a) {
       afficherQuart((float*)matrice, taille);
    }

    //Pour calculer le temps
    t2 = clock();
    *temps = (float) (t2 - t1) / CLOCKS_PER_SEC;
    return 0;
}


