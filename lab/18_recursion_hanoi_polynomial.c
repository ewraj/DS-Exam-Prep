/* UNIT 1 & 2 EXTRAS : RECURSION, TOWER OF HANOI, TAIL RECURSION,
                       POLYNOMIAL ADDITION (linked list), SPARSE MATRIX
   These are theory-heavy topics in your syllabus that often become a viva
   "can you write it?" question.
*/
#include <stdio.h>
#include <stdlib.h>

/* ---------- RECURSION: factorial (NOT tail recursive) ----------
   After the recursive call returns, we still have to multiply by n,
   so the stack frame must be kept alive. */
int factorial(int n) {
    if (n <= 1) return 1;          /* BASE CASE - without it: stack overflow */
    return n * factorial(n - 1);   /* work remains AFTER the call */
}

/* ---------- TAIL RECURSION: same thing, tail recursive ----------
   The recursive call is the LAST operation; nothing is pending afterwards,
   so the compiler can reuse the same stack frame (tail call optimisation)
   and turn it into a loop -> O(1) stack instead of O(n). */
int factorialTail(int n, int acc) {
    if (n <= 1) return acc;
    return factorialTail(n - 1, n * acc);   /* nothing left to do after this */
}

/* ---------- TOWER OF HANOI ----------
   Move n disks from `from` to `to` using `aux`.
   Total moves = 2^n - 1.     Recurrence: T(n) = 2T(n-1) + 1
   Rules: one disk at a time; never place a larger disk on a smaller one. */
void hanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        printf("Move disk 1 from %c to %c\n", from, to);
        return;
    }
    hanoi(n - 1, from, aux, to);                            /* 1 */
    printf("Move disk %d from %c to %c\n", n, from, to);    /* 2 */
    hanoi(n - 1, aux, to, from);                            /* 3 */
}

/* ---------- FIBONACCI (shows the cost of naive recursion) ---------- */
int fib(int n) {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);   /* O(2^n) - exponential, recomputes a lot */
}

/* ===================== POLYNOMIAL USING LINKED LIST =====================
   Each node = coefficient + exponent. Terms kept in DECREASING exponent order.
   e.g. 5x^2 + 4x + 2  ->  (5,2) -> (4,1) -> (2,0) -> NULL              */
struct poly {
    int coeff, expo;
    struct poly *next;
};

struct poly* appendTerm(struct poly *head, int c, int e) {
    struct poly *n = (struct poly *)malloc(sizeof(struct poly)), *t;
    n->coeff = c; n->expo = e; n->next = NULL;
    if (head == NULL) return n;
    t = head;
    while (t->next != NULL) t = t->next;
    t->next = n;
    return head;
}

/* ADD TWO POLYNOMIALS: walk both lists comparing exponents */
struct poly* addPoly(struct poly *p1, struct poly *p2) {
    struct poly *res = NULL;
    while (p1 != NULL && p2 != NULL) {
        if (p1->expo > p2->expo) {
            res = appendTerm(res, p1->coeff, p1->expo); p1 = p1->next;
        } else if (p1->expo < p2->expo) {
            res = appendTerm(res, p2->coeff, p2->expo); p2 = p2->next;
        } else {                                   /* equal exponents -> add */
            if (p1->coeff + p2->coeff != 0)
                res = appendTerm(res, p1->coeff + p2->coeff, p1->expo);
            p1 = p1->next; p2 = p2->next;
        }
    }
    while (p1 != NULL) { res = appendTerm(res, p1->coeff, p1->expo); p1 = p1->next; }
    while (p2 != NULL) { res = appendTerm(res, p2->coeff, p2->expo); p2 = p2->next; }
    return res;
}

void printPoly(struct poly *p) {
    if (p == NULL) { printf("0\n"); return; }
    while (p != NULL) {
        printf("%dx^%d", p->coeff, p->expo);
        if (p->next != NULL) printf(" + ");
        p = p->next;
    }
    printf("\n");
}

/* ===================== SPARSE MATRIX (3-tuple form) =====================
   A matrix where most elements are 0. Store only the non-zero ones as
   (row, column, value). Row 0 of the triplet holds rows, cols, and the
   number of non-zero elements.                                          */
void sparseMatrix(void) {
    int m, n, i, j, k = 0;
    int a[10][10], t[100][3];

    printf("\nEnter rows and columns: ");
    scanf("%d %d", &m, &n);
    printf("Enter the matrix:\n");
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &a[i][j]);

    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            if (a[i][j] != 0) {
                t[k][0] = i; t[k][1] = j; t[k][2] = a[i][j];
                k++;
            }

    printf("\n3-tuple representation:\nRow Col Val\n");
    printf("%3d %3d %3d   <- dimensions and non-zero count\n", m, n, k);
    for (i = 0; i < k; i++)
        printf("%3d %3d %3d\n", t[i][0], t[i][1], t[i][2]);

    printf("\nOriginal needs %d ints, sparse form needs %d ints\n",
           m * n, (k + 1) * 3);
}

int main(void) {
    int ch, n;
    struct poly *p1 = NULL, *p2 = NULL, *sum;

    while (1) {
        printf("\n1.Factorial 2.Tail-recursive factorial 3.Tower of Hanoi"
               "\n4.Fibonacci 5.Polynomial addition 6.Sparse matrix 7.Exit\nChoice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: printf("n: "); scanf("%d", &n);
                    printf("%d! = %d\n", n, factorial(n)); break;
            case 2: printf("n: "); scanf("%d", &n);
                    printf("%d! = %d\n", n, factorialTail(n, 1)); break;
            case 3: printf("Number of disks: "); scanf("%d", &n);
                    hanoi(n, 'A', 'C', 'B');
                    printf("Total moves = %d (2^%d - 1)\n", (1 << n) - 1, n); break;
            case 4: printf("n: "); scanf("%d", &n);
                    printf("fib(%d) = %d\n", n, fib(n)); break;
            case 5:
                    /* 5x^2 + 4x + 2 */
                    p1 = NULL;
                    p1 = appendTerm(p1, 5, 2);
                    p1 = appendTerm(p1, 4, 1);
                    p1 = appendTerm(p1, 2, 0);
                    /* 5x^1 + 5x^0 */
                    p2 = NULL;
                    p2 = appendTerm(p2, 5, 1);
                    p2 = appendTerm(p2, 5, 0);
                    printf("P1 = "); printPoly(p1);
                    printf("P2 = "); printPoly(p2);
                    sum = addPoly(p1, p2);
                    printf("Sum = "); printPoly(sum);
                    break;
            case 6: sparseMatrix(); break;
            case 7: return 0;
            default: printf("Invalid choice\n");
        }
    }
}
