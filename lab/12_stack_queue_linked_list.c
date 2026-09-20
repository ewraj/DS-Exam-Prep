/* Syllabus 22(a) STACK USING LINKED LIST + 22(c) QUEUE USING LINKED LIST

   STACK with a linked list: push and pop BOTH at the HEAD -> O(1), no overflow.
   QUEUE with a linked list: insert at REAR, delete at FRONT -> both O(1)
                              (we keep a rear pointer so enqueue is O(1)).
*/
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

/* ==================== STACK ==================== */
struct node *top = NULL;

void push(int value) {
    struct node *n = (struct node *)malloc(sizeof(struct node));
    if (n == NULL) { printf("Heap full - Stack Overflow\n"); return; }
    n->data = value;
    n->next = top;        /* new node points to old top */
    top = n;              /* new node becomes top       */
    printf("%d pushed\n", value);
}

int pop(void) {
    struct node *temp;
    int value;
    if (top == NULL) { printf("Stack Underflow\n"); return -1; }
    temp = top;
    value = top->data;
    top = top->next;      /* move top down */
    free(temp);
    return value;
}

void displayStack(void) {
    struct node *temp = top;
    if (temp == NULL) { printf("Stack is empty\n"); return; }
    printf("Stack (top -> bottom): ");
    while (temp != NULL) { printf("%d ", temp->data); temp = temp->next; }
    printf("\n");
}

/* ==================== QUEUE ==================== */
struct node *front = NULL, *rear = NULL;

void enqueue(int value) {
    struct node *n = (struct node *)malloc(sizeof(struct node));
    if (n == NULL) { printf("Heap full - Queue Overflow\n"); return; }
    n->data = value;
    n->next = NULL;
    if (rear == NULL) {          /* queue was empty */
        front = rear = n;
    } else {
        rear->next = n;          /* link behind the old rear */
        rear = n;
    }
    printf("%d enqueued\n", value);
}

int dequeue(void) {
    struct node *temp;
    int value;
    if (front == NULL) { printf("Queue Underflow\n"); return -1; }
    temp = front;
    value = front->data;
    front = front->next;
    if (front == NULL) rear = NULL;   /* queue became empty - reset rear */
    free(temp);
    return value;
}

void displayQueue(void) {
    struct node *temp = front;
    if (temp == NULL) { printf("Queue is empty\n"); return; }
    printf("Queue (front -> rear): ");
    while (temp != NULL) { printf("%d ", temp->data); temp = temp->next; }
    printf("\n");
}

int main(void) {
    int ch, x;
    while (1) {
        printf("\n--- STACK: 1.Push 2.Pop 3.Show ---"
               "\n--- QUEUE: 4.Enqueue 5.Dequeue 6.Show ---\n7.Exit\nChoice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: printf("Value: "); scanf("%d", &x); push(x); break;
            case 2: x = pop(); if (x != -1) printf("Popped: %d\n", x); break;
            case 3: displayStack(); break;
            case 4: printf("Value: "); scanf("%d", &x); enqueue(x); break;
            case 5: x = dequeue(); if (x != -1) printf("Dequeued: %d\n", x); break;
            case 6: displayQueue(); break;
            case 7: return 0;
            default: printf("Invalid choice\n");
        }
    }
}
