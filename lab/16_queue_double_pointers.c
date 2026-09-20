/* Syllabus 22(b) : QUEUE USING DOUBLE POINTERS

   "Double pointer" = pointer to a pointer (struct node **).
   We pass &front and &rear into the functions so the functions can MODIFY the
   caller's actual pointers. Without a double pointer, C passes a COPY of the
   pointer and the caller's front/rear would never change.

   This is the standard viva point:
     void f(struct node *head)   -> changes to head are LOST
     void f(struct node **head)  -> changes to *head are VISIBLE to the caller
*/
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

/* note the ** : pointer to a pointer */
void enqueue(struct node **front, struct node **rear, int value) {
    struct node *n = (struct node *)malloc(sizeof(struct node));
    if (n == NULL) { printf("Memory allocation failed\n"); return; }
    n->data = value;
    n->next = NULL;

    if (*rear == NULL) {          /* queue is empty */
        *front = *rear = n;       /* dereference to change the CALLER's pointers */
    } else {
        (*rear)->next = n;
        *rear = n;
    }
    printf("%d enqueued\n", value);
}

int dequeue(struct node **front, struct node **rear) {
    struct node *temp;
    int value;

    if (*front == NULL) { printf("Queue Underflow\n"); return -1; }

    temp  = *front;
    value = temp->data;
    *front = (*front)->next;

    if (*front == NULL) *rear = NULL;   /* queue became empty */

    free(temp);
    return value;
}

void display(struct node *front) {
    if (front == NULL) { printf("Queue is empty\n"); return; }
    printf("Queue (front -> rear): ");
    while (front != NULL) { printf("%d ", front->data); front = front->next; }
    printf("\n");
}

int main(void) {
    struct node *front = NULL, *rear = NULL;
    int ch, x;
    while (1) {
        printf("\n1.Enqueue 2.Dequeue 3.Display 4.Exit\nChoice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: printf("Value: "); scanf("%d", &x);
                    enqueue(&front, &rear, x); break;       /* pass ADDRESSES */
            case 2: x = dequeue(&front, &rear);
                    if (x != -1) printf("Dequeued: %d\n", x); break;
            case 3: display(front); break;
            case 4: return 0;
            default: printf("Invalid choice\n");
        }
    }
}
