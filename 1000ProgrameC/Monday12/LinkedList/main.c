#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"

int main()
{
    printf("Hello world!\n");

    agenda *head = NULL;
    head = malloc(sizeof(agenda));
    if(head == NULL){
        printf("Memoria nu a fost alocata!");
        return 1;
    }
    strcpy(head->nume, "Mihai Cornel");
    head->next = NULL;

    printList(head);

    return 0;
}
