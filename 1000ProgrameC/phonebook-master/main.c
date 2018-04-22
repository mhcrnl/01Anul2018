#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <sys/file.h>
#include <errno.h>
#include <sys/mman.h>
#include <unistd.h>
#include "hashtable.h"
#include "phonebook_orig.h"

#define DICT_FILE "./dictionary/words.txt"
#define PGSIZES 2

static double diff_in_second(struct timespec t1, struct timespec t2)
{
        struct timespec diff;
        if (t2.tv_nsec-t1.tv_nsec < 0) {
                diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
                diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
        } else {
                diff.tv_sec  = t2.tv_sec - t1.tv_sec;
                diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
        }
        return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

static pb_entry *search_hash(struct hashtable *h, char *name)
{
        return hashtable_search(h, name);
}

static int insert_hash(struct hashtable *h, char *strline)
{
        //insert value to the list
        pb_entry *ety = malloc(sizeof(pb_entry));
        if (!ety) {
                perror(strerror(errno));
                return -1;
        }
        memset(ety, 0, sizeof(pb_entry));
        memset(ety->lastName, 0, strlen(strline) + 1);
        memcpy(ety->lastName, strline, strlen(strline));
        if (hashtable_insert(h, ety->lastName, ety)) {
                printf("insert hashtable fail\n");
                return -1;
        }
        return 0;
}

int main(int argc, char *argv[])
{
        FILE *fp;
        int i = 0;
        char line[MAX_LAST_NAME_SIZE];
        struct timespec start, end;
        double cpu_time1, cpu_time2;
        int pagesizes;
        int cur;
        int filelen;
        char *mapedlocation;
        char *mapbuf;

        char *strline;
        char *delim;

        int remaining;

        //hashtable
        struct hashtable *h;
        h = create_hashtable(32, hash_fn, equal_fn);

        if ( -1 == (pagesizes = sysconf(_SC_PAGESIZE))) {
                perror(strerror(errno));
                return -1;
        }

        pagesizes <<= PGSIZES;                                       //for map file block size
        mapedlocation = NULL;
        mapbuf = NULL;
        cur = 0;
        delim = "\n";
        strline = NULL;
        if (NULL == (mapbuf = malloc(pagesizes))) {
                perror(strerror(errno));
                return -1;
        }

        if (mlock(mapbuf, pagesizes)) {
                perror(strerror(errno));
                return -1;
        }

        /* check file opening */
        fp = fopen(DICT_FILE, "r");
        if (fp == NULL) {
                printf("cannot open the file\n");
                return -1;
        }

        if (flock(fileno(fp), LOCK_EX)) {
                perror(strerror(errno));
                return -1;
        }

        if (-1 == fseek(fp, 0, SEEK_END)) {
                perror(strerror(errno));
                return -1;
        }

        if (-1 == (filelen = ftell(fp))) {
                perror(strerror(errno));
                return -1;
        }

        rewind(fp);
        /* build the entry */
        pb_entry *pHead, *e;
        pHead = (pb_entry *) malloc(sizeof(pb_entry));
        printf("size of phonebook entry : %lu bytes\n", sizeof(pb_entry));
        e = pHead;
        e->pNext = NULL;

#if defined(__GNUC__)
        __builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(pb_entry));
#endif
        clock_gettime(CLOCK_REALTIME, &start);

        while (cur + pagesizes < filelen) {
                memset(mapbuf, 0, pagesizes);
                if (MAP_FAILED == (mapedlocation = mmap(NULL, pagesizes,
                                                                                         PROT_READ,  MAP_PRIVATE | MAP_LOCKED,
                                                                                         fileno(fp), cur))) {
                            perror(strerror(errno));
                            return -1;
                }

                memcpy(mapbuf, mapedlocation, pagesizes);
                strline = strtok(mapbuf, delim);
                if (!strline) {
                        printf("get file content fail\n");
                        return -1;
                }

                insert_hash(h, strline);
                while ((strline = strtok(NULL, delim))) {
                        insert_hash(h, strline);
                }

                if (-1 == munlock(mapedlocation, pagesizes)) {
                        perror(strerror(errno));
                        return -1;
                }

                if (-1 == munmap(mapedlocation, pagesizes)) {
                        perror(strerror(errno));
                        return -1;
                }
                cur += pagesizes;
        }

        //add last file content
        remaining = filelen - cur;
        memset(mapbuf, 0, pagesizes);
        if (MAP_FAILED == (mapedlocation = mmap(NULL, remaining,
                                                PROT_READ,  MAP_PRIVATE | MAP_LOCKED,
                                                fileno(fp), cur))) {
                perror(strerror(errno));
                return -1;
        }

        memcpy(mapbuf, mapedlocation, remaining);
        strline = strtok(mapbuf, delim);
        if (!strline) {
                printf("get file content fail\n");
                return -1;
        }

        insert_hash(h, strline);
        while ((strline = strtok(NULL, delim))) {
                insert_hash(h, strline);
        }

        if (-1 == munlock(mapedlocation, remaining)) {
                perror(strerror(errno));
                return -1;
        }

        if (-1 == munmap(mapedlocation, remaining)) {
                perror(strerror(errno));
                return -1;
        }

        clock_gettime(CLOCK_REALTIME, &end);
        cpu_time1 = diff_in_second(start, end);

        if (flock(fileno(fp), LOCK_UN)) {
                perror(strerror(errno));
                return -1;
        }
        if (munlock(mapbuf, pagesizes)) {
                perror(strerror(errno));
                return -1;
        }
        free(mapbuf);
        /* close file as soon as possible */
        fclose(fp);

        e = pHead;

        /* the givn last name to find */
        char input[MAX_LAST_NAME_SIZE] = "zyxel";
        e = pHead;

        //assert(findName(input, e) &&
        //       "Did you implement findName() in " IMPL "?");
        //assert(0 == strcmp(findName(input, e)->lastName, "zyxel"));

#if defined(__GNUC__)
        __builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(pb_entry));
#endif
        /* compute the execution time */
        clock_gettime(CLOCK_REALTIME, &start);
        //findName(input, e);
        pb_entry *pbety = search_hash(h, input);
        clock_gettime(CLOCK_REALTIME, &end);
        cpu_time2 = diff_in_second(start, end);

        FILE *output;
#if defined(OPT)
        output = fopen("opt.txt", "a");
#else
        output = fopen("orig.txt", "a");
#endif
        fprintf(output, "append() findName() %lf %lf\n", cpu_time1, cpu_time2);
        fclose(output);

        printf("execution time of append() : %lf sec\n", cpu_time1);
        printf("execution time of findName() : %lf sec\n", cpu_time2);

        if (pHead->pNext) free(pHead->pNext);
        free(pHead);

        return 0;
}
