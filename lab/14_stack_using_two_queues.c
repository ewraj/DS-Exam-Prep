/* VIVA FAVOURITE : IMPLEMENT A STACK USING TWO QUEUES
   Method used here: PUSH COSTLY  -> push O(n), pop O(1)

   push(x): enqueue x into q2
            move everything from q1 into q2
            swap q1 and q2   (q1 now holds elements in stack/LIFO order)
   pop():   dequeue from q1

   The alternative (POP COSTLY) is written at the bottom as a comment.
*/
#include <stdio.h>
#define MAX 100

typedef struct {
    int a[MAX];
    int front, rear, count;
} Queue;

void initQ(Queue *q) { q->front = 0; q->rear = -1; q->count = 0; }
int  isEmptyQ(Queue *q) { return q->count == 0; }

void enqueue(Queue *q, int x) {
    if (q->count == MAX) { printf("Queue full\n"); return; }
    q->rear = (q->rear + 1) % MAX;
    q->a[q->rear] = x;
    q->count++;
}

int dequeue(Queue *q) {
    int x;
    if (isEmptyQ(q)) return -1;
    x = q->a[q->front];
    q->front = (q->front + 1) % MAX;
    q->count--;
    return x;
}

int frontQ(Queue *q) { return isEmptyQ(q) ? -1 : q->a[q->front]; }

Queue q1, q2;

/* ---------- PUSH : O(n) ---------- */
void push(int x) {
    Queue temp;
    enqueue(&q2, x);                       /* 1. new element into q2 */
    while (!isEmptyQ(&q1))                 /* 2. old elements behind it */
        enqueue(&q2, dequeue(&q1));
    temp = q1; q1 = q2; q2 = temp;         /* 3. swap q1 and q2 */
    printf("%d pushed\n", x);
}

/* ---------- POP : O(1) ---------- */
int pop(void) {
    if (isEmptyQ(&q1)) { printf("Stack Underflow\n"); return -1; }
    return dequeue(&q1);
}

int peek(void) {
    if (isEmptyQ(&q1)) { printf("Stack is empty\n"); return -1; }
    return frontQ(&q1);
}

void display(void) {
    int i, idx;
    if (isEmptyQ(&q1)) { printf("Stack is empty\n"); return; }
    printf("Stack (top -> bottom): ");
    for (i = 0; i < q1.count; i++) {
        idx = (q1.front + i) % MAX;
        printf("%d ", q1.a[idx]);
    }
    printf("\n");
}

int main(void) {
    int ch, x;
    initQ(&q1); initQ(&q2);
    printf("STACK implemented with TWO QUEUES (push costly)\n");
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

/* ===== ALTERNATIVE: POP COSTLY (push O(1), pop O(n)) =====
   void push(int x) { enqueue(&q1, x); }

   int pop(void) {
       Queue temp; int x;
       if (isEmptyQ(&q1)) return -1;
       while (q1.count > 1)                  // move all but the last
           enqueue(&q2, dequeue(&q1));
       x = dequeue(&q1);                     // the last one is the top
       temp = q1; q1 = q2; q2 = temp;        // swap
       return x;
   }
*/
