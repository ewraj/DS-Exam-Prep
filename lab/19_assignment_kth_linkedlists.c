/* ASSIGNMENT No. 1 (TCS 301) -- Questions 1 to 9
   Insert / delete a node at the Kth POSITION in every kind of linked list.

   Q1  create and display a singly linked list      (complete program)
   Q2  insert at kth position in SINGLY LL
   Q3  delete from kth position in SINGLY LL
   Q4  insert at kth position in CIRCULAR LL
   Q5  delete from kth position in CIRCULAR LL
   Q6  insert at kth position in DOUBLY LL
   Q7  delete from kth position in DOUBLY LL
   Q8  insert at kth position in DOUBLY CIRCULAR LL
   Q9  delete from kth position in DOUBLY CIRCULAR LL

   POSITIONS ARE 1-BASED:  k = 1 means the new node becomes the FIRST node.

   THE UNIVERSAL PATTERN for every "kth position" question:
     to INSERT at k -> stop at node number (k-1), link the new node after it
     to DELETE at k -> stop at node number (k-1), bypass the node after it
     k = 1 is ALWAYS the special case, because there is no node number 0.
*/
#include <stdio.h>
#include <stdlib.h>

/* ============================================================
   PART A : SINGLY LINKED LIST                     (Q1, Q2, Q3)
   ============================================================ */
struct node {
    int data;
    struct node *next;
};

struct node *head = NULL;

struct node* createNode(int value) {
    struct node *n = (struct node *)malloc(sizeof(struct node));
    if (n == NULL) { printf("Memory allocation failed\n"); exit(1); }
    n->data = value;
    n->next = NULL;
    return n;
}

/* ---------- Q1 : CREATE a singly linked list (insert at end) ---------- */
void create(int value) {
    struct node *n = createNode(value), *temp;
    if (head == NULL) { head = n; return; }
    temp = head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = n;
}

