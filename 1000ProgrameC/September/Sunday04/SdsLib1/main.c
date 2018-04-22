#include <stdio.h>
#include <stdlib.h>
#include "sds.h"

int main()
{
    printf("Hello world!\n");

    sds myString = sdsnew ("salut din libraria sds!");
    printf("%s\n", myString);
    sdsfree(myString);

    return 0;
}
