#ifndef CLIBRARY_H_INCLUDED
#define CLIBRARY_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

struct DATA{
    int an;
    int luna;
    int zi;
};

struct STUDENT{
    char name[26];
    float time;
    int recent_chapter;
    struct DATA ultimaVizita;
};


// Converteste o temperatura celsius in fahrenheit
float convertCelsiusToFahrenheit(int cels);
//Aduna doua numere
int Adunare(int a, int b);
//Aduna elementele unui vector si returneaza suma lor
int sumaVector(int vect[], int dim);
//Introducerea de elemente in array vector dinamic cu malloc
int *arrayDinamicMemory();
//Cel mai mic numitor comun a doua numere intregi
int celMaiMicNumitorComun(int nr1, int nr2);
//Verificare daca un numar este par. Un numar este par daca impartit la 2 rezulta 0.
void numarPar(int nr);

#endif // CLIBRARY_H_INCLUDED
