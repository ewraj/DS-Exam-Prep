/* Syllabus 18(a) : IMPLEMENT QUEUE USING ARRAY  (linear queue)
   FIFO - insert at REAR, delete at FRONT.
   Empty: front == -1 || front > rear      Full: rear == MAX-1
   NOTE: this linear queue suffers FALSE OVERFLOW - see 04_circular_queue.c
*/ 
//done
#include <stdio.h>
#define MAX 5

int queue[MAX];
int front = -1, rear = -1;

int isEmpty(void) { return front == -1 || front > rear; }
int isFull (void) { return rear == MAX - 1; }

void enqueue(int x) {
    if (isFull()) { printf("Queue Overflow! Cannot insert %d\n", x); return; }
    if (front == -1) front = 0;      /* first insertion */
    queue[++rear] = x;
    printf("%d inserted\n", x);
}

int dequeue(void) {
    int x;
    if (isEmpty()) { printf("Queue Underflow!\n"); return -1; }
    x = queue[front++];
    if (front > rear) front = rear = -1;   /* queue became empty -> reset */
    return x;
}

void display(void) {
    int i;
    if (isEmpty()) { printf("Queue is empty\n"); return; }
    printf("Queue (front -> rear): ");
    for (i = front; i <= rear; i++) printf("%d ", queue[i]);
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
