#include "linkedlist.h"

void printList(agenda *head){

    agenda *curent = head;

    while(curent != NULL){
        printf("%s\n", curent->nume);
        curent = curent->next;
    }
}
