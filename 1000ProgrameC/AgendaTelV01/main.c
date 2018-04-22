#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "contact.h"

int main()
{
    printf("Hello world!\n");

    //char nume[20];
    //char tel[13];

    contact *head = NULL;
    head = malloc(sizeof(contact));
    if(head == NULL){
        return 1;
    }

    strcpy(head->nume, "Mihai Cornel");
    strcpy(head->tel, "0722270796");
    head->next = NULL;

    addLast(head, "Alexandru Vasile", "0754623456");
    addLast(head, "Alexandru Vasile", "0754623456");

    printLista(head);

    return 0;
}
