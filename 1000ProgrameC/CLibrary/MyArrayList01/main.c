#include <stdio.h>
#include <stdlib.h>

#include "ArrayList.h"

int main()
{
    printf("Hello world!\n");

    ArrayList *l;
    l = createArrayList(10);
    put(l,"vasile");
    return 0;
}
