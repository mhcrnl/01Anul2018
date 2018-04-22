#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Hello world!\n");

    char string[256];
    int i;

    puts("Introduce-ti un text pt functia scanf(): ");
    /**< Aceasta functie preia doar primul cuvant pana la intalnirea caracterului gol
    string este fara & deoarece acesta nu este necesar*/
    scanf("%s", string);
    printf("A-ti introdus stringul: %s", string);

    puts("Va rog introduce-ti un string lung pt functia fgets: ");
    fgets(string, 256, stdin);
    for(i=0; i<256; i++){
        if(string[i]=='\n'){
            string[i] = '\0';
            break;
        }
    }

    printf("A-ti introdus stringul: %s", string);

    return 0;
}
