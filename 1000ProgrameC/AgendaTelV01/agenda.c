#include "contact.h"

void printLista(contact *head){
    contact *curent = head;
    while(curent != NULL){
        printf("%s %s\n", curent->nume, curent->tel);
        curent = curent->next;
    }
}

void addLast(contact *head, char nume[], char tel[]) {
    contact *curent = head;

    while(curent->next != NULL){
        curent = curent->next;
    }
    // Adaugarea unui nou nod
    curent->next = malloc(sizeof(contact));
    strcpy(curent->nume, nume);
    strcpy(curent->tel, tel);
    curent->next->next = NULL;
}

