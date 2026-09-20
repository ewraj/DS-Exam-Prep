/* Syllabus 19(b) : Linked list with pointers LEFT and RIGHT.
   - New nodes are ALWAYS added after the RIGHT end (i.e. at the tail).
   - User enters a KEY, it is searched in the list.
   - If found  -> that node is DELETED and the list is updated.
   - If not found -> print "Unsuccessful Search".

   Each node has left and right pointers, so this is really a doubly linked
   list; we keep two globals `left` (head) and `right` (tail).
*/
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left, *right;
};

struct node *left = NULL;     /* head of the list */
struct node *right = NULL;    /* tail of the list */

struct node* createNode(int value) {
    struct node *n = (struct node *)malloc(sizeof(struct node));
    if (n == NULL) { printf("Memory allocation failed\n"); exit(1); }
    n->data = value;
    n->left = n->right = NULL;
    return n;
}

/* insert after the right end -> O(1) because we keep a tail pointer */
void insert(int value) {
    struct node *n = createNode(value);
    if (left == NULL) {                 /* list was empty */
        left = right = n;
    } else {
        right->right = n;               /* link old tail forward  */
        n->left = right;                /* link new node backward */
        right = n;                      /* new node becomes tail  */
    }
    printf("%d inserted\n", value);
}

/* search and delete the node holding key */
void searchAndDelete(int key) {
    struct node *temp = left;

    while (temp != NULL && temp->data != key)
        temp = temp->right;

    if (temp == NULL) {                 /* key not found */
        printf("Unsuccessful Search\n");
        return;
    }

    /* fix the LEFT neighbour's forward pointer */
    if (temp->left != NULL) temp->left->right = temp->right;
    else                    left = temp->right;      /* deleting the head */

    /* fix the RIGHT neighbour's backward pointer */
    if (temp->right != NULL) temp->right->left = temp->left;
    else                     right = temp->left;     /* deleting the tail */

    printf("Key %d found and deleted\n", key);
    free(temp);
}

void display(void) {
    struct node *temp = left;
    if (temp == NULL) { printf("List is empty\n"); return; }
    printf("List: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->right;
    }
    printf("\n");
}

int main(void) {
    int ch, x;
    while (1) {
        printf("\n1.Insert(at right) 2.Search & Delete key 3.Display 4.Exit\nChoice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: printf("Enter value: "); scanf("%d", &x); insert(x); break;
            case 2: printf("Enter key to search: "); scanf("%d", &x);
                    searchAndDelete(x); break;
            case 3: display(); break;
            case 4: return 0;
            default: printf("Invalid choice\n");
        }
    }
}
