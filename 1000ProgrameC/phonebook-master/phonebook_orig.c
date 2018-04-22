#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_orig.h"
#include "hashtable.h"

/* original version */
pb_entry *findName(char lastname[], pb_entry *pHead)
{
        while (pHead != NULL) {
                if (strcasecmp(lastname, pHead->lastName) == 0)
                        return pHead;
                pHead = pHead->pNext;
        }
        return NULL;
}

pb_entry *append(char lastName[], pb_entry *e)
{
        /* allocate memory for the new entry and put lastName */
        e->pNext = (pb_entry *) malloc(sizeof(pb_entry));
        e = e->pNext;
        memcpy(e->lastName, lastName, strlen(lastName));
        e->pNext = NULL;

        return e;
}
