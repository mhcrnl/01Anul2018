#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <conio.h>

typedef struct Element Element;
typedef struct List List;
typedef struct Contact Contact;

struct Contact {
    int id;
    char firstName[20], lastName[20], phoneNumber[20], sex[5], email[40], address[100];
};

struct Element {
    Contact val;
    Element *tail;
};

struct List {
    Element *head;
    int size;
};

List * initList() {
    List *l;
    l = (List*)malloc(sizeof(List));
    l->head = NULL;
    l->size = 0;
    return l;
};

//Global variable
char OPTION; //the chosen option
List *l; //initialize list which is the container of a whole program

//Prototype of all the functions

void menu();
void chooseOption(char OPTION);
void addNewContact();
void addToList(Contact val);
void displayAllContacts();
void displayByLastName();
void displayByFirstName();
void updateContactToList();
void deleteContactFromList();
void writeIntoFile();
void readIntoList();
void recentContact();

///////////////////////////////////////////////
////////////////Program start//////////////////
///////////////////////////////////////////////

int main() {
    FILE *file;
    char *fileName;
    fileName = "phonebookData.txt";
    file = fopen(fileName, "a");
    l = initList();
    readIntoList();

    printf("Welcome to PhoneBook Application!!!\n\n");

    while(1) {
        menu();
        chooseOption(OPTION);
    }

    return 0;
}

///////////////////////////////////////////////
////////////////Program end////////////////////
///////////////////////////////////////////////

void menu() {
    printf("*********************************************************\n");
    printf("*\t\t\t\t\t\t\t*\n");
    printf("*\tMenu:\t\t\t\t\t\t*\n");
    printf("*\t\t\t\t\t\t\t*\n");
    printf("*\tPossible Option:\t\t\t\t*\n");
    printf("*\t1. Add a new contact\t\t\t\t*\n");
    printf("*\t2. Display all contacts\t\t\t\t*\n");
    printf("*\t3. Display contact(s) by last name\t\t*\n");
    printf("*\t4. Display contact(s) by first name\t\t*\n");
    printf("*\t5. Update a contact (by using phone number)\t*\n");
    printf("*\t6. Delete a contact (by using phone number)\t*\n");
    printf("*\t7. Exit the program and save\t\t\t*\n");
    printf("*\t\t\t\t\t\t\t*\n");
    printf("*********************************************************\n\n");
    printf("Choose an operation[1-7]: ");
    //OPTION = getc();
}

void chooseOption(char OPTION) {
    char answer;
    switch (OPTION) {
        case '1':
            addNewContact();
            break;
        case '2':
            displayAllContacts();
            break;
        case '3':
            displayByLastName();
             break;
        case '4':
            displayByFirstName();
            break;
        case '5':
            if (l->size >= 1) {
                updateContactToList();
            } else {
                printf("\nSorry, there is no contact to update!!!\n");
            }
            break;
        case '6':
            if (l->size >= 1) {
                deleteContactFromList();
            } else {
                printf("\nSorry, there is no contact to delete!!!\n");
            }
            break;
        case '7':
            printf("\nAre you sure you want to exit and save the program? [Y/N] : ");
            scanf("%s", &answer);
            if (answer == 'y' || answer == 'Y') {
                printf("\nGood bye!!!\n");
                writeIntoFile();
                exit(0);
            }
            system("cls");
            printf("Welcome back!!!\n");
            break;
        default:
            system("cls");
            printf("Option not found!!!\n");
            printf("Please try to choose another option\n\n");
            break;
    }
}

