/* VIVA FAVOURITE : IMPLEMENT A QUEUE USING TWO STACKS
   Method used here: DEQUEUE COSTLY -> enqueue O(1), dequeue AMORTIZED O(1)

   s1 = "input stack",  s2 = "output stack"

   enqueue(x): push x onto s1                                 -> O(1)
   dequeue():  if s2 is empty, pour ALL of s1 into s2
                 (this reverses the order, so the oldest ends up on top)
               pop from s2

   Why amortized O(1)? Each element is moved from s1 to s2 AT MOST ONCE in its
   lifetime, so n operations cost O(n) in total -> O(1) average per operation.
   (Say the word "amortized" in the viva.)
*/
#include <stdio.h>
#define MAX 100

typedef struct {
    int a[MAX];
    int top;
} Stack;

void initS(Stack *s) { s->top = -1; }
int  isEmptyS(Stack *s) { return s->top == -1; }
int  isFullS (Stack *s) { return s->top == MAX - 1; }

void push(Stack *s, int x) {
    if (isFullS(s)) { printf("Stack full\n"); return; }
    s->a[++s->top] = x;
}

int pop(Stack *s) {
    if (isEmptyS(s)) return -1;
    return s->a[s->top--];
}

int peekS(Stack *s) { return isEmptyS(s) ? -1 : s->a[s->top]; }

Stack s1, s2;

/* ---------- ENQUEUE : O(1) ---------- */
void enqueue(int x) {
    push(&s1, x);
    printf("%d enqueued\n", x);
}

/* ---------- DEQUEUE : amortized O(1) ---------- */
int dequeue(void) {
    if (isEmptyS(&s1) && isEmptyS(&s2)) {
        printf("Queue Underflow\n");
        return -1;
    }
    if (isEmptyS(&s2)) {                  /* only refill when s2 is empty! */
        while (!isEmptyS(&s1))
            push(&s2, pop(&s1));          /* pouring reverses the order */
    }
    return pop(&s2);
}

int frontElement(void) {
    if (isEmptyS(&s1) && isEmptyS(&s2)) { printf("Queue is empty\n"); return -1; }
    if (isEmptyS(&s2))
        while (!isEmptyS(&s1)) push(&s2, pop(&s1));
    return peekS(&s2);
}

void display(void) {
    int i;
    if (isEmptyS(&s1) && isEmptyS(&s2)) { printf("Queue is empty\n"); return; }
    printf("Queue (front -> rear): ");
    for (i = s2.top; i >= 0; i--) printf("%d ", s2.a[i]);   /* s2 top = front */
    for (i = 0; i <= s1.top; i++) printf("%d ", s1.a[i]);   /* s1 bottom next */
    printf("\n");
}

int main(void) {
    int ch, x;
    initS(&s1); initS(&s2);
    printf("QUEUE implemented with TWO STACKS (dequeue costly)\n");
    while (1) {
        printf("\n1.Enqueue 2.Dequeue 3.Front 4.Display 5.Exit\nChoice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: printf("Value: "); scanf("%d", &x); enqueue(x); break;
            case 2: x = dequeue(); if (x != -1) printf("Dequeued: %d\n", x); break;
            case 3: x = frontElement(); if (x != -1) printf("Front: %d\n", x); break;
            case 4: display(); break;
            case 5: return 0;
            default: printf("Invalid choice\n");
        }
    }
}

/* ===== ALTERNATIVE: ENQUEUE COSTLY (enqueue O(n), dequeue O(1)) =====
   void enqueue(int x) {
       while (!isEmptyS(&s1)) push(&s2, pop(&s1));   // empty s1 into s2
       push(&s1, x);                                 // put x at the bottom
       while (!isEmptyS(&s2)) push(&s1, pop(&s2));   // pour back
   }
   int dequeue(void) { return pop(&s1); }            // oldest is on top
*/
