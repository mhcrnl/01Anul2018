#include "fileEx1.h"

void writeFile(char filename[],int size1, int arr[size1]){
    FILE *fp;
    fp = fopen(filename,"a");
    if(fp == NULL){
        printf("Fila %s nu a fost deschisa. Eroare: %s.\n", filename, strerror(errno));
    }

    for(int i=0; i<size1; i++){
        fprintf(fp, "%d", arr[i]);
    }


    fclose(fp);
}
