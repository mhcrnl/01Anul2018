#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Hello world!\n");

    int i, n, *ptr, sum=0;

    printf("Introduce-ti numarul de elemente in array: ");
    scanf("%d", &n);

    ptr = (int*)calloc(n, sizeof(int));
    if(ptr==NULL){
        printf("Eroare! Memoria nu a fost alocata.");
        exit(0);
    }

    printf("Introduce-ti elementele array-ului: ");
    for(i=0; i<n; ++i){
        scanf("%d", ptr+i);
        sum += *(ptr+i);
    }
    printf("SUMA=%d.", sum);
    free(ptr);

    return 0;
}
