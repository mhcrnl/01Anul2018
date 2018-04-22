#ifndef AGENDA_H_INCLUDED
#define AGENDA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "contact.h"

typedef struct AGENDA {
    contact *valori;
    struct AGENDA *next;
} agenda;

agenda **createList(void);

#endif // AGENDA_H_INCLUDED