/* ---------- Q1 : DISPLAY the singly linked list ---------- */
void display(void) {
    struct node *temp = head;
    if (head == NULL) { printf("List is empty\n"); return; }
    printf("List: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

/* ---------- Q2 : INSERT a node at the Kth POSITION in a SINGLY LL ---------- */
void insertAtK(int value, int k) {
    struct node *n, *temp;
    int i;

    if (k < 1) { printf("Invalid position\n"); return; }

    /* CASE 1 : insert at the very beginning */
    if (k == 1) {
        n = createNode(value);
        n->next = head;
        head = n;
        printf("%d inserted at position 1\n", value);
        return;
    }

    /* CASE 2 : walk to node number (k-1) */
    temp = head;
    for (i = 1; i < k - 1 && temp != NULL; i++)
        temp = temp->next;

    if (temp == NULL) { printf("Position out of range\n"); return; }

    n = createNode(value);
    n->next = temp->next;      /* ORDER MATTERS: attach the tail side first */
    temp->next = n;            /* then attach the head side                 */
    printf("%d inserted at position %d\n", value, k);
}

/* ---------- Q3 : DELETE a node from the Kth POSITION in a SINGLY LL ---------- */
void deleteAtK(int k) {
    struct node *temp = head, *prev = NULL;
    int i;

    if (head == NULL) { printf("List is empty - Underflow\n"); return; }
    if (k < 1) { printf("Invalid position\n"); return; }

    /* CASE 1 : delete the first node */
    if (k == 1) {
        head = head->next;
        printf("Node %d deleted from position 1\n", temp->data);
        free(temp);
        return;
    }

    /* CASE 2 : walk to node number k, remembering the previous one */
    for (i = 1; i < k && temp != NULL; i++) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) { printf("Position out of range\n"); return; }

    prev->next = temp->next;        /* bypass the node */
    printf("Node %d deleted from position %d\n", temp->data, k);
    free(temp);
}

/* ============================================================
   PART B : CIRCULAR LINKED LIST                       (Q4, Q5)
   last->next = head, so traversal uses do..while, never while(p != NULL)
   ============================================================ */
struct node *chead = NULL;

int clength(void) {
    struct node *temp = chead;
    int count = 0;
    if (chead == NULL) return 0;
    do { count++; temp = temp->next; } while (temp != chead);
    return count;
}

void ccreate(int value) {
    struct node *n = createNode(value), *last;
    if (chead == NULL) { chead = n; n->next = n; return; }
    last = chead;
    while (last->next != chead) last = last->next;
    last->next = n;
    n->next = chead;
}

void cdisplay(void) {
    struct node *temp = chead;
    if (chead == NULL) { printf("Circular list is empty\n"); return; }
    printf("Circular list: ");
    do { printf("%d -> ", temp->data); temp = temp->next; } while (temp != chead);
    printf("(back to head %d)\n", chead->data);
}

/* ---------- Q4 : INSERT at the Kth POSITION in a CIRCULAR LL ---------- */
void cinsertAtK(int value, int k) {
    struct node *n, *temp, *last;
    int i, len = clength();

    if (k < 1 || k > len + 1) { printf("Invalid position\n"); return; }

    n = createNode(value);

    /* CASE 1 : the list is empty */
    if (chead == NULL) {
        chead = n;
        n->next = n;                 /* a ring of one node */
        printf("%d inserted at position 1\n", value);
        return;
    }

    /* CASE 2 : insert at position 1 -> the LAST node must point to the new head */
    if (k == 1) {
        last = chead;
        while (last->next != chead) last = last->next;
        n->next = chead;
        last->next = n;
        chead = n;                   /* new node becomes the head */
        printf("%d inserted at position 1\n", value);
        return;
    }

    /* CASE 3 : walk to node number (k-1) */
    temp = chead;
    for (i = 1; i < k - 1; i++)
        temp = temp->next;

    n->next = temp->next;
    temp->next = n;
    printf("%d inserted at position %d\n", value, k);
}

/* ---------- Q5 : DELETE from the Kth POSITION in a CIRCULAR LL ---------- */
void cdeleteAtK(int k) {
    struct node *temp = chead, *prev = NULL, *last;
    int i, len = clength();

    if (chead == NULL) { printf("Circular list is empty - Underflow\n"); return; }
    if (k < 1 || k > len) { printf("Invalid position\n"); return; }

    /* CASE 1 : only one node in the list */
    if (len == 1) {
        printf("Node %d deleted, list is now empty\n", chead->data);
        free(chead);
        chead = NULL;
        return;
    }

    /* CASE 2 : delete the head -> the LAST node must point to the new head */
    if (k == 1) {
        last = chead;
        while (last->next != chead) last = last->next;
        temp = chead;
        chead = chead->next;
        last->next = chead;
        printf("Node %d deleted from position 1\n", temp->data);
        free(temp);
        return;
    }

    /* CASE 3 : walk to node number k */
    for (i = 1; i < k; i++) {
        prev = temp;
        temp = temp->next;
    }

    prev->next = temp->next;
    printf("Node %d deleted from position %d\n", temp->data, k);
    free(temp);
}

/* ============================================================
   PART C : DOUBLY LINKED LIST                         (Q6, Q7)
   node = prev | data | next
   ============================================================ */
struct dnode {
    int data;
    struct dnode *prev, *next;
};

struct dnode *dhead = NULL;

struct dnode* createDNode(int value) {
    struct dnode *n = (struct dnode *)malloc(sizeof(struct dnode));
    if (n == NULL) { printf("Memory allocation failed\n"); exit(1); }
    n->data = value;
    n->prev = n->next = NULL;
    return n;
}

void dcreate(int value) {
    struct dnode *n = createDNode(value), *temp;
    if (dhead == NULL) { dhead = n; return; }
    temp = dhead;
    while (temp->next != NULL) temp = temp->next;
    temp->next = n;
    n->prev = temp;
}

void ddisplay(void) {
    struct dnode *temp = dhead;
    if (dhead == NULL) { printf("Doubly list is empty\n"); return; }
    printf("Doubly list: NULL <-> ");
    while (temp != NULL) { printf("%d <-> ", temp->data); temp = temp->next; }
    printf("NULL\n");
}

/* ---------- Q6 : INSERT at the Kth POSITION in a DOUBLY LL ----------
   Up to FOUR pointer fields need updating:
     n->prev, n->next, the left neighbour's next, the right neighbour's prev */
void dinsertAtK(int value, int k) {
    struct dnode *n, *temp;
    int i;

    if (k < 1) { printf("Invalid position\n"); return; }

    n = createDNode(value);

    /* CASE 1 : insert at the beginning */
    if (k == 1) {
        n->next = dhead;
        if (dhead != NULL) dhead->prev = n;
        dhead = n;
        printf("%d inserted at position 1\n", value);
        return;
    }

    /* CASE 2 : walk to node number (k-1) */
    temp = dhead;
    for (i = 1; i < k - 1 && temp != NULL; i++)
        temp = temp->next;

    if (temp == NULL) { printf("Position out of range\n"); free(n); return; }

    n->next = temp->next;
    n->prev = temp;
    if (temp->next != NULL) temp->next->prev = n;   /* only if a right neighbour exists */
    temp->next = n;
    printf("%d inserted at position %d\n", value, k);
}

/* ---------- Q7 : DELETE from the Kth POSITION in a DOUBLY LL ---------- */
void ddeleteAtK(int k) {
    struct dnode *temp = dhead;
    int i;

    if (dhead == NULL) { printf("Doubly list is empty - Underflow\n"); return; }
    if (k < 1) { printf("Invalid position\n"); return; }

    /* walk to node number k */
    for (i = 1; i < k && temp != NULL; i++)
        temp = temp->next;

    if (temp == NULL) { printf("Position out of range\n"); return; }

    /* fix the LEFT neighbour */
    if (temp->prev != NULL) temp->prev->next = temp->next;
    else                    dhead = temp->next;         /* deleting the head */

    /* fix the RIGHT neighbour */
    if (temp->next != NULL) temp->next->prev = temp->prev;

    printf("Node %d deleted from position %d\n", temp->data, k);
    free(temp);
}

/* ============================================================
   PART D : DOUBLY CIRCULAR LINKED LIST                (Q8, Q9)
   last->next = head  AND  head->prev = last
   There is no NULL anywhere in this list, so no NULL checks are needed --
   but every operation must keep BOTH rings intact.
   ============================================================ */
struct dnode *dchead = NULL;

int dclength(void) {
    struct dnode *temp = dchead;
    int count = 0;
    if (dchead == NULL) return 0;
    do { count++; temp = temp->next; } while (temp != dchead);
    return count;
}

void dccreate(int value) {
    struct dnode *n = createDNode(value), *last;
    if (dchead == NULL) {
        dchead = n;
        n->next = n->prev = n;      /* points to itself both ways */
        return;
    }
    last = dchead->prev;            /* head->prev IS the last node - O(1) */
    last->next = n;
    n->prev = last;
    n->next = dchead;
    dchead->prev = n;
}

void dcdisplay(void) {
    struct dnode *temp = dchead;
    if (dchead == NULL) { printf("Doubly circular list is empty\n"); return; }
    printf("Doubly circular: ");
    do { printf("%d <-> ", temp->data); temp = temp->next; } while (temp != dchead);
    printf("(back to head %d)\n", dchead->data);
}

/* ---------- Q8 : INSERT at the Kth POSITION in a DOUBLY CIRCULAR LL ---------- */
void dcinsertAtK(int value, int k) {
    struct dnode *n, *temp;
    int i, len = dclength();

    if (k < 1 || k > len + 1) { printf("Invalid position\n"); return; }

    n = createDNode(value);

    /* CASE 1 : empty list */
    if (dchead == NULL) {
        dchead = n;
        n->next = n->prev = n;
        printf("%d inserted at position 1\n", value);
        return;
    }

    /* CASE 2 : insert at position 1 */
    if (k == 1) {
        temp = dchead->prev;         /* the last node */
        n->next = dchead;
        n->prev = temp;
        temp->next = n;
        dchead->prev = n;
        dchead = n;                  /* new node becomes head */
        printf("%d inserted at position 1\n", value);
        return;
    }

    /* CASE 3 : walk to node number (k-1). This also covers inserting at the end. */
    temp = dchead;
    for (i = 1; i < k - 1; i++)
        temp = temp->next;

    n->next = temp->next;
    n->prev = temp;
    temp->next->prev = n;            /* never NULL in a circular list */
    temp->next = n;
    printf("%d inserted at position %d\n", value, k);
}

/* ---------- Q9 : DELETE from the Kth POSITION in a DOUBLY CIRCULAR LL ---------- */
void dcdeleteAtK(int k) {
    struct dnode *temp = dchead;
    int i, len = dclength();

    if (dchead == NULL) { printf("List is empty - Underflow\n"); return; }
    if (k < 1 || k > len) { printf("Invalid position\n"); return; }

    /* CASE 1 : only one node */
    if (len == 1) {
        printf("Node %d deleted, list is now empty\n", dchead->data);
        free(dchead);
        dchead = NULL;
        return;
    }

    /* walk to node number k */
    for (i = 1; i < k; i++)
        temp = temp->next;

    /* unlink -- both neighbours always exist, so no NULL checks needed */
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;

    if (temp == dchead) dchead = temp->next;    /* deleting the head */

    printf("Node %d deleted from position %d\n", temp->data, k);
    free(temp);
}

/* ============================================================
                    DRIVER PROGRAM  (Q1)
   ============================================================ */
int main(void) {
    int ch, n, i, value, k;

    printf("=== Q1: CREATE A SINGLY LINKED LIST ===\n");
    printf("How many nodes? ");
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        printf("Enter data for node %d: ", i);
        scanf("%d", &value);
        create(value);
        ccreate(value);        /* build the other three lists with the same */
        dcreate(value);        /* data so that every function below can be  */
        dccreate(value);       /* demonstrated from one menu                */
    }
    display();

    while (1) {
        printf("\n--- SINGLY   : 1.Insert@k  2.Delete@k  3.Display\n"
               "--- CIRCULAR : 4.Insert@k  5.Delete@k  6.Display\n"
               "--- DOUBLY   : 7.Insert@k  8.Delete@k  9.Display\n"
               "--- DOUBLY CIRCULAR: 10.Insert@k 11.Delete@k 12.Display\n"
               "13.Exit\nChoice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: printf("Value: "); scanf("%d", &value);
                    printf("Position k: "); scanf("%d", &k);
                    insertAtK(value, k); break;
            case 2: printf("Position k: "); scanf("%d", &k);
                    deleteAtK(k); break;
            case 3: display(); break;

            case 4: printf("Value: "); scanf("%d", &value);
                    printf("Position k: "); scanf("%d", &k);
                    cinsertAtK(value, k); break;
            case 5: printf("Position k: "); scanf("%d", &k);
                    cdeleteAtK(k); break;
            case 6: cdisplay(); break;

            case 7: printf("Value: "); scanf("%d", &value);
                    printf("Position k: "); scanf("%d", &k);
                    dinsertAtK(value, k); break;
            case 8: printf("Position k: "); scanf("%d", &k);
                    ddeleteAtK(k); break;
            case 9: ddisplay(); break;

            case 10: printf("Value: "); scanf("%d", &value);
                     printf("Position k: "); scanf("%d", &k);
                     dcinsertAtK(value, k); break;
            case 11: printf("Position k: "); scanf("%d", &k);
                     dcdeleteAtK(k); break;
            case 12: dcdisplay(); break;

            case 13: return 0;
            default: printf("Invalid choice\n");
        }
    }
}
