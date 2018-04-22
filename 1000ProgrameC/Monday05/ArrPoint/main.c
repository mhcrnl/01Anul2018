#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char g_arr[20] = "Regele bucatarilor ";
char *p_g_arr = "gateste extraordinar.";

/** --------------------------------------------------------------
Aceasta functie returneaza un array de numere aleatoare
------------------------------------------------------------------*/
int *RandomElem()
{
    static int arraElem[10];
    int i;

    srand((unsigned)time (NULL));
    for(i=0; i<10; i++){
        arraElem[i]=rand();
        printf("arraElem[%d]=%d\n", i, arraElem[i]);
    }
}

void stringToFunc(char _1arr[], char *_2arr)
{
    char a = _1arr[0];
    printf("%c\n",a);
    int len = strlen(_1arr);
    int i;
    for(i=0; i< len; i++)
        printf("%c", _1arr[i]);

    char b = _2arr[0];
    printf("%c\n", b);
    for(;*_2arr;++_2arr) printf("%c ", *_2arr);
}

void stringArray()
{
    char strarr[] = "Programare in c este extraordinara";
    char *pString = strarr;
    char *pAlt = "Programarea in c";

    printf("%c %c\n", strarr[6], pString[6]);
    printf("%c %c\n", *(strarr+6), *(pString+6));

    char a = strarr[0];
    printf("a=%c\n", a);

    char b = pString[0];
    printf("b=%c\n", b);

    char c = pAlt[0];
    printf("c=%c\n", c);
}
void PointeriCatreArray(){

     double Myarr[7] ={22.22, 33.33,44.44,55.55,66.66,77.77,88.88};
     double *pointMyarr;
     pointMyarr = Myarr;
     int i;

     printf("Accesarea tabloului utilizand pointerul!\n");
     for(i=0; i<7; i++){
        printf("Valoarea Myarr[%d]=%f.\n", i, *(pointMyarr+i));
     }

    printf("Acesarea pointerului utilizand array-ul; \n");
    for(i=0; i<7; i++){
        printf("valoarea Myarr[%d] = %f.\n", i, *(Myarr+i));
    }
}

void PointerAndArray(){

    int myarr[7] = {11,22,33,44,55,66,77};
    int i;

    for(i=0; i<7; i++){

        printf("myarr[%d]= %d ; Adresa este %u.\n", i, myarr[i], &myarr[i]);
        printf("myarr[%d]= %d ; Adresa este %u.\n", i, *(myarr+i), myarr+i);
        printf("myarr[%d]= %d ; Adresa este %u.\n", i, *(myarr)+i, myarr+i);
        printf("myarr[%d]= %d ; Adresa este %u.\n", i, *myarr+i, myarr+i);

    }

    printf("PRIMUL ELEMENT DIN ARRAY: %u ; SI ARE VALOAREA = %d sau %d.\n", myarr, *myarr, myarr[0]);
    printf("Al DOILEA ELEMENT DIN ARRAY: %u ; SI ARE VALOAREA = %d sau %d.\n", myarr+1, *(myarr+1), myarr[0+1]);

}

void numeArrayPrimulElement(){

    int _123[7] = {88,99,11,22,33,44,55};
    int i;

    for(i=0; i<7; i++){
        printf("Array _123[%d] = %d ; Adresa este %u.\n", i, *(_123 + i), _123+i);
        printf("Array _123[%d] = %d ; Adresa este %u.\n", i, _123[i], &_123[i]);
    }
}

int main()
{
    printf("Hello world!\n");

    PointerAndArray();
    numeArrayPrimulElement();
    PointeriCatreArray();
    stringArray();
    stringToFunc(g_arr, p_g_arr);
    //const int elem = 20;
    RandomElem();
    return 0;
}
