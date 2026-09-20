/* Syllabus 20(c) : DOUBLY LINKED LIST - insert, delete, display
   Each node: prev | data | next
   Advantage: traversal in BOTH directions; deletion of a known node is O(1).
   Disadvantage: extra memory for prev; two pointers to update on every op.
   Golden rule: when inserting/deleting, update FOUR pointer fields carefully.
*/
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *prev, *next;
};

struct node *head = NULL;

struct node* createNode(int value) {
    struct node *n = (struct node *)malloc(sizeof(struct node));
    if (n == NULL) { printf("Memory allocation failed\n"); exit(1); }
    n->data = value;
    n->prev = n->next = NULL;
    return n;
}

/* ---------- INSERT AT BEGINNING ---------- */
void insertBegin(int value) {
    struct node *n = createNode(value);
    if (head != NULL) {
        n->next = head;
        head->prev = n;
    }
    head = n;
    printf("%d inserted at beginning\n", value);
}

/* ---------- INSERT AT END ---------- */
void insertEnd(int value) {
    struct node *n = createNode(value), *temp;
    if (head == NULL) { head = n; printf("%d inserted\n", value); return; }
    temp = head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = n;
    n->prev = temp;
    printf("%d inserted at end\n", value);
}

/* ---------- INSERT AFTER A GIVEN VALUE ---------- */
void insertAfter(int key, int value) {
    struct node *temp = head, *n;
    while (temp != NULL && temp->data != key) temp = temp->next;
    if (temp == NULL) { printf("%d not found\n", key); return; }

    n = createNode(value);
    n->next = temp->next;
    n->prev = temp;
    if (temp->next != NULL) temp->next->prev = n;
    temp->next = n;
    printf("%d inserted after %d\n", value, key);
}

/* ---------- DELETE BY VALUE ---------- */
void deleteValue(int key) {
    struct node *temp = head;
    while (temp != NULL && temp->data != key) temp = temp->next;
    if (temp == NULL) { printf("Unsuccessful Search - %d not found\n", key); return; }

    if (temp->prev != NULL) temp->prev->next = temp->next;
    else                    head = temp->next;        /* deleting head */

    if (temp->next != NULL) temp->next->prev = temp->prev;

    free(temp);
    printf("%d deleted\n", key);
}

void displayForward(void) {
    struct node *temp = head;
    if (temp == NULL) { printf("List is empty\n"); return; }
    printf("Forward : NULL <-> ");
    while (temp != NULL) { printf("%d <-> ", temp->data); temp = temp->next; }
    printf("NULL\n");
}

void displayBackward(void) {
    struct node *temp = head;
    if (temp == NULL) { printf("List is empty\n"); return; }
    while (temp->next != NULL) temp = temp->next;    /* go to last node */
    printf("Backward: NULL <-> ");
    while (temp != NULL) { printf("%d <-> ", temp->data); temp = temp->prev; }
    printf("NULL\n");
}

int main(void) {
    int ch, x, key;
    while (1) {
        printf("\n1.InsertBegin 2.InsertEnd 3.InsertAfter 4.Delete"
               " 5.Display Forward 6.Display Backward 7.Exit\nChoice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: printf("Value: "); scanf("%d", &x); insertBegin(x); break;
            case 2: printf("Value: "); scanf("%d", &x); insertEnd(x); break;
            case 3: printf("Insert after which value: "); scanf("%d", &key);
                    printf("Value: "); scanf("%d", &x);
                    insertAfter(key, x); break;
            case 4: printf("Value to delete: "); scanf("%d", &x);
                    deleteValue(x); break;
            case 5: displayForward(); break;
            case 6: displayBackward(); break;
            case 7: return 0;
            default: printf("Invalid choice\n");
        }
    }
}
