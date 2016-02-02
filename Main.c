//
// Created by lucas on 02/02/16.
//

#include <stdio.h>
#include "Main.h"


int main(){
	demander_param();
	return 0;
}

int demander_param(){
	int c;
    
    printf("Veuillez taper un entier : ");
    c = getc(stdin);

    printf("Vous avez tape : ");
    putc(c, stdout);

    return 0;
}