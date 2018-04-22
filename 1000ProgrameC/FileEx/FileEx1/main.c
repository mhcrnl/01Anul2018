#include <stdio.h>
#include <stdlib.h>

#include "fileEx1.h"

int main()
{
    printf("Hello world!\n");

    char filename[20] = "textfile.txt";
    int myArr[10] = {2,4,6,2,1,3,6,7,4};

    writeFile(filename, 10, myArr);

    return 0;
}
