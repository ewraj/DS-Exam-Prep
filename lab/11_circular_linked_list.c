/* Syllabus 21 : CIRCULAR LINKED LIST - insert, delete, display

   KEY DIFFERENCE from a singly list:
     last->next = head   (instead of NULL)
   So you can NEVER traverse with  while (temp != NULL)  -- infinite loop.
   Always use:  do { ... temp = temp->next; } while (temp != head);
*/
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node *head = NULL;

struct node* createNode(int value) {
    struct node *n = (struct node *)malloc(sizeof(struct node));
    if (n == NULL) { printf("Memory allocation failed\n"); exit(1); }
    n->data = value;
    n->next = NULL;
    return n;
}

/* ---------- INSERT AT BEGINNING ---------- */
void insertBegin(int value) {
    struct node *n = createNode(value), *last;
    if (head == NULL) {
        head = n;
        n->next = n;             /* points to itself - a ring of one */
        printf("%d inserted\n", value);
        return;
    }
    last = head;
    while (last->next != head) last = last->next;   /* find last node */
    n->next = head;
    last->next = n;              /* last must now point to the NEW head */
    head = n;
    printf("%d inserted at beginning\n", value);
}

/* ---------- INSERT AT END ---------- */
void insertEnd(int value) {
    struct node *n = createNode(value), *last;
    if (head == NULL) {
        head = n; n->next = n;
        printf("%d inserted\n", value);
        return;
    }
    last = head;
    while (last->next != head) last = last->next;
    last->next = n;
    n->next = head;              /* close the circle */
    printf("%d inserted at end\n", value);
}

/* ---------- DELETE BY VALUE ---------- */
void deleteValue(int key) {
    struct node *temp = head, *prev = NULL, *last;

    if (head == NULL) { printf("List is empty\n"); return; }

    /* Case 1: only one node */
    if (head->next == head && head->data == key) {
        free(head);
        head = NULL;
        printf("%d deleted, list is now empty\n", key);
        return;
    }

    /* Case 2: deleting the head */
    if (head->data == key) {
        last = head;
        while (last->next != head) last = last->next;
        temp = head;
        head = head->next;
        last->next = head;       /* last points to the new head */
        free(temp);
        printf("%d deleted\n", key);
        return;
    }

    /* Case 3: somewhere in the middle / at the end */
    prev = head;
    temp = head->next;
    while (temp != head && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == head) { printf("Unsuccessful Search - %d not found\n", key); return; }

    prev->next = temp->next;
    free(temp);
    printf("%d deleted\n", key);
}

/* ---------- DISPLAY : note the do-while ---------- */
void display(void) {
    struct node *temp = head;
    if (head == NULL) { printf("List is empty\n"); return; }
    printf("Circular list: ");
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);      /* stop when we are back at the head */
    printf("(back to head %d)\n", head->data);
}

int main(void) {
    int ch, x;
    while (1) {
        printf("\n1.InsertBegin 2.InsertEnd 3.Delete 4.Display 5.Exit\nChoice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: printf("Value: "); scanf("%d", &x); insertBegin(x); break;
            case 2: printf("Value: "); scanf("%d", &x); insertEnd(x); break;
            case 3: printf("Value to delete: "); scanf("%d", &x);
                    deleteValue(x); break;
            case 4: display(); break;
            case 5: return 0;
            default: printf("Invalid choice\n");
        }
    }
}
