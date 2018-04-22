#include <stdio.h>
#include <stdlib.h>

int *MallocArray(int nrElem);

int main()
{
    printf("Hello world!\n");

    int *pointerArray, i, nrElem=10;
    pointerArray = MallocArray(nrElem);
    for(i=0;i<nrElem; i++){
        printf("%d ", pointerArray+i);
    }

    return 0;
}

int *MallocArray(int nrElem)
{
    int *ptr, i;

    //printf("Introduce-ti numarul de elemente din array: ");
    //scanf("%d", &n);

    ptr = (int*)malloc(nrElem*sizeof(int));
    if(ptr = NULL){
        printf("ERROARE! Memoria nu a fost alocata. ");
        exit(0);
    }

    printf("Introduce-ti valorile elementelor din array: ");
    for(i=0; i<nrElem; i++){
        scanf("%d", ptr+i);
    }

    return ptr;
    free(ptr);

}
