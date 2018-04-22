/*
 * =====================================================================================
 *
 *       Filename:  phonebook.c
 *
 *    Description:  Phone Book Application with CRUD capabilities
 *
 *        Version:  1.0
 *        Created:  14-07-23 12:50:50 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  DONALD NARDI (), sav.nardi@gmail.com
 *   Organization:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// phone record data
typedef struct{
    char name[60];
    char phone[12];
} PhoneRecord;

// BST node that will hold a phone record
typedef struct treeNode {
    PhoneRecord data;
    struct treeNode *left, *right, *subname;
} TreeNode, *TreeNodePtr;


// create a linked list node for a phone record
TreeNodePtr newTreeNode(PhoneRecord record) {
    TreeNodePtr p = (TreeNodePtr) malloc(sizeof(TreeNode));
    p -> data = record;
    p -> left = p -> right = NULL;
    return p;
}

// traverse the binary tree and insert a node based on full name value
TreeNodePtr findOrInsert(TreeNodePtr bst, PhoneRecord record){
    TreeNodePtr newTreeNode(PhoneRecord);
    if (bst == NULL) return newTreeNode(record);
    TreeNodePtr curr = bst;
    int cmp;
    while((cmp = strcmp(record.name, curr->data.name)) != 0){
        if(cmp < 0){
            if(curr->left == NULL) return curr->left = newTreeNode(record);
            curr = curr -> left;
        } else {
            if(curr->right == NULL) return curr->right = newTreeNode(record);
            curr = curr->right;
        }
    }
    return curr;
}

// simple search and find BST traversal without insertion
TreeNodePtr findInBST(TreeNodePtr np, PhoneRecord record){
    TreeNodePtr curr = np;
    int cmp;

    while (curr != NULL && (cmp = strcmp(record.name, curr->data.name)) != 0) {
        if (cmp < 0) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return curr;
}

/*
    finds the minimum node value
    used for adjusting BST on deletion of a node
*/
TreeNodePtr findMin(TreeNodePtr np){
    if(np==NULL){
       /* There is no element in the tree */
       return NULL;
    }
    if(np->left){ /* Go to the left sub tree to find the min element */
        return findMin(np->left);
    } else {
       return np;
    }
}

/*
    traverse the tree and find the record to delete (if it exists).
    use the FindMin function to find and replace the deleted node
    with the next smallest value on the deleted node's right branch.
*/
TreeNodePtr delete(TreeNodePtr np, PhoneRecord record){
    TreeNodePtr temp;
    if(np==NULL){
        printf("Record not found for deletion.\n\n\n");
    } else if(strcmp(record.name,np->data.name) < 0){
        np->left = delete(np->left, record);
    } else if(strcmp(record.name, np->data.name) > 0){
        np->right = delete(np->right, record);
    } else{
        if(np->right && np->left){
            temp = findMin(np->right);
            np -> data = temp->data;
            np -> right = delete(np->right,temp->data);
        } else{
            temp = np;
            if(np->left == NULL)
                np = np->right;
            else if(np->right == NULL)
                np = np->left;
            free(temp); /* temp is no longer required */
            printf("Record deleted successfully!\n\n\n");
        }
    }
    return np;
}

/*
    runs over a text file and creates the BST from the contacts
    it finds within.
*/
TreeNodePtr loadContacts(char filename[20], TreeNodePtr bst){
    char lname[30];
    char fname[30];
    char phone[15];
    char space[2] = " ";
    int counter;
    PhoneRecord record;
    TreeNodePtr np;

    np = NULL;
    FILE *fp;

    fp = fopen(filename, "r");

    if (fp == NULL){
        printf("File doesn't exist...\n");
        printf("Making file: %s\n", filename);
        fp = fopen(filename, "w");
        fclose(fp);
        return np;
    } else {
        counter = 0;
        while (!feof(fp)){
            strcpy(lname, "");
            fscanf(fp, "%s %s %s", lname, fname, phone);
            if (strcmp(lname, "") != 0) {
                strcpy(record.name, lname);
                strcat(record.name, space);
                strcat(record.name, fname);
                strcpy(record.phone, phone);
                // make BST
                if (bst == NULL){
                    bst = newTreeNode(record);
                    return bst;
                } else {
                    np = findOrInsert(bst, record);
                }
            }
            counter++;
        }
    }
    fclose(fp);
    return np;
}

