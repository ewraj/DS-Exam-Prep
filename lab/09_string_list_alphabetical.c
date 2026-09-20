/* Syllabus 20(a) : INSERT STRINGS INTO A LINKED LIST IN ALPHABETICAL ORDER
   This is an ORDERED LIST - the insert function finds the correct position
   using strcmp() before linking the node.

   strcmp(a,b) returns  < 0 if a < b,  0 if equal,  > 0 if a > b.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char name[50];
    struct node *next;
};

struct node *head = NULL;

void insertSorted(char str[]) {
    struct node *n, *temp, *prev = NULL;

    n = (struct node *)malloc(sizeof(struct node));
    if (n == NULL) { printf("Memory allocation failed\n"); exit(1); }
    strcpy(n->name, str);
    n->next = NULL;

    /* Case 1: empty list, or the new string comes before the head */
    if (head == NULL || strcmp(str, head->name) < 0) {
        n->next = head;
        head = n;
        printf("\"%s\" inserted\n", str);
        return;
    }

    /* Case 2: walk until we find the first node bigger than str */
    temp = head;
    while (temp != NULL && strcmp(temp->name, str) < 0) {
        prev = temp;
        temp = temp->next;
    }

    n->next = temp;        /* link forward  */
    prev->next = n;        /* link backward */
    printf("\"%s\" inserted\n", str);
}

void search(char str[]) {
    struct node *temp = head;
    int pos = 1;
    while (temp != NULL) {
        if (strcmp(temp->name, str) == 0) {
            printf("\"%s\" found at position %d\n", str, pos);
            return;
        }
        temp = temp->next; pos++;
    }
    printf("Unsuccessful Search\n");
}

void display(void) {
    struct node *temp = head;
    if (temp == NULL) { printf("List is empty\n"); return; }
    printf("Sorted list: ");
    while (temp != NULL) { printf("%s -> ", temp->name); temp = temp->next; }
    printf("NULL\n");
}

int main(void) {
    int ch;
    char str[50];
    while (1) {
        printf("\n1.Insert string 2.Search 3.Display 4.Exit\nChoice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: printf("Enter string: "); scanf("%s", str);
                    insertSorted(str); break;
            case 2: printf("Enter string to search: "); scanf("%s", str);
                    search(str); break;
            case 3: display(); break;
            case 4: return 0;
            default: printf("Invalid choice\n");
        }
    }
}
