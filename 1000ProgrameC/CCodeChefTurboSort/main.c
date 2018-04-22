#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b){
    return (*(int*)a) - *(int*)b;
}

int main()
{
    int nrElem;
    //printf("Insert the number of elements: \n");
    scanf("%d", &nrElem);
    int values[nrElem];
    //printf("Insert elements of the array: \n");
    int i;
    for(i=0; i<nrElem; i++){
        scanf("%d", &values[i]);
    }
    //sort the elements with qsort function from stdlib.h
    qsort(values, nrElem, sizeof(int), compare);
    //printf("Print the array after sort:\n");
    for(i=0; i<nrElem; i++){
        printf("%d\n", values[i]);
    }

    return 0;
}
