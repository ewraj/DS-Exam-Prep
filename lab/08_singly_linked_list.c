/* SINGLY LINKED LIST - full menu (base program for Unit 2)
   Insert at beginning / end / at a position, delete, search, display, reverse.
   This is the program to master: everything else is a variation of it.
*/
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;     /* self-referential structure */
};

struct node *head = NULL;

struct node* createNode(int value) {
    struct node *n = (struct node *)malloc(sizeof(struct node));
    if (n == NULL) { printf("Memory allocation failed\n"); exit(1); }
    n->data = value;
    n->next = NULL;
    return n;
}

/* ---------- INSERT AT BEGINNING : O(1) ---------- */
void insertBegin(int value) {
    struct node *n = createNode(value);
    n->next = head;        /* new node points to old head */
    head = n;              /* new node becomes head       */
}

/* ---------- INSERT AT END : O(n) ---------- */
void insertEnd(int value) {
    struct node *n = createNode(value), *temp;
    if (head == NULL) { head = n; return; }
    temp = head;
    while (temp->next != NULL) temp = temp->next;   /* walk to last node */
    temp->next = n;
}

/* ---------- INSERT AT POSITION (1-based) ---------- */
void insertAt(int value, int pos) {
    struct node *n, *temp;
    int i;
    if (pos < 1) { printf("Invalid position\n"); return; }
    if (pos == 1) { insertBegin(value); return; }

    temp = head;
    for (i = 1; i < pos - 1 && temp != NULL; i++)   /* stop at pos-1 */
        temp = temp->next;

    if (temp == NULL) { printf("Position out of range\n"); return; }

    n = createNode(value);
    n->next = temp->next;      /* ORDER MATTERS: link new node first */
    temp->next = n;            /* then link previous node to it      */
}

/* ---------- DELETE BY VALUE ---------- */
void deleteValue(int key) {
    struct node *temp = head, *prev = NULL;

    if (head == NULL) { printf("List is empty\n"); return; }

    if (head->data == key) {           /* deleting the head */
        head = head->next;
        free(temp);
        printf("%d deleted\n", key);
        return;
    }

    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) { printf("Unsuccessful Search - %d not found\n", key); return; }

    prev->next = temp->next;           /* bypass the node */
    free(temp);
    printf("%d deleted\n", key);
}

/* ---------- SEARCH : Syllabus 20(b) ---------- */
void search(int key) {
    struct node *temp = head;
    int pos = 1;
    while (temp != NULL) {
        if (temp->data == key) {
            printf("%d found at position %d\n", key, pos);
            return;
        }
        temp = temp->next;
        pos++;
    }
    printf("Unsuccessful Search - %d not found\n", key);
}

/* ---------- REVERSE (iterative, 3 pointers) ---------- */
void reverse(void) {
    struct node *prev = NULL, *curr = head, *next = NULL;
    while (curr != NULL) {
        next = curr->next;     /* save the rest      */
        curr->next = prev;     /* flip the link      */
        prev = curr;           /* move prev forward  */
        curr = next;           /* move curr forward  */
    }
    head = prev;               /* prev is the new head */
    printf("List reversed\n");
}

void display(void) {
    struct node *temp = head;
    if (temp == NULL) { printf("List is empty\n"); return; }
    printf("List: ");
    while (temp != NULL) {               /* terminates on NULL */
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main(void) {
    int ch, x, pos;
    while (1) {
        printf("\n1.InsertBegin 2.InsertEnd 3.InsertAtPos 4.Delete 5.Search"
               " 6.Reverse 7.Display 8.Exit\nChoice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: printf("Value: "); scanf("%d", &x); insertBegin(x); break;
            case 2: printf("Value: "); scanf("%d", &x); insertEnd(x); break;
            case 3: printf("Value: "); scanf("%d", &x);
                    printf("Position: "); scanf("%d", &pos);
                    insertAt(x, pos); break;
            case 4: printf("Value to delete: "); scanf("%d", &x);
                    deleteValue(x); break;
            case 5: printf("Value to search: "); scanf("%d", &x);
                    search(x); break;
            case 6: reverse(); break;
            case 7: display(); break;
            case 8: return 0;
            default: printf("Invalid choice\n");
        }
    }
}
