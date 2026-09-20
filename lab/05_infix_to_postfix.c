/* Syllabus 18(b) : CONVERT INFIX EXPRESSION TO POSTFIX  (uses a stack)

   ALGORITHM (say this in viva):
   Scan the infix expression left to right:
     1. Operand            -> append directly to the output
     2. '('                -> push onto stack
     3. ')'                -> pop and output until '(' is found; discard the '('
     4. Operator           -> while stack top has HIGHER or EQUAL precedence,
                              pop and output; then push the current operator
                              (for the right-associative '^', pop only on STRICTLY higher)
     5. End                -> pop everything remaining and output

   Precedence: ^ (3) > * / (2) > + - (1) > ( (0)
   Example: A+B*C      -> ABC*+
            (A+B)*C    -> AB+C*
            A+B*C-D/E  -> ABC*+DE/-
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 100

char stack[MAX];
int top = -1;

void push(char c) { stack[++top] = c; }
char pop(void)    { return stack[top--]; }
char peek(void)   { return (top == -1) ? '\0' : stack[top]; }
int isEmpty(void) { return top == -1; }

int precedence(char c) {
    switch (c) {
        case '^': return 3;
        case '*':
        case '/':
        case '%': return 2;
        case '+':
        case '-': return 1;
        default : return 0;          /* '(' */
    }
}

void infixToPostfix(char infix[], char postfix[]) {
    int i, k = 0;
    char c;
    for (i = 0; infix[i] != '\0'; i++) {
        c = infix[i];
        if (c == ' ') continue;

        if (isalnum(c)) {                       /* 1. operand */
            postfix[k++] = c;
        }
        else if (c == '(') {                    /* 2. opening bracket */
            push(c);
        }
        else if (c == ')') {                    /* 3. closing bracket */
            while (!isEmpty() && peek() != '(')
                postfix[k++] = pop();
            pop();                              /* discard the '(' */
        }
        else {                                  /* 4. operator */
            if (c == '^') {                     /* right associative */
                while (!isEmpty() && precedence(peek()) > precedence(c))
                    postfix[k++] = pop();
            } else {                            /* left associative */
                while (!isEmpty() && precedence(peek()) >= precedence(c))
                    postfix[k++] = pop();
            }
            push(c);
        }
    }
    while (!isEmpty())                          /* 5. flush the stack */
        postfix[k++] = pop();
    postfix[k] = '\0';
}

int main(void) {
    char infix[MAX], postfix[MAX];
    printf("Enter infix expression (e.g. (A+B)*C-D/E): ");
    scanf("%s", infix);
    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);
    return 0;
}
