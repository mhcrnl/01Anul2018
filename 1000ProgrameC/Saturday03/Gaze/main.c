#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Gaze {
    char luna[15];
    int index;
};

enum Luna { ianuarie, februarie, martie, aprilie, mai, iunie, iulie,
            august, septembrie, octombrie, noiembrie, decembrie};

//enum Luna luna;

void insertData(struct Gaze gaze[], int dim){
    char luna[15];
    int i;

    for(i=0; i<dim; i++){
        puts("Introduce-ti luna (ianuarie etc.) : ");
        scanf("%s", &luna);
        strcpy(gaze[i].luna, luna);
        puts("Introduce-ti indexul: ");
        scanf("%d", gaze[i].index);
    }

}

void printEnum(enum Luna luna, int dim){
    int i;
    for(i=0; i<dim; i++){
        printf("%d", luna=1);
    }
}

void afisareGaze(struct Gaze gaze){
    printf("LUNA: %s ; INDEX: %d \n", gaze.luna, gaze.index);

}

void afisareGaze1(struct Gaze gaze[], int dim){

    int i;

    for(i=0; i<dim; i++){
       printf("LUNA: %s ; INDEX: %d \n", gaze[i].luna, gaze[i].index);
    }
}

int difConsum(struct Gaze gaze[], int dim){
    int i, ret;
    for(i=0; i<dim; i++){
        ret = gaze[i+1].index-gaze[i].index ;
    }
    printf("DIFERENTA consum: %d\n", ret);
    return ret;
}


int main()
{
    printf("Hello world!\n");

    struct Gaze gazeIan;
    struct Gaze gaze2016[12];

    strcpy(gaze2016[0].luna , "Ianuarie");
    gaze2016[0].index= 203 ;

    strcpy(gaze2016[1].luna , "Februarie");
    gaze2016[1].index= 205 ;

    afisareGaze1(gaze2016, 12);
    difConsum(gaze2016, 1);

    strcpy(gazeIan.luna, "Ianuarie");
    gazeIan.index = 234;

    insertData(gaze2016, 2);

    enum Luna luna;
    printEnum(luna, 11);

    afisareGaze(gazeIan);

    return 0;
}
