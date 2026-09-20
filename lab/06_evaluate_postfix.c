/* Syllabus 18(c) : EVALUATE A POSTFIX EXPRESSION  (uses a stack)

   ALGORITHM:
     Scan left to right.
       - Operand  -> push its value
       - Operator -> pop TWO values.  The FIRST popped is op2 (right operand),
                     the SECOND popped is op1 (left operand).
                     Compute op1 OP op2 and push the result.
     At the end the single value left on the stack is the answer.

   ORDER MATTERS for - and /  :  result = op1 - op2, NOT op2 - op1.

   Example: "231*+9-"  ->  2 + (3*1) - 9 = -4
   Input digits here are single characters 0-9.
*/
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#define MAX 100

int stack[MAX];
int top = -1;

void push(int x) { stack[++top] = x; }
int  pop(void)   { return stack[top--]; }

int evaluatePostfix(char exp[]) {
    int i, op1, op2, res;
    char c;
    for (i = 0; exp[i] != '\0'; i++) {
        c = exp[i];
        if (c == ' ') continue;

        if (isdigit(c)) {
            push(c - '0');                 /* char digit -> int */
        } else {
            op2 = pop();                   /* FIRST pop = right operand */
            op1 = pop();                   /* SECOND pop = left operand */
            switch (c) {
                case '+': res = op1 + op2; break;
                case '-': res = op1 - op2; break;
                case '*': res = op1 * op2; break;
                case '/':
                    if (op2 == 0) { printf("Error: division by zero\n"); return 0; }
                    res = op1 / op2; break;
                case '^': res = (int)pow(op1, op2); break;
                default : printf("Invalid operator %c\n", c); return 0;
            }
            push(res);
        }
    }
    return pop();
}

int main(void) {
    char exp[MAX];
    printf("Enter postfix expression (single digits, e.g. 231*+9-): ");
    scanf("%s", exp);
    printf("Result = %d\n", evaluatePostfix(exp));
    return 0;
}
/* compile with: gcc 06_evaluate_postfix.c -o e -lm   (-lm for pow) */
