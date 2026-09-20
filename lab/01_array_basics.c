/* Syllabus 16(a,b,c,d) + 17(a) + 17(b) : ARRAY PROGRAMS
   16a sum of even elements | 16b union | 16c intersection
   16d store N and reverse   | 17a maximum element | 17b dynamic array
   Compile: gcc 01_array_basics.c -o a && ./a
*/
#include <stdio.h>
#include <stdlib.h>

/* ---------- 16(a) sum of all EVEN elements ---------- */
int sumEven(int a[], int n) {
    int i, sum = 0;
    for (i = 0; i < n; i++)
        if (a[i] % 2 == 0)
            sum += a[i];
    return sum;
}

/* helper: is x present in a[0..n-1] ? */
int isPresent(int a[], int n, int x) {
    int i;
    for (i = 0; i < n; i++)
        if (a[i] == x) return 1;
    return 0;
}

/* ---------- 16(b) UNION of two arrays (no duplicates) ---------- */
int unionArr(int a[], int n, int b[], int m, int res[]) {
    int i, k = 0;
    for (i = 0; i < n; i++)
        if (!isPresent(res, k, a[i])) res[k++] = a[i];
    for (i = 0; i < m; i++)
        if (!isPresent(res, k, b[i])) res[k++] = b[i];
    return k;                      /* size of union */
}

/* ---------- 16(c) INTERSECTION of two arrays ---------- */
int intersectArr(int a[], int n, int b[], int m, int res[]) {
    int i, k = 0;
    for (i = 0; i < n; i++)
        if (isPresent(b, m, a[i]) && !isPresent(res, k, a[i]))
            res[k++] = a[i];
    return k;
}

/* ---------- 16(d) REVERSE the array (in place, two pointers) ---------- */
void reverseArr(int a[], int n) {
    int i = 0, j = n - 1, t;
    while (i < j) {
        t = a[i]; a[i] = a[j]; a[j] = t;
        i++; j--;
    }
}

/* ---------- 17(a) MAXIMUM element ---------- */
int findMax(int a[], int n) {
    int i, max = a[0];
    for (i = 1; i < n; i++)
        if (a[i] > max) max = a[i];
    return max;
}

void display(char *label, int a[], int n) {
    int i;
    printf("%s", label);
    for (i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

int main(void) {
    int n, m, i;
    int b[50], res[100];
    int *a;                        /* 17(b) DYNAMIC ARRAY */

    printf("Enter size of array A: ");
    scanf("%d", &n);

    /* ---- dynamic memory allocation ---- */
    a = (int *)malloc(n * sizeof(int));
    if (a == NULL) {               /* ALWAYS check malloc */
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Enter %d elements of A: ", n);
    for (i = 0; i < n; i++) scanf("%d", &a[i]);

    printf("Enter size of array B: ");
    scanf("%d", &m);
    printf("Enter %d elements of B: ", m);
    for (i = 0; i < m; i++) scanf("%d", &b[i]);

    printf("\nSum of even elements of A = %d\n", sumEven(a, n));
    printf("Maximum element of A       = %d\n", findMax(a, n));

    i = unionArr(a, n, b, m, res);
    display("Union        : ", res, i);

    i = intersectArr(a, n, b, m, res);
    if (i == 0) printf("Intersection : (empty)\n");
    else        display("Intersection : ", res, i);

    reverseArr(a, n);
    display("A reversed   : ", a, n);

    free(a);                       /* release the dynamic memory */
    a = NULL;                      /* avoid a dangling pointer   */
    return 0;
}
