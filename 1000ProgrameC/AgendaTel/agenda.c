# include "agenda.h"

agenda **createList(void){

    agenda **list = malloc(sizeof(agenda) * 2);

    list[0] = NULL;
    list[1] = NULL;

    return list;
}