void addNewContact() {
    Contact new_contact;
    Element *tmp;
    tmp = l->head;

    if (l->size == 0) {
        new_contact.id = 0;
    } else {
        Element *tmp1;
        tmp1 = l->head;
        while (tmp1 != NULL) {
            new_contact.id = tmp1->val.id;
            tmp1 = tmp1->tail;
        }
        new_contact.id++;
    }
    system("cls");
    printf("New Contact\n\n");
    printf("Please:\n");
    printf("  Input your last name: ");
    scanf("%s", new_contact.lastName);
    printf("  Input your first name: ");
    scanf("%s", new_contact.firstName);
    up:
    printf("  Input your phone number: ");
    scanf("%s", new_contact.phoneNumber);
    while (tmp != NULL) {
        if (strcmp(tmp->val.phoneNumber, new_contact.phoneNumber) == 0) {
            printf("\n\n  This phone number is already registered.\n");
            printf("  Please make sure you input the new number.\n\n");
            goto up;
        }
        tmp = tmp->tail;
    }
    again:
    printf("  Input your gender [M/F]: ");
    scanf("%s", new_contact.sex);
    if (strcmp(new_contact.sex, "M") != 0 && strcmp(new_contact.sex, "F") != 0 && strcmp(new_contact.sex, "m") != 0 && strcmp(new_contact.sex, "f") != 0) {
        printf("\n  Invalid! Please input M/F\n\n");
        goto again;
    }
    printf("  Input your email: ");
    scanf("%s", new_contact.email);
    printf("  Input your address: ");
    fgets(new_contact.address, 100, stdin);
    fgets(new_contact.address, 100, stdin);
    printf("\nYour contact is temporary saved.\nPress any key to return back to menu.\n");
    //getch();
    system("cls");
    addToList(new_contact);
}

void addToList(Contact val){
    if (l->size == 0) {
        Element *tmp;
        tmp = (Element*)malloc(sizeof(Element));
        tmp->val.id = val.id;
        strcpy(tmp->val.firstName, val.firstName);
        strcpy(tmp->val.lastName, val.lastName);
        strcpy(tmp->val.phoneNumber, val.phoneNumber);
        strcpy(tmp->val.sex, val.sex);
        strcpy(tmp->val.email, val.email);
        strcpy(tmp->val.address, val.address);
        tmp->tail = l->head;
        l->head = tmp;
        l->size += 1;
    }
    else{
        Element *tmp, *queue;
        tmp = (Element*)malloc(sizeof(Element));
        tmp->val.id = val.id;
        strcpy(tmp->val.firstName, val.firstName);
        strcpy(tmp->val.lastName, val.lastName);
        strcpy(tmp->val.phoneNumber, val.phoneNumber);
        strcpy(tmp->val.sex, val.sex);
        strcpy(tmp->val.email, val.email);
        strcpy(tmp->val.address, val.address);
        tmp->tail = NULL;
        queue = l->head;
        while (queue->tail != NULL){
            queue = queue->tail;
        }
        queue->tail = tmp;
        l->size += 1;
    }
}

void displayAllContacts(){
    Element *tmp;
    tmp = l->head;
    int noContact = 1;
    system("cls");
    printf("Display All Contacts\n");
    while (tmp != NULL){
        printf("\n\tID: %d\t\t\tName: %s %s\n", tmp->val.id, tmp->val.lastName, tmp->val.firstName);
        printf("\tSex: %s\t\t\tPhone Number: %s\n", tmp->val.sex, tmp->val.phoneNumber);
        printf("\tEmail: %s\n", tmp->val.email);
        printf("\tAddress: %s\n", tmp->val.address);
        noContact = 0;
        tmp = tmp->tail;
    }

    if (noContact) {
        system("cls");
        printf("Sorry, your phone book is empty!!!\n");
    }
    printf("\nPress any key to return back to menu.\n");
    //getch();
    system("cls");
}

void displayByLastName() {
    Element *tmp;
    char lastName[20];
    int notFound = 1;
    system("cls");
    printf("Search Contact by last name\n\n");
    printf("Input the last name: ");
    scanf("%s", lastName);

    tmp = l->head;
    system("cls");
    printf("Display Contacts by Last Name\n");
    while (tmp != NULL) {
        if (strcmpi(tmp->val.lastName, lastName) == 0) {
            printf("\n\tID: %d\t\t\tName: %s %s\n", tmp->val.id, tmp->val.lastName, tmp->val.firstName);
            printf("\tSex: %s\t\t\tPhone Number: %s\n", tmp->val.sex, tmp->val.phoneNumber);
            printf("\tEmail: %s\n", tmp->val.email);
            printf("\tAddress: %s\n", tmp->val.address);
            notFound = 0;
        }
        tmp = tmp->tail;
    }

    if (notFound) {
        system("cls");
        printf("Sorry, no contact found!!!\n");
    }
    printf("\nPress any key to return back to menu.\n");
    getch();
    system("cls");
}

