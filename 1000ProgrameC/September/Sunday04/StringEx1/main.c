#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Hello world!\n");

    char contact[] = "Mihai Cornel 0722.27.07.96 Mihai Irina 0744.56.78.98";
    int len;
    const char n[2] = " ";
    char *token;

    char str[5]= "Cornel";
    puts(str);
    printf("%s\n", str);

    printf("\nContact: %s.\n", contact);
    puts(contact);

    len = strlen(contact);
    printf("Lungimea stringului: %d de caractere.\n", len);

    token = strtok(contact, n);
    while(token != NULL){
        printf("%s\n", token);
        token = strtok(NULL,n);
    }
     //puts(len);


    return 0;
}
