#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Hello world!\n");

    int *ptr, i, n1, n2;

    printf("Introduce-ti dimensiunea array-ului: ");
    scanf("%d", &n1);

    ptr = (int*) malloc(n1*sizeof(int));
    printf("Adresa memoriei alocate anterior: ");
    for(i=0; i<n1; ++i){
        printf("%u\t", ptr+i);
    }
    printf("Introduce-ti noua dimensiune a array-ului: ");
    scanf("%d", &n2);

    ptr = realloc(ptr,n2);
    for(i=0; i<n2;++i){
        printf("%u\t", ptr+i);
    }
    return 0;
}
