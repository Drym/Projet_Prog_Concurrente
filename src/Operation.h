/*
 * @authors Chloe et Lucas
 */

#ifndef PROJET_PROG_CONCURRENTE_OPERATION_H
#define PROJET_PROG_CONCURRENTE_OPERATION_H

int chaufferMilieu( float **matrice, int n, int taille, float TEMP_CHAUD);
int uneIterationV2(float **matrice,float **tmp, int taille, float TEMP_FROID);
int miseAFroid(float **matrice, int taille, float TEMP_FROID);

#endif //PROJET_PROG_CONCURRENTE_OPERATION_H
