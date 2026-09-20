# Night-Before Cheatsheet — read this last

## The 8 sentences that answer half the viva

1. **Stack** = LIFO, insert and delete at the same end called top. `top = -1` when empty.
2. **Queue** = FIFO, insert at rear, delete at front.
3. **Array** = contiguous memory, address is *calculated* → O(1) access. **Linked list** = scattered memory, address is *followed* → O(n) access.
4. `Address(A[i]) = Base + i * element_size`
5. **Circular linked list** = last node points to head instead of NULL → traverse with `do..while(p != head)`.
6. **Doubly linked list** = extra `prev` pointer → both directions, O(1) delete, but more memory and more pointers to update.
7. **Postfix** needs no parentheses and no precedence, so a machine evaluates it in one pass with one stack.
8. **Circular queue** exists because a linear queue reports **false overflow** — `rear = (rear+1) % MAX` reuses the freed front slots.

## Complexity table (memorise)

| Operation | Array | Singly LL | Doubly LL | Stack | Queue |
|---|---|---|---|---|---|
| Access i-th | **O(1)** | O(n) | O(n) | — | — |
| Search | O(n) | O(n) | O(n) | O(n) | O(n) |
| Insert at beginning | O(n) | **O(1)** | **O(1)** | — | — |
| Insert at end | O(1) | O(n)* | O(n)* | — | — |
| Delete at beginning | O(n) | **O(1)** | **O(1)** | — | — |
| Delete a known node | O(n) | O(n) | **O(1)** | — | — |
| push / pop | — | — | — | **O(1)** | — |
| enqueue / dequeue | — | — | — | — | **O(1)** |

\* O(1) if a tail pointer is maintained.

**Conversions:** stack from 1 queue → push O(n), pop O(1). Stack from 2 queues → one side is O(n), pick which. Queue from 2 stacks → enqueue O(1), dequeue **amortized O(1)**.

## Conditions to never mix up

```
Stack full     : top == MAX-1          Stack empty    : top == -1
Linear queue   : rear == MAX-1         empty: front == -1 || front > rear
Circular queue : (rear+1)%MAX == front empty: front == -1
```

## Pointer snippets they ask you to write on paper

```c
/* node definition (self-referential structure) */
struct node { int data; struct node *next; };

/* insert at beginning */
n->next = head;  head = n;

/* insert after temp   -- ORDER MATTERS */
n->next = temp->next;  temp->next = n;

/* delete the node after prev */
prev->next = temp->next;  free(temp);

/* reverse a linked list (3 pointers) */
while (curr) { next = curr->next; curr->next = prev; prev = curr; curr = next; }
head = prev;

/* circular list traversal -- never use while(p != NULL) */
do { printf("%d", p->data); p = p->next; } while (p != head);
```

## Traps they set

- Traversing a circular list with `while (p != NULL)` → **infinite loop**.
- `#define SQUARE(x) x*x` → `SQUARE(2+3)` gives **11**, not 25. Bracket everything.
- Preprocessor directives take **no semicolon**.
- Forgetting to check `malloc` returned NULL.
- Forgetting `free()` → **memory leak**; using a pointer after `free()` → **dangling pointer**.
- In postfix evaluation, the **first** popped value is the **right** operand.
- Deleting the head / the only node / the tail in a linked list — always three special cases.
- `struct node next;` instead of `struct node *next;` → the structure size would be infinite.

## If you blank out

Say the definition, then draw the diagram on paper. Boxes with arrows for a linked list, a vertical stack with `top` labelled, a horizontal queue with `front` and `rear`. Examiners give marks for the diagram, and drawing it usually restarts your memory.
