#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    printf("Alocarea dinamica de memorie!\n");

    char nume[100];
    char *descriere;

    strcpy(nume, "Mihai Cornel");
    /**Alocarea dinamica de memorie*/
    descriere = malloc(200*sizeof(char)) ;
    if (descriere == NULL){
        fprintf(stderr, "Memoria nu a putut fi alocata");
    } else {
        strcpy(descriere, "Acesta este un curs de C/C++ pe care este\
        bine sa-l parcurgeti pana la final");
    }

    printf("Nume: %s.\n", nume);
    printf("Descriere: %s.\n", descriere);

    free(descriere);
    return 0;
}
