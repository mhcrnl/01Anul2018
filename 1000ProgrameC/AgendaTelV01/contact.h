#ifndef CONTACT_H_INCLUDED
#define CONTACT_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct CONTACT {
    char nume[20];
    char tel[13];
    struct CONTACT *next;
} contact;

/**< 1. Afisarea listei */
void printLista(contact *head);
/**< 2. Adaugare la sfarsitul listei */
void addLast(contact *head, char nume[], char tel[]);

#endif // CONTACT_H_INCLUDED
