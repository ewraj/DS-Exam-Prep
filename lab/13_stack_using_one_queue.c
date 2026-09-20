/* VIVA FAVOURITE : IMPLEMENT A STACK USING A **SINGLE** QUEUE

   TRICK: after enqueuing the new element, rotate the queue by re-enqueuing
   the previous (size-1) elements. That brings the newest element to the FRONT,
   so a normal FIFO dequeue behaves like a LIFO pop.

   push : O(n)      pop : O(1)      top : O(1)

   Dry run:  push 1 -> [1]
             push 2 -> enqueue: [1,2], rotate 1x -> [2,1]
             push 3 -> enqueue: [2,1,3], rotate 2x -> [3,2,1]
             pop    -> 3   (correct LIFO)
*/
#include <stdio.h>
#define MAX 100

/* --- a plain circular queue, our only primitive --- */
int q[MAX];
int front = 0, rear = -1, count = 0;

void enqueue(int x) {
    if (count == MAX) { printf("Queue full\n"); return; }
    rear = (rear + 1) % MAX;
    q[rear] = x;
    count++;
}

int dequeue(void) {
    int x;
    if (count == 0) { printf("Queue empty\n"); return -1; }
    x = q[front];
    front = (front + 1) % MAX;
    count--;
    return x;
}

int qFront(void) { return (count == 0) ? -1 : q[front]; }
int size(void)   { return count; }

/* ================= STACK OPERATIONS ================= */

void push(int x) {
    int n = size();                 /* how many were there BEFORE x */
    int i;
    enqueue(x);                     /* x is now at the back  */
    for (i = 0; i < n; i++)         /* rotate the old ones behind x */
        enqueue(dequeue());
    printf("%d pushed\n", x);
}

int pop(void) {
    if (size() == 0) { printf("Stack Underflow\n"); return -1; }
    return dequeue();               /* front holds the newest element */
}

int peek(void) {
    if (size() == 0) { printf("Stack is empty\n"); return -1; }
    return qFront();
}

void display(void) {
    int i, idx;
    if (size() == 0) { printf("Stack is empty\n"); return; }
    printf("Stack (top -> bottom): ");
    for (i = 0; i < count; i++) {
        idx = (front + i) % MAX;
        printf("%d ", q[idx]);
    }
    printf("\n");
}

int main(void) {
    int ch, x;
    printf("STACK implemented with a SINGLE QUEUE\n");
    while (1) {
        printf("\n1.Push 2.Pop 3.Peek 4.Display 5.Exit\nChoice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: printf("Value: "); scanf("%d", &x); push(x); break;
            case 2: x = pop(); if (x != -1) printf("Popped: %d\n", x); break;
            case 3: x = peek(); if (x != -1) printf("Top: %d\n", x); break;
            case 4: display(); break;
            case 5: return 0;
            default: printf("Invalid choice\n");
        }
    }
}
