/* Syllabus 17(c) : IMPLEMENT STACK USING ARRAY
   LIFO - push and pop both happen at TOP.
   Empty: top == -1      Full: top == MAX-1
   push/pop/peek all O(1)
*/
#include <stdio.h>
#define MAX 5

int stack[MAX];
int top = -1;                    /* -1 means empty */

int isEmpty(void) { return top == -1; }
int isFull (void) { return top == MAX - 1; }

void push(int x) {
    if (isFull()) {              /* OVERFLOW */
        printf("Stack Overflow! Cannot push %d\n", x);
        return;
    }
    stack[++top] = x;            /* increment top, then store */
    printf("%d pushed\n", x);
}

int pop(void) {
    if (isEmpty()) {             /* UNDERFLOW */
        printf("Stack Underflow! Nothing to pop\n");
        return -1;
    }
    return stack[top--];         /* return top, then decrement */
}

int peek(void) {
    if (isEmpty()) { printf("Stack is empty\n"); return -1; }
    return stack[top];
}

void display(void) {
    int i;
    if (isEmpty()) { printf("Stack is empty\n"); return; }
    printf("Stack (top -> bottom): ");
    for (i = top; i >= 0; i--) printf("%d ", stack[i]);
    printf("\n");
}

int main(void) {
    int ch, x;
    while (1) {
        printf("\n1.Push 2.Pop 3.Peek 4.Display 5.Exit\nChoice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: printf("Enter value: "); scanf("%d", &x);
                    push(x); break;
            case 2: x = pop();
                    if (x != -1) printf("Popped: %d\n", x); break;
            case 3: x = peek();
                    if (x != -1) printf("Top: %d\n", x); break;
            case 4: display(); break;
            case 5: return 0;
            default: printf("Invalid choice\n");
        }
    }
}
