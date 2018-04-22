/*
 * AUTHOR: Mihai Cornel  mhcrnl@gmail.com
 * File main.c  Date: Sat Jul 30 2016
 * Program -
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <iostream.h>

/**< Data de inceput a timpului
    OUTPUT: Sun Jan 00:00:00 1900
 */
void startOfCalendarTime(){
    struct tm start = {.tm_mday = 1};
    mktime(&start);
    printf("%s \n", asctime(&start));
}
/**
 *  The following program computes the number of seconds that
        have passed since the beginning of the month.
 *  RETURN : double seconds passed from beginning of the month.
 */

double secondsPastFromBeginningOfMonth1(){
    time_t acum = time(NULL);
    struct tm beginOfMonth;
    beginOfMonth = *localtime(&acum);
    beginOfMonth.tm_hour = 0;
    beginOfMonth.tm_min = 0;
    beginOfMonth.tm_sec = 0;
    beginOfMonth.tm_mday =1;
    double seconds = difftime(acum, mktime(&beginOfMonth));
    return seconds;
}
/**---------------------------------------------------------------------------------
 *   The following program computes the number of seconds that
        have passed since the beginning of the month.
 *  OUTPUT: 2344323 seconds have passed since the beginning of the month.
 -----------------------------------------------------------------------------------*/

void secondsPastFromBeginningOfMonth(){
    time_t acum = time(NULL);

    struct tm beginOfMonth;
    beginOfMonth = *localtime(&acum);
    // set the begin of month
    beginOfMonth.tm_hour = 0;
    beginOfMonth.tm_min = 0;
    beginOfMonth.tm_sec = 0;
    beginOfMonth.tm_mday = 1;
    double seconds = difftime(acum, mktime(&beginOfMonth));
    printf("%.f seconds have passed since the beginning of the month.\n", seconds);
}
/** ----------------------------------------------------------------------
        Functie pt. afisarea timpului actual cu tip de returnare
        time_t time( time_t *arg );
    Return: Sat Jul 30 06:38:10 2016

------------------------------------------------------------------------- */
time_t DataAcum1(){
    time_t acum = time(NULL);
   // time(&acum);
    if(acum != -1)
        return acum;
}


int main()
{
    printf("Hello world!\n");

    clock_t ceas = clock();
    printf("CEAS: %f \n", ceas);
    int i;
    for( i =0; i<1000; i++){
        printf("%f ",i);
    }
    printf("CEAS: %f \n", ceas);

    startOfCalendarTime();

    double sec = secondsPastFromBeginningOfMonth1();
    printf("Secunde trecute de la inceputul lunii: %f \n", sec);

    secondsPastFromBeginningOfMonth();

    time_t data;
    data = DataAcum1();
    printf("Data acum: %s", ctime(&data));

    DataAcum();

    time_t myTime;
    myTime = time(NULL);
    printf(ctime(&myTime));

    return EXIT_SUCCESS;
}
/**
 *      Functia afiseaza data actuala si utilizeaza functia
 *      time_t
 * Print: Sat Jul 30 06:38:10 2016
 *
 */


 void DataAcum() {
    time_t timp;
    timp = time(NULL);  /**  Get current time; same as time(&timp)   */
    printf(ctime(&timp));
 }