void displayByFirstName() {
    Element *tmp;
    char firstName[20];
    int notFound = 1;
    system("cls");
    printf("Search Contact by first name\n\n");
    printf("Input the first name: ");
    scanf("%s", firstName);

    tmp = l->head;
    system("cls");
    printf("Display Contacts by First Name:\n");
    while (tmp != NULL) {
        if (strcmpi(tmp->val.firstName, firstName) == 0) {
            printf("\n\tID: %d\t\t\tName: %s %s\n", tmp->val.id, tmp->val.lastName, tmp->val.firstName);
            printf("\tSex: %s\t\t\tPhone Number: %s\n", tmp->val.sex, tmp->val.phoneNumber);
            printf("\tEmail: %s\n", tmp->val.email);
            printf("\tAddress: %s\n", tmp->val.address);
            notFound = 0;
        }
        tmp = tmp->tail;
    }

    if (notFound) {
        system("cls");
        printf("Sorry, no contact found!!!\n");
    }
    printf("\nPress any key to return back to menu.\n");
    getch();
    system("cls");
}

void updateContactToList() {
    recentContact();

    char num[20], answer;
    Element *tmp;
    tmp = l->head;
    system("cls");
    printf("Update Contact by phone number\n\n");
    printf("Input contact phone number that you wish to update: ");
    scanf("%s", num);

    int found = 0;

    while (tmp != NULL) {
        if (strcmp(tmp->val.phoneNumber, num) == 0) {
            found = 1;
            break;
        }
        tmp = tmp->tail;
    }

    if (found == 1) {
        Contact up_contact;
        system("cls");
        printf("Recent contact information:\n");
        printf("\tID: %d\t\t\tName: %s %s\n", tmp->val.id, tmp->val.lastName, tmp->val.firstName);
        printf("\tSex: %s\t\t\tPhone Number: %s\n", tmp->val.sex, tmp->val.phoneNumber);
        printf("\tEmail: %s\n", tmp->val.email);
        printf("\tAddress: %s\n", tmp->val.address);
        printf("\nContact Update: \n");
        printf("  Input your last name: ");
        scanf("%s", up_contact.lastName);
        printf("  Input your first name: ");
        scanf("%s", up_contact.firstName);
        up:
        printf("  Input your phone number: ");
        scanf("%s", up_contact.phoneNumber);
        Element *tmp1;
        tmp1 = l->head;
        while (tmp1 != NULL) {
            if (strcmp(tmp1->val.phoneNumber, up_contact.phoneNumber) == 0 && strcmp(tmp1->val.phoneNumber, num) != 0) {
                printf("\n  This phone number is already registered.\n");
                printf("  Please make sure you input the new number.\n\n");
                goto up;
            }
            tmp1 = tmp1->tail;
        }
        again:
        printf("  Input your gender [M/F]: ");
        scanf("%s", up_contact.sex);
        if (strcmp(up_contact.sex, "M") != 0 && strcmp(up_contact.sex, "F") != 0 && strcmp(up_contact.sex, "m") != 0 && strcmp(up_contact.sex, "f") != 0) {
            printf("\n  Invalid! Please input M/F\n\n");
            goto again;
        }
        printf("  Input your email: ");
        scanf("%s", up_contact.email);
        printf("  Input your address: ");
        fgets(up_contact.address, 100, stdin);
        fgets(up_contact.address, 100, stdin);

        printf("\nAre you sure you want to update this contact? [Y/N]: ");
        scanf("%s", &answer);

        if (answer == 'y' || answer == 'Y') {
            strcpy(tmp->val.firstName, up_contact.firstName);
            strcpy(tmp->val.lastName, up_contact.lastName);
            strcpy(tmp->val.phoneNumber, up_contact.phoneNumber);
            strcpy(tmp->val.sex, up_contact.sex);
            strcpy(tmp->val.email, up_contact.email);
            strcpy(tmp->val.address, up_contact.address);
            printf("\nContact temporary updated!!!\n");
        } else {
            printf("\nContact does not update!!!\n");
        }
    } else {
        printf("\nThere is no contact that matched this phone number: '%s'!!!\n", num);
    }
    printf("\nPress any key to return back to menu.\n");
    getch();
    system("cls");
}

