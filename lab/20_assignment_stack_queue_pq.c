/* ASSIGNMENT No. 1 (TCS 301) -- Questions 10 to 16

   Q10 stack using linked list
   Q11 queue using linked list
   Q12 stack using array
   Q13 queue using array
   Q14 circular queue using array
   Q15 PRIORITY QUEUE using array
   Q16 PRIORITY QUEUE using linked list

   Q10-Q14 also appear in files 02, 03, 04 and 12 -- they are repeated here so
   the whole assignment sits in one place. Q15 and Q16 are new.
*/
#include <stdio.h>
#include <stdlib.h>
#define MAX 10

/* ============================================================
   Q12 : STACK USING ARRAY
   Empty: top == -1        Full: top == MAX-1        push/pop O(1)
   ============================================================ */
int stk[MAX];
int top = -1;

void push(int x) {
    if (top == MAX - 1) { printf("Stack Overflow\n"); return; }
    stk[++top] = x;
    printf("%d pushed\n", x);
}

int pop(void) {
    if (top == -1) { printf("Stack Underflow\n"); return -1; }
    return stk[top--];
}

void displayStack(void) {
    int i;
    if (top == -1) { printf("Stack is empty\n"); return; }
    printf("Stack (top -> bottom): ");
    for (i = top; i >= 0; i--) printf("%d ", stk[i]);
    printf("\n");
}

/* ============================================================
   Q13 : QUEUE USING ARRAY  (linear queue)
   Empty: front == -1 || front > rear      Full: rear == MAX-1
   ============================================================ */
int que[MAX];
int qfront = -1, qrear = -1;

void enqueue(int x) {
    if (qrear == MAX - 1) { printf("Queue Overflow\n"); return; }
    if (qfront == -1) qfront = 0;
    que[++qrear] = x;
    printf("%d enqueued\n", x);
}

int dequeue(void) {
    int x;
    if (qfront == -1 || qfront > qrear) { printf("Queue Underflow\n"); return -1; }
    x = que[qfront++];
    if (qfront > qrear) qfront = qrear = -1;   /* queue emptied -> reset */
    return x;
}

void displayQueue(void) {
    int i;
    if (qfront == -1 || qfront > qrear) { printf("Queue is empty\n"); return; }
    printf("Queue (front -> rear): ");
    for (i = qfront; i <= qrear; i++) printf("%d ", que[i]);
    printf("\n");
}

/* ============================================================
   Q14 : CIRCULAR QUEUE USING ARRAY
   rear = (rear+1) % MAX   fixes the FALSE OVERFLOW of a linear queue
   Empty: front == -1      Full: (rear+1) % MAX == front
   ============================================================ */
int cq[MAX];
int cfront = -1, crear = -1;

void cenqueue(int x) {
    if ((crear + 1) % MAX == cfront) { printf("Circular Queue Overflow\n"); return; }
    if (cfront == -1) cfront = 0;
    crear = (crear + 1) % MAX;          /* wrap around */
    cq[crear] = x;
    printf("%d enqueued\n", x);
}

int cdequeue(void) {
    int x;
    if (cfront == -1) { printf("Circular Queue Underflow\n"); return -1; }
    x = cq[cfront];
    if (cfront == crear) cfront = crear = -1;      /* last element removed */
    else cfront = (cfront + 1) % MAX;
    return x;
}

