#include <stdio.h>
#include <stdlib.h>

void inversareCuvant()
{
    char cuvant;

    printf("Introduceti un cuvant: ");
    scanf("%s", &cuvant);

    if(cuvant != " ") inversareCuvant();

    printf("Afisare inversare Cuvant: %s\n", cuvant);
}
/**< Factorialul unui numar 5 > 1*2*3*4*5 = 120 */
int factorial(int n){
    return ((n>=1) ? n*(factorial(n-1)) : 1);
}

unsigned long factorial1(int numar){
    if(!numar) return 1;
    return numar*factorial1(numar-1);
}

unsigned long asociativitate(int numar)
{
    long s=0; int k;
    if(numar <= 2) return 1;
    for(k=1; k<numar; k++)
        s+= asociativitate(k) * asociativitate(numar-k);
    return s;
}

unsigned cmmdc(unsigned x, unsigned y)
{
    if(!y) return x;
    return cmmdc(y, x%y);
}

int main()
{
    printf("Hello world!\n");
    int c;
    c= factorial1(5);
    printf("FACTORIAL: %d\n", c);

    int d;
    d = asociativitate(15);
    printf("ASOCIATIVITATE: %d\n", d);

    int e;
    e = cmmdc(8, 18);
    printf("CMMDC: %d\n", e);
    //inversareCuvant();
    return 0;
}
