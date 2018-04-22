#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Clibrary.h"

int main()
{
    struct STUDENT stdnt;
    stdnt.time = 1.5;
    //stdnt.STUDENT=0;
    //Crearea unui array de studenti
    struct STUDENT stdnts[100];
    //Adaugarea unui student
    strcpy(stdnts[0].name, "Mihai Cornel");
    stdnts[0].time = 3.5;
    stdnts[0].recent_chapter = 5;
    stdnts[0].ultimaVizita.an = 2016;
    stdnts[0].ultimaVizita.luna = 9;
    stdnts[0].ultimaVizita.zi  = 10;

    struct DATA data ={2016, 9, 10};

    printf("Hello world!\n");
    int a =28, b=32;
    float tempF;
    tempF = convertCelsiusToFahrenheit(9);
    printf("Convert Celsius to Fahrenheit: %f\n", tempF);
    numarPar(a);
    numarPar(33);

    int suma = Adunare(a,b);
    printf("Adunare %d + %d = %d\n", a,b,suma);

    int v[3] = {1,2,3};
    int sum =0;
    sum = sumaVector(v, 3);
    printf("SUMA VECTORULUI: %d\n", sum);

    int nr1, nr2, rez;
    printf("Introduce-ti doua numere pt. a afla cel mai mic numitor comun:\n");
    scanf("%d %d", &nr1, &nr2);
    celMaiMicNumitorComun(nr1, nr2);
    printf("\n");

    int *myArr;
    myArr = arrayDinamicMemory();
    printf("Array: %d\n", myArr);
    return 0;
}