void deleteContactFromList(){
    recentContact();
    char num[20], answer;
    Element *tmp;
    tmp = l->head;
    system("cls");
    printf("Delete Contact by phone number\n\n");
    printf("Input contact phone number that you wish to delete: ");
    scanf("%s", num);

    int pos = 0, found = 0;

    while (tmp != NULL) {
        if (strcmp(tmp->val.phoneNumber, num) == 0) {
            found = 1;
            break;
        }
        tmp = tmp->tail;
        pos++;
    }

    if (found == 1) {
        printf("\nAre you sure you want to delete this contact? [Y/N] : ");
        scanf("%s", &answer);

        if (answer == 'y' || answer == 'Y') {
            if (pos == 0) {
                Element *tmp1;
                tmp1 = l->head;
                l->head = l->head->tail;
                free(tmp1);
                l->size -= 1;
            }
            else {
                Element *tmp1, *tmp2;
                tmp2 = l->head;
                int i;
                for (i=1; i<=pos-1; i++){
                    tmp2 = tmp2->tail;
                }
                tmp1 = tmp2->tail;
                tmp2->tail = tmp1->tail;
                free(tmp1);
                l->size -= 1;
            }
            printf("\nContact temporary deleted.\n");
        } else {
            printf("\nContact does not delete!!!\n");
        }
    } else {
        printf("\nThere is no contact that matched this phone number: '%s'!!!\n", num);
    }
    printf("\nPress any key to return back to menu.\n");
    getch();
    system("cls");
}

void writeIntoFile() {
    Element *tmp;
    tmp = l->head;

    FILE *file;
    char *fileName, id[5];
    fileName = "phonebookData.txt";
    file = fopen(fileName, "w+");

    while (tmp != NULL){
        sprintf(id, "%d", tmp->val.id);
        fputs(id, file);
        fputs("|", file);
        fputs(tmp->val.firstName, file);
        fputs("|", file);
        fputs(tmp->val.lastName, file);
        fputs("|", file);
        fputs(tmp->val.phoneNumber, file);
        fputs("|", file);
        fputs(tmp->val.sex, file);
        fputs("|", file);
        fputs(tmp->val.email, file);
        fputs("|", file);
        fputs(tmp->val.address, file);
        tmp = tmp->tail;
    }
    fclose(file);
}

void readIntoList() {
    Contact new_contact;
    FILE *file;
    char *fileName;
    fileName = "phonebookData.txt";
    file = fopen(fileName, "r");
    char content[1000];
    char str[1000];

    while (fgets(content, 1000, file) != NULL) {
        strcpy(str,content);
        char * pch;
        char splitted_string[7][100];
        pch = strtok (str,"|");
        int index = 0;
        while (pch != NULL) {
            strcpy(splitted_string[index],pch);
            pch = strtok(NULL, "|");
            index++;
        }
        new_contact.id = atoi(splitted_string[0]);
        strcpy(new_contact.firstName, splitted_string[01]);
        strcpy(new_contact.lastName, splitted_string[2]);
        strcpy(new_contact.phoneNumber, splitted_string[3]);
        strcpy(new_contact.sex, splitted_string[4]);
        strcpy(new_contact.email, splitted_string[5]);
        strcpy(new_contact.address, splitted_string[6]);
        addToList(new_contact);
    }
    fclose(file);
}

void recentContact(){
    Element *tmp;
    tmp = l->head;
    int noContact = 1;
    system("cls");
    printf("Recent Contacts\n");
    while (tmp != NULL){
        printf("\n\tID: %d\t\t\tName: %s %s\n", tmp->val.id, tmp->val.lastName, tmp->val.firstName);
        printf("\tSex: %s\t\t\tPhone Number: %s\n", tmp->val.sex, tmp->val.phoneNumber);
        printf("\tEmail: %s\n", tmp->val.email);
        printf("\tAddress: %s\n", tmp->val.address);
        noContact = 0;
        tmp = tmp->tail;
    }
}
