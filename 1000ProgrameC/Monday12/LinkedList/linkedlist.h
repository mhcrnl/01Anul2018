#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct AGENDA {
    char nume[20];
    struct AGENDA *next;
}agenda;

void printList(agenda *head);

#endif // LINKEDLIST_H_INCLUDED