// In Order traversal for printing of contacts
void printInOrder(TreeNodePtr node){
    if (node != NULL) {
        printInOrder(node->left);
        printf("\tName:\t%s\n\tPhone:\t%s\n\n", node->data.name,node->data.phone);
        printInOrder(node->right);
    }
}

// Pre Order traversal for printing of contacts as they were entered
void printPreOrder(TreeNodePtr node){
    if (node != NULL){
        printf("\tName:\t%s\n\tPhone:\t%s\n\n",node->data.name, node->data.phone);
        printPreOrder(node->left);
        printPreOrder(node->right);
    }
}

// Save the contacts to the file in the order they were entered.
void savePreOrder(FILE *out, TreeNodePtr node){
   if (node != NULL){
        fprintf(out, "%s %s\n", node->data.name,node->data.phone);
        savePreOrder(out, node->left);
        savePreOrder(out, node->right);
    }
}

//
void closeProgram(char filename[20], TreeNodePtr bst){
    FILE *out;
    out = fopen(filename, "w");
    savePreOrder(out, bst);
    fclose(out);
    while (bst != NULL){
        bst = delete(bst, bst->data);
    }
}

void clearScreen(void){
    for (int i = 0; i < 25; i++){
        printf("\n");
    }
}

int main(int argc, char *argv[]){
    TreeNodePtr bst, np;
    PhoneRecord record;
    char input[30];
    char space[2] = " ";

    int userChoice = 0;
    bst = NULL;

    printf("Welcome to PhoneBook!\n");
    printf("Loading contacts...\n");
    bst = loadContacts("contacts.txt", bst);
    np = loadContacts("contacts.txt", bst);
    if (bst == NULL){
        printf("No contacts found.  Add some!\n");
    }

    while (userChoice != 6){
        printf("*******************************************\n");
        printf("Menu:\n");
        printf("\t1. Add a contact\n");
        printf("\t2. Delete a contact by name\n");
        printf("\t3. Search for contact by name\n");
        printf("\t4. Sort contacts by last name\n");
        printf("\t5. Print contacts\n");
        printf("\t6. Save and quit PhoneBook\n");
        printf("*******************************************\n");
        printf("> ");
        scanf(" %d", &userChoice);
        char choice = getchar();

        switch (userChoice) {
            case 1:
                printf("Enter contact's last name: ");
                scanf(" %s", input);
                strcpy(record.name,input);
                printf("Enter contact's first name: ");
                scanf(" %s", input);
                strcat(record.name, space);
                strcat(record.name, input);
                printf("Enter contact's phone number: ");
                scanf(" %s", record.phone);
                if (bst == NULL) {
                    bst = newTreeNode(record);
                    printf("Contact added!\n\n\n\n");
                    break;
                } else {
                    np = findOrInsert(bst, record);
                }
                if (strcmp(np->data.phone,record.phone) != 0){
                    printf("Contact already exists\n\n\n\n");
                } else {
                    printf("Contact added!\n\n\n\n");
                }
                break;
            case 2:
                clearScreen();
                printf("Enter contact's last name: ");
                scanf("%s", input);
                strcpy(record.name, input);
                printf("Enter contact's first name: ");
                scanf("%s", input);
                strcat(record.name, space);
                strcat(record.name, input);
                bst = delete(bst, record);
                break;
            case 3:
                clearScreen();
                printf("Enter contact's last name: ");
                scanf("%s", input);
                strcpy(record.name, input);
                printf("Enter contact's first name: ");
                scanf("%s", input);
                strcat(record.name, space);
                strcat(record.name, input);
                np = findInBST(bst, record);
                if (np == NULL) {
                    printf("\n\nRecord not found.\n\n");
                } else {
                    printf("\n\nHere is the record you were looking for:\n\tName:\t %s\n\tPhone:\t%s\n", np->data.name, np->data.phone);
                }
                break;
            case 4:
                clearScreen();
                if (bst == NULL){
                    printf("\n\nNo contacts.  Add some!\n");
                } else {
                    printf("\n\nHere are the contacts sorted by last name: \n");
                    printInOrder(bst);
                }
                break;
            case 5:
                clearScreen();
                if (bst == NULL){
                    printf("\n\nNo contacts.  Add some!\n");
                } else {
                    printf("\n\nHere are the contacts you currently have: \n");
                    printPreOrder(bst);
                }
                break;
            case 6:
                closeProgram("contacts.txt", bst);
                printf("\n\nThank you for using PhoneBook\n");
                break;
            default:
                printf("\n\nPlease enter a valid choice\n\n");
                break;
        }
    }
}
