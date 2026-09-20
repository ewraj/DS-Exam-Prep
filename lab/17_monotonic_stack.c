/* VIVA FAVOURITE : MONOTONIC STACK

   A monotonic stack keeps its elements in sorted order (increasing or
   decreasing from bottom to top). Before pushing, we pop everything that
   would break that order.

   Every element is pushed once and popped at most once -> TOTAL O(n).

   Included here:
     1. Next Greater Element   (monotonic DECREASING stack)
     2. Next Smaller Element   (monotonic INCREASING stack)
     3. Stock Span problem     (classic application)
*/
#include <stdio.h>
#define MAX 100

int stack[MAX];
int top = -1;

void push(int x)  { stack[++top] = x; }
int  pop(void)    { return stack[top--]; }
int  peek(void)   { return stack[top]; }
int  isEmpty(void){ return top == -1; }

/* ---------- 1. NEXT GREATER ELEMENT (to the right) ----------
   We keep a stack that is DECREASING from bottom to top.
   Traverse from RIGHT to LEFT.
   Logic: pop everything <= current, because the current element is both
   BIGGER and CLOSER, so those popped ones can never be anybody's answer.
*/
void nextGreaterElement(int a[], int n, int res[]) {
    int i;
    top = -1;                                 /* reset the stack */
    for (i = n - 1; i >= 0; i--) {
        while (!isEmpty() && peek() <= a[i])  /* maintain the invariant */
            pop();
        res[i] = isEmpty() ? -1 : peek();     /* whatever survives is the answer */
        push(a[i]);
    }
}

/* ---------- 2. NEXT SMALLER ELEMENT (to the right) ----------
   Same idea, flipped comparison -> stack is INCREASING bottom to top.
*/
void nextSmallerElement(int a[], int n, int res[]) {
    int i;
    top = -1;
    for (i = n - 1; i >= 0; i--) {
        while (!isEmpty() && peek() >= a[i])
            pop();
        res[i] = isEmpty() ? -1 : peek();
        push(a[i]);
    }
}

/* ---------- 3. STOCK SPAN ----------
   span[i] = number of consecutive days up to and including day i on which
   the price was <= price[i].
   Here the stack stores INDICES, and we traverse LEFT to RIGHT.
*/
void stockSpan(int price[], int n, int span[]) {
    int i;
    top = -1;
    for (i = 0; i < n; i++) {
        while (!isEmpty() && price[peek()] <= price[i])
            pop();
        span[i] = isEmpty() ? (i + 1) : (i - peek());
        push(i);                              /* push the INDEX */
    }
}

void display(char *label, int a[], int n) {
    int i;
    printf("%-22s", label);
    for (i = 0; i < n; i++) printf("%4d", a[i]);
    printf("\n");
}

int main(void) {
    int a[MAX], res[MAX], n, i;

    printf("Enter number of elements: ");
    scanf("%d", &n);
    printf("Enter %d elements: ", n);
    for (i = 0; i < n; i++) scanf("%d", &a[i]);

    printf("\n");
    display("Array               :", a, n);

    nextGreaterElement(a, n, res);
    display("Next Greater Element:", res, n);

    nextSmallerElement(a, n, res);
    display("Next Smaller Element:", res, n);

    stockSpan(a, n, res);
    display("Stock Span          :", res, n);

    printf("\n(-1 means no such element exists)\n");
    return 0;
}

/* Sample:  n = 6,  array = 4 5 2 25 7 8
   Next Greater :  5  25  25  -1   8  -1
   Next Smaller :  2   2  -1   7  -1  -1
   Stock Span   :  1   2   1   4   1   2
*/