void cdisplayQueue(void) {
    int i;
    if (cfront == -1) { printf("Circular queue is empty\n"); return; }
    printf("Circular queue (front -> rear): ");
    i = cfront;
    while (1) {
        printf("%d ", cq[i]);
        if (i == crear) break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

/* ============================================================
   Q15 : PRIORITY QUEUE USING ARRAY

   A priority queue serves the HIGHEST PRIORITY element first, not the one
   that arrived first. Here a SMALLER priority number = HIGHER priority
   (priority 1 is served before priority 5), which is the usual convention.

   Method used: insert in SORTED order, so deletion is always from the front.
     insert : O(n)   (shift elements to make room at the right spot)
     delete : O(1)   (the front element is always the highest priority)

   The alternative is unsorted insert O(1) + search-for-max delete O(n).
   ============================================================ */
struct pqItem {
    int data;
    int priority;
};

struct pqItem pq[MAX];
int pqSize = 0;

void pqInsert(int data, int priority) {
    int i;

    if (pqSize == MAX) { printf("Priority Queue Overflow\n"); return; }

    /* shift every item with a WORSE (larger) priority one place right */
    i = pqSize - 1;
    while (i >= 0 && pq[i].priority > priority) {
        pq[i + 1] = pq[i];
        i--;
    }

    /* the gap at i+1 is now the correct slot */
    pq[i + 1].data = data;
    pq[i + 1].priority = priority;
    pqSize++;

    printf("Inserted data %d with priority %d\n", data, priority);
}

int pqDelete(void) {
    int data, i;

    if (pqSize == 0) { printf("Priority Queue Underflow\n"); return -1; }

    data = pq[0].data;                 /* front = highest priority */
    printf("Deleted data %d (priority %d)\n", data, pq[0].priority);

    for (i = 0; i < pqSize - 1; i++)   /* shift everything left */
        pq[i] = pq[i + 1];
    pqSize--;

    return data;
}

void pqDisplay(void) {
    int i;
    if (pqSize == 0) { printf("Priority queue is empty\n"); return; }
    printf("Priority queue (highest priority first):\n");
    for (i = 0; i < pqSize; i++)
        printf("   data = %d, priority = %d\n", pq[i].data, pq[i].priority);
}

/* ============================================================
   Q10 : STACK USING LINKED LIST
   push and pop BOTH at the head -> O(1), and no fixed size limit.
   ============================================================ */
struct node {
    int data;
    struct node *next;
};

struct node *stkTop = NULL;

void lpush(int value) {
    struct node *n = (struct node *)malloc(sizeof(struct node));
    if (n == NULL) { printf("Heap full - Stack Overflow\n"); return; }
    n->data = value;
    n->next = stkTop;        /* new node points to the old top */
    stkTop = n;              /* new node becomes the top       */
    printf("%d pushed\n", value);
}

int lpop(void) {
    struct node *temp;
    int value;
    if (stkTop == NULL) { printf("Stack Underflow\n"); return -1; }
    temp = stkTop;
    value = stkTop->data;
    stkTop = stkTop->next;   /* move the top down */
    free(temp);
    return value;
}

void ldisplayStack(void) {
    struct node *temp = stkTop;
    if (temp == NULL) { printf("Stack is empty\n"); return; }
    printf("Stack (top -> bottom): ");
    while (temp != NULL) { printf("%d ", temp->data); temp = temp->next; }
    printf("\n");
}

/* ============================================================
   Q11 : QUEUE USING LINKED LIST
   insert at rear, delete at front, both O(1) thanks to the rear pointer.
   ============================================================ */
struct node *lfront = NULL, *lrear = NULL;

void lenqueue(int value) {
    struct node *n = (struct node *)malloc(sizeof(struct node));
    if (n == NULL) { printf("Heap full - Queue Overflow\n"); return; }
    n->data = value;
    n->next = NULL;
    if (lrear == NULL) lfront = lrear = n;     /* queue was empty */
    else { lrear->next = n; lrear = n; }
    printf("%d enqueued\n", value);
}

int ldequeue(void) {
    struct node *temp;
    int value;
    if (lfront == NULL) { printf("Queue Underflow\n"); return -1; }
    temp = lfront;
    value = lfront->data;
    lfront = lfront->next;
    if (lfront == NULL) lrear = NULL;          /* queue became empty */
    free(temp);
    return value;
}

void ldisplayQueue(void) {
    struct node *temp = lfront;
    if (temp == NULL) { printf("Queue is empty\n"); return; }
    printf("Queue (front -> rear): ");
    while (temp != NULL) { printf("%d ", temp->data); temp = temp->next; }
    printf("\n");
}

/* ============================================================
   Q16 : PRIORITY QUEUE USING LINKED LIST

   The list is kept SORTED by priority, so the head is always the highest
   priority element.
     insert : O(n)   (find the correct position)
     delete : O(1)   (always remove the head)
   Advantage over the array version: no fixed size, and deletion needs no
   shifting at all -- just move the head pointer.
   ============================================================ */
struct pnode {
    int data;
    int priority;
    struct pnode *next;
};

struct pnode *pqHead = NULL;

void lpqInsert(int data, int priority) {
    struct pnode *n, *temp;

    n = (struct pnode *)malloc(sizeof(struct pnode));
    if (n == NULL) { printf("Memory allocation failed\n"); return; }
    n->data = data;
    n->priority = priority;
    n->next = NULL;

    /* CASE 1 : empty list, or the new node outranks the current head */
    if (pqHead == NULL || priority < pqHead->priority) {
        n->next = pqHead;
        pqHead = n;
        printf("Inserted data %d with priority %d\n", data, priority);
        return;
    }

    /* CASE 2 : walk until the NEXT node has a worse (larger) priority.
       Using > (not >=) keeps equal priorities in FIFO order. */
    temp = pqHead;
    while (temp->next != NULL && temp->next->priority <= priority)
        temp = temp->next;

    n->next = temp->next;
    temp->next = n;
    printf("Inserted data %d with priority %d\n", data, priority);
}

int lpqDelete(void) {
    struct pnode *temp;
    int data;

    if (pqHead == NULL) { printf("Priority Queue Underflow\n"); return -1; }

    temp = pqHead;
    data = temp->data;
    printf("Deleted data %d (priority %d)\n", data, temp->priority);

    pqHead = pqHead->next;      /* the head is always the highest priority */
    free(temp);
    return data;
}

void lpqDisplay(void) {
    struct pnode *temp = pqHead;
    if (temp == NULL) { printf("Priority queue is empty\n"); return; }
    printf("Priority queue (highest priority first):\n");
    while (temp != NULL) {
        printf("   data = %d, priority = %d\n", temp->data, temp->priority);
        temp = temp->next;
    }
}

/* ============================================================
                          DRIVER
   ============================================================ */
int main(void) {
    int ch, x, p;

    while (1) {
        printf("\n===== ASSIGNMENT Q10 - Q16 =====\n"
               "ARRAY       -> 1.Push 2.Pop 3.ShowStack\n"
               "            -> 4.Enqueue 5.Dequeue 6.ShowQueue\n"
               "            -> 7.C-Enqueue 8.C-Dequeue 9.ShowCircularQueue\n"
               "            -> 10.PQ Insert 11.PQ Delete 12.Show PQ\n"
               "LINKED LIST -> 13.Push 14.Pop 15.ShowStack\n"
               "            -> 16.Enqueue 17.Dequeue 18.ShowQueue\n"
               "            -> 19.PQ Insert 20.PQ Delete 21.Show PQ\n"
               "22.Exit\nChoice: ");
        scanf("%d", &ch);

        switch (ch) {
            /* Q12 stack using array */
            case 1: printf("Value: "); scanf("%d", &x); push(x); break;
            case 2: x = pop(); if (x != -1) printf("Popped: %d\n", x); break;
            case 3: displayStack(); break;

            /* Q13 queue using array */
            case 4: printf("Value: "); scanf("%d", &x); enqueue(x); break;
            case 5: x = dequeue(); if (x != -1) printf("Dequeued: %d\n", x); break;
            case 6: displayQueue(); break;

            /* Q14 circular queue using array */
            case 7: printf("Value: "); scanf("%d", &x); cenqueue(x); break;
            case 8: x = cdequeue(); if (x != -1) printf("Dequeued: %d\n", x); break;
            case 9: cdisplayQueue(); break;

            /* Q15 priority queue using array */
            case 10: printf("Data: "); scanf("%d", &x);
                     printf("Priority (smaller = higher): "); scanf("%d", &p);
                     pqInsert(x, p); break;
            case 11: pqDelete(); break;
            case 12: pqDisplay(); break;

            /* Q10 stack using linked list */
            case 13: printf("Value: "); scanf("%d", &x); lpush(x); break;
            case 14: x = lpop(); if (x != -1) printf("Popped: %d\n", x); break;
            case 15: ldisplayStack(); break;

            /* Q11 queue using linked list */
            case 16: printf("Value: "); scanf("%d", &x); lenqueue(x); break;
            case 17: x = ldequeue(); if (x != -1) printf("Dequeued: %d\n", x); break;
            case 18: ldisplayQueue(); break;

            /* Q16 priority queue using linked list */
            case 19: printf("Data: "); scanf("%d", &x);
                     printf("Priority (smaller = higher): "); scanf("%d", &p);
                     lpqInsert(x, p); break;
            case 20: lpqDelete(); break;
            case 21: lpqDisplay(); break;

            case 22: return 0;
            default: printf("Invalid choice\n");
        }
    }
}
