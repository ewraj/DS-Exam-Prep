/* CIRCULAR QUEUE using array  (Unit 2)
   Fixes the FALSE OVERFLOW of a linear queue by wrapping around with %.
   rear  = (rear + 1) % MAX
   front = (front + 1) % MAX
   Empty : front == -1
   Full  : (rear + 1) % MAX == front
*/
#include <stdio.h>
#define MAX 5

int cq[MAX];
int front = -1, rear = -1;

int isEmpty(void) { return front == -1; }
int isFull (void) { return (rear + 1) % MAX == front; }

void enqueue(int x) {
    if (isFull()) { printf("Circular Queue Overflow!\n"); return; }
    if (front == -1) front = 0;          /* first element */
    rear = (rear + 1) % MAX;             /* wrap around */
    cq[rear] = x;
    printf("%d inserted\n", x);
}

int dequeue(void) {
    int x;
    if (isEmpty()) { printf("Circular Queue Underflow!\n"); return -1; }
    x = cq[front];
    if (front == rear) front = rear = -1;        /* last element removed */
    else front = (front + 1) % MAX;
    return x;
}

void display(void) {
    int i;
    if (isEmpty()) { printf("Queue is empty\n"); return; }
    printf("Queue (front -> rear): ");
    i = front;
    while (1) {
        printf("%d ", cq[i]);
        if (i == rear) break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main(void) {
    int ch, x;
    while (1) {
        printf("\n1.Enqueue 2.Dequeue 3.Display 4.Exit\nChoice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: printf("Enter value: "); scanf("%d", &x);
                    enqueue(x); break;
            case 2: x = dequeue();
                    if (x != -1) printf("Deleted: %d\n", x); break;
            case 3: display(); break;
            case 4: return 0;
            default: printf("Invalid choice\n");
        }
    }
}
