#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16

/* original version */
typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
  struct detail *detail;
    struct __PHONE_BOOK_ENTRY *pNext;
} pb_entry;

typedef struct __PHONE_BOOK_DETAIL {
  char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
}detail;

pb_entry *findName(char lastname[], pb_entry *pHead);
pb_entry *append(char lastName[], pb_entry *e);

#endif
