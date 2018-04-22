#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <strings.h>
#include "hashtable.h"
#include "phonebook_orig.h"

static const unsigned int primes[] = {
        53, 97, 193, 389,
        769, 1543, 3079, 6151,
        12289, 24593, 49157, 98317,
        196613, 393241, 786433, 1572869,
        3145739, 6291469, 12582917, 25165843,
        50331653, 100663319, 201326611, 402653189,
        805306457, 1610612741
};

static const unsigned int primeseed[] = {
        31, 131, 1313, 13131, 131313
};

const unsigned int prime_table_length = sizeof(primes)/sizeof(primes[0]);
const float max_load_factor = 0.65;

/**************************************************************************/
unsigned int BKDRHash(char *str)
{
        unsigned int seed = primeseed[1];
        unsigned int hash = 0;

        while (*str) {
                hash = hash * seed + (*str++);
        }

        return (hash & 0x7FFFFFFF);
}

unsigned int hash_fn (void *value)
{
        char *lastname = (char*)value;
        return BKDRHash(lastname);
}

int equal_fn(void *key1, void *key2)
{
        char *name1 = (char *)key1;
        char *name2 = (char *)key2;
        printf("name1 %s\n", name1);
        printf("name2 %s\n", name2);

        return strcasecmp(name1, name2) == 0 ? 1 : 0;
}

/*************************************************************************/
struct hashtable *create_hashtable(unsigned int minsize, unsigned int (*hashfn) (void *),
                                   int (*eqfn)(void *, void *))
{
        struct hashtable *h;
        unsigned int pindex, size = primes[0];
        if (minsize > (1u << 30))
                return NULL;

        for (pindex = 0; pindex < prime_table_length; pindex++) {
                if(primes[pindex] > minsize) {
                        size = primes[pindex];
                        break;
                }
        }

        h = (struct hashtable*)malloc(sizeof(struct hashtable));
        if (!h) {
                perror(strerror(errno));
                return NULL;
        }

        h->table = (struct entry **)malloc(sizeof(struct entry*) * size);
        if (!h->table) {
                free(h);
                perror(strerror(errno));
                return NULL;
        }

        memset(h->table, 0, sizeof(struct entry*) * size);
        h->tablelength = size;
        h->primeindex = pindex;
        h->entrycount = 0;
        h->hashfn = hashfn;
        h->eqfn = eqfn;
        h->loadlimit = (unsigned int) ceil(size * max_load_factor);
        return h;
}

unsigned int hash(struct hashtable *h, void *key)
{
        unsigned int i = h->hashfn(key);
        i += ~(i << 9);
        i ^= ((i >> 14) | (i >> 18));
        i += (i << 4);
        i ^= ((i >> 10) | (i >> 22));
        return i;
}

static int hashtable_expand(struct hashtable *h)
{
        struct entry **newtable;
        struct entry *e;
        struct entry **pE;
        unsigned int newsize, i, index;

        if (h->primeindex == (prime_table_length - 1))
                return 0;

        newsize = primes[++(h->primeindex)];

        newtable = (struct entry **)malloc(sizeof(struct entry*) * newsize);
        if (newtable) {
                memset(newtable, 0, newsize * sizeof(struct entry *));
                for(i = 0; i < h->tablelength; ++i) {
                        while ((e = h->table[i])) {
                                h->table[i] = e->next;
                                index = indexFor(newsize, e->h);
                                e->next = newtable[index];
                                newtable[index] = e;
                        }
                }
                free(h->table);
                h->table = newtable;
        } else {
                newtable = (struct entry**)realloc(h->table, newsize * sizeof(struct entry*));
                if (!newtable) {
                        (h->primeindex)--;
                        perror(strerror(errno));
                        return 0;
                }
                h->table = newtable;
                memset(newtable[h->tablelength], 0, newsize - h->tablelength);
                for (i = 0; i < h->tablelength; ++i) {
                        for (pE = &(newtable[i]), e = *pE; e != NULL; e = *pE) {
                                index = indexFor(newsize, e->h);
                                if (index == 1)
                                        pE = &(e->next);
                                else {
                                        *pE = e->next;
                                        e->next = newtable[index];
                                        newtable[index] = e;
                                }
                        }
                }
        }
        h->tablelength = newsize;
        h->loadlimit = (unsigned int) ceil(newsize * max_load_factor);
        return 0;
}

unsigned int hashtable_count(struct hashtable *h)
{
        return h->entrycount;
}

int hashtable_insert(struct hashtable *h, void *key, void *value)
{
        unsigned int index;
        struct entry *e;
        if (++(h->entrycount) > h->loadlimit)
                hashtable_expand(h);

        e = (struct entry *)malloc(sizeof(struct entry));
        if (!e) {
                --(h->entrycount);
                perror(strerror(errno));
                return 0;
        }

        e->h = hash(h, key);
        index = indexFor(h->tablelength, e->h);
        e->key = key;
        e->value = value;
        e->next = h->table[index];
        h->table[index] = e;
        return 0;
}

void *hashtable_search(struct hashtable *h, void *key)
{
        struct entry *e;
        unsigned int hashvalue, index;
        hashvalue = hash(h, key);
        printf("hashvalue %ud\n", hashvalue);
        index = indexFor(h->tablelength, hashvalue);
        e = h->table[index];
        while (e) {
                if ((hashvalue == e->h) && (h->eqfn(key, e->key))) {
                        printf("%p\n", e->value);
                        return e->value;
                }
                e = e->next;
        }
        return NULL;
}

void *hashtable_remove(struct hashtable *h, void *key)
{
        struct entry *e;
        struct entry **pE;
        void *value;
        unsigned int hashvalue, index;

        hashvalue = hash(h, key);
        index = indexFor(h->tablelength, hash(h, key));
        pE = &(h->table[index]);
        e = *pE;
        while (e) {
                if ((hashvalue == e->h) && (h->eqfn(key, e->key)) ) {
                        *pE = e->next;
                        h->entrycount--;
                        value = e->value;
                        free(e->key);
                        free(e);
                        return value;
                }
                pE = &(e->next);
                e = e->next;
        }
        return NULL;
}

void hashtable_destroy(struct hashtable *h, int free_values)
{
        unsigned int i;
        struct entry *e, *f;
        struct entry **table = h->table;
        if (free_values) {
                for (i = 0; i < h->tablelength; ++i) {
                        e = table[i];
                        while (e) {
                                f = e;
                                e = e->next;
                                free(f->key);
                                free(f->value);
                                free(f);
                        }
                }
        } else {
                for (i = 0; i < h->tablelength; ++i) {
                        e = table[i];
                        while (e) {
                                f = e;
                                e = e->next;
                                free(f->key);
                                free(f);
                        }
                }
        }
        free(h->table);
        free(h);
}
