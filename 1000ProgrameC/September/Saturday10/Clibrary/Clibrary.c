#include "Clibrary.h"

float convertCelsiusToFahrenheit(int cels){
    float fahr;
    fahr = 1.8*cels + 32;
    return fahr;

}

void numarPar(int nr){
    if(nr%2) printf("Numarul %d este impar.\n", nr);
    else printf("Numarul %d este par.\n", nr );
    return ;
}

int celMaiMicNumitorComun(int nr1, int nr2)
{
    int cmmnc;//celmaimicnumitorcomun

    cmmnc = (nr1>nr2) ? nr1 : nr2;

    while(1){
        if(cmmnc%nr1==0 && cmmnc%nr2==0){
            printf("Cel mai mic numitor comun al %d si %d este %d.\n", nr1, nr2, cmmnc);
            break;
        }
        ++cmmnc;
    }
    return cmmnc;
}

int *arrayDinamicMemory()
{
    int i, nrElem;
    int *ptrArr;

    printf("Introduce-ti numarul de elemente din vector: ");
    scanf("%d", &nrElem);
    //Alocarea dinamica de elemente
    ptrArr = (int*)malloc(nrElem*sizeof(int));
    //Verificam daca memoria este alocata
    if(ptrArr== NULL){
        printf("Eroare! Memoria nu a fost alocata.");
        exit(0);
    }
    //introducem elementele din array
    for(i=0; i<nrElem; i++){
        printf("Introduce-ti elementele Vector[%d] = ", i);
        scanf("%d", ptrArr+i);
    }
    return ptrArr;

}


int sumaVector(int vect[], int dim)
{
    int suma =0;
    int i;
    for(i=0; i<dim; i++){
        suma = suma + vect[i];
    }
    return suma;
}

int Adunare(int a, int b)
{
    int suma;
    suma = a+b;
    return suma;
}
