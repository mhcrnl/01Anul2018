#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Hello world!\n");

    int i, n, *ptr, sum=0;

    printf("Introduce-ti numarul de elemente din array: ");
    scanf("%d", &n);

    ptr = (int*) malloc(n *sizeof(int));
    if(ptr==NULL){
        printf("Eroare memoria nu a fost alocata\n");
        exit(0);
    }

    printf("Introduce-ti elementele array-ului: ");
    for(i=0; i<n; i++){
        scanf("%d", ptr+i);
        sum += *(ptr+i);
    }

    printf("suma = %d", sum);
    free(ptr);

    return 0;
}
