//hashtable header file
#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

struct entry {
        void *key, *value;
        unsigned int h;
        struct entry *next;
};

struct hashtable {
        unsigned int tablelength;
        struct entry **table;
        unsigned int entrycount;
        unsigned int loadlimit;
        unsigned int primeindex;
        unsigned int (*hashfn) (void *key);
        int (*eqfn) (void *k1, void *k2);
};

/******************************************************/
static inline unsigned int indexFor(unsigned int tablelength, unsigned int hashvalue)
{
        return (hashvalue % tablelength);
}

/******************************************************************************************/
unsigned int BKDRHash(char *str);
int equal_fn(void *key1, void *key2);
unsigned int hash_fn (void *value);

/******************************************************************************************/
struct hashtable *create_hashtable(unsigned int minsize, unsigned int (*hashfunction) (void *),
                                   int (*key_eq_fn)(void*, void*));

int hashtable_insert(struct hashtable *h, void *key, void *value);

#define DEFINE_HASHTABLE_INSERT(fnname, keytype, valuetype)        \
int fnname(struct hashtable *h, keytype *key, valuetype *value)           \
{        \
        return hashtable_insert(h, key, value);            \
}

void *hashtable_search(struct hashtable *h, void *key);

#define DEFINE_HASHTABLE_SEARCH(fnname, keytype, valuetype)    \
valuetype *fnname(struct hashtable *h, keytype *k)    \
{    \
        return (valuetype *) (hashtable_search(h, k));        \
}

void *hashtable_remove(struct hashtable *h, void *key);

#define DEFINE_HASHTABLE_REMOVE(fnname, keytype, valuetype)    \
valuetype *fnname(struct hashtable *h, keytype *k)    \
{    \
        return (valuetype *) (hashtable_remove(h, k));        \
}

unsigned int hashtable_count(struct hashtable *h);

void hashtable_destroy(struct hashtable *h, int free_values);

#endif
