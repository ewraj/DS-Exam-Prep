# More Viva Questions (forwarded set + assignment theory)

---

## 1. "Ek doubly linked list node ko create karne me kitne bytes use hote hain — 20?"

**Yes, 20 bytes on a typical 64-bit compiler.** But the correct viva answer is: *it depends on the machine*, and here is why.

A doubly linked list node is:
```c
struct dnode {
    int data;               /* 4 bytes  */
    struct dnode *prev;     /* 8 bytes on 64-bit */
    struct dnode *next;     /* 8 bytes on 64-bit */
};
```

**Size = sizeof(data) + 2 × sizeof(pointer)**, plus padding.

| Compiler / machine | int | pointer | Raw total | **sizeof(struct) with padding** |
|---|---|---|---|---|
| 64-bit (gcc on modern Windows/Linux) | 4 | 8 | 20 | **24** ← struct padding |
| 32-bit (gcc -m32, old Dev-C++) | 4 | 4 | **12** | 12 |
| 16-bit Turbo C | 2 | 2 | **6** | 6 |

**Important catch:** on 64-bit the *raw sum* is 20, but `sizeof(struct dnode)` actually returns **24**. The compiler inserts **4 bytes of padding** after `int data` so that the 8-byte pointers start at an address that is a multiple of 8 (**memory alignment**). If your teacher says 20, they mean the sum of the fields.

**So answer it like this:**
> "Data 4 bytes plus two pointers of 8 bytes each is 20 bytes of actual data. But because of structure padding for alignment, `sizeof` returns 24 on a 64-bit machine. On a 32-bit compiler it is 12 bytes, and on Turbo C it is 6."

**Related, expect these follow-ups:**
- **Singly LL node?** `int + 1 pointer` = 4+8 = **12 on 64-bit** (no padding needed), 8 on 32-bit, 4 on Turbo C.
- **Why does doubly need more memory?** The extra `prev` pointer in *every* node — that is the main disadvantage of a doubly linked list.
- **How do you find it in code?** `printf("%d", sizeof(struct dnode));`
- **What is structure padding?** Empty bytes the compiler inserts between members so each member sits at an address that is a multiple of its own size. It wastes a little space but makes memory access much faster, because a misaligned read costs extra CPU cycles.
- **Total memory for n nodes?** `n * sizeof(node)` — and note it is allocated as n *separate* heap blocks, not one contiguous block like an array.

---

## 2. "front > rear kiski condition hoti hai?"

**`front > rear` is the EMPTY condition (UNDERFLOW) of a linear queue implemented with an array.**

Full statement of the empty test:
```c
if (front == -1 || front > rear)     /* queue is EMPTY */
```

**Why does it happen?** In a linear queue, deletion moves `front` forward and insertion moves `rear` forward. When you delete the last remaining element, `front` steps past `rear` — so `front > rear` means every element inserted has already been deleted.

**Dry run with MAX = 5:**
```
start            front = -1, rear = -1        EMPTY
enqueue 10       front =  0, rear =  0
enqueue 20       front =  0, rear =  1
dequeue          front =  1, rear =  1
dequeue          front =  2, rear =  1   ->  front > rear  ->  EMPTY
```
Good practice is to reset `front = rear = -1` at that moment.

**The complete condition table — memorise this, they love it:**

| Condition | Linear queue | Circular queue | Stack |
|---|---|---|---|
| Initially | `front = rear = -1` | `front = rear = -1` | `top = -1` |
| Empty (underflow) | `front == -1 \|\| front > rear` | `front == -1` | `top == -1` |
| Full (overflow) | `rear == MAX-1` | `(rear+1) % MAX == front` | `top == MAX-1` |
| One element | `front == rear` | `front == rear` | `top == 0` |

**Guaranteed follow-up — "Is `rear == MAX-1` a real overflow?"**
No. In a linear queue it can be a **false / logical overflow** — `rear` has reached the end of the array but the slots before `front` are free and wasted. That is exactly the problem the **circular queue** solves by wrapping: `rear = (rear + 1) % MAX`.

---

## 3. "Linked list or array?" — which one, and when

They are asking you to *choose* and *justify*. Never say "linked list is better" flatly.

**Use an ARRAY when:**
- You know the size in advance, or it does not change much.
- You need **random access** by index — `a[i]` is O(1).
- You will do **binary search** or sorting.
- Memory is tight — no pointer overhead per element.
- You want speed in practice — contiguous memory means **cache locality**.

**Use a LINKED LIST when:**
- The size is **unknown or changes a lot** at run time.
- You do many **insertions and deletions**, especially at the beginning or middle — O(1) once you have the pointer, vs O(n) shifting in an array.
- You cannot guarantee one large **contiguous** block of free memory (a linked list can use scattered free blocks).
- You are building a stack, queue, graph adjacency list, or a hash table with chaining.

**One-line answer:**
> "Array for fast access and fixed size, linked list for fast insertion/deletion and dynamic size. Array trades flexibility for speed of access; linked list trades speed of access for flexibility."

(The full comparison table and the memory-fetching explanation are in `01-VIVA-ANSWERS.md`, sections 7 and 8.)

---

## 4. "Real life applications of linked list and array"

### Array — real life
1. **Contact list / phone book** stored in fixed slots, accessed by index.
2. **Image processing** — a digital image is a 2D array of pixel values.
3. **Matrices** in graphics and scientific computing.
4. **Leaderboards / marksheets** — fixed number of students, accessed by roll number.
5. **Lookup tables** — days of the week, month names, ASCII tables.
6. **Seat booking** in a cinema or aeroplane — fixed number of seats, seat number = index.
7. **CPU registers and memory itself** — RAM is essentially a giant array of bytes.
8. Implementing other data structures — stacks, queues, heaps, hash tables.

### Linked list — real life
1. **Music playlist** — next song / previous song (doubly linked list). A playlist on **repeat** is a circular linked list.
2. **Browser back and forward buttons** — doubly linked list of visited pages.
3. **Undo / redo** in MS Word, Photoshop.
4. **Image viewer** — next / previous image.
5. **Photo carousel or slideshow** on a website — circular linked list.
6. **Train coaches** — each coach linked to the next; adding or removing a coach in the middle does not disturb the others.
7. **Dynamic memory management** — the OS keeps a linked list of free memory blocks.
8. **Hash table collision handling** (separate chaining).
9. **Polynomial and big-number arithmetic**.
10. **Round-robin CPU scheduling** — circular linked list of processes.
11. Blockchain — each block stores a link to the previous block.

---

## 5. "And queue?" — real life applications of a queue

1. **Printer queue** — documents print in the order they were sent (spooling).
2. **Ticket counter / bank / billing line** — first come, first served.
3. **CPU scheduling and disk scheduling** in an operating system.
4. **Call centre** — calls are answered in the order received.
5. **Keyboard buffer** — keystrokes are processed in the order typed.
6. **Data transfer between two processes** of different speeds — a buffer/pipe, e.g. **video streaming buffering**, IO buffers.
7. **BFS** (Breadth First Search) in graphs and trees.
8. **Traffic at a toll booth / traffic light** system.
9. Handling **interrupts** in real-time systems.
10. Server request handling — incoming web requests wait in a queue.

**Circular queue:** round-robin CPU scheduling, traffic light control, memory management — anywhere you must reuse a fixed buffer forever.

**Priority queue:** hospital **emergency room triage** (most critical patient first, not first-arrived), Dijkstra's shortest path, Prim's MST, Huffman coding, OS scheduling by process priority, printer jobs where an urgent job jumps the line.

**Deque (double-ended queue):** undo history, browser history, sliding-window problems, a deck of cards where you draw from either end.

---

## 6. Priority Queue (needed for assignment Q15 and Q16)

**Definition:** A queue in which every element has a **priority**, and elements are served in order of priority rather than order of arrival. Among equal priorities, FIFO order is kept.

**Convention:** usually a **smaller number means higher priority** (priority 1 is served before priority 5). State whichever convention you use.

**Two ways to build it:**

| | Insert | Delete |
|---|---|---|
| Keep the list **sorted** (what our code does) | **O(n)** — find the right spot | **O(1)** — always take the front |
| Keep it **unsorted** | **O(1)** — just append | **O(n)** — search for the highest priority |
| Using a **binary heap** (the real-world way) | **O(log n)** | **O(log n)** |

**Array vs linked list implementation:** the array version needs shifting on every insert and delete and has a fixed size; the linked-list version needs no shifting (just pointer changes) and grows dynamically — but costs an extra pointer per node.

**Code:** `lab/20_assignment_stack_queue_pq.c`, questions 15 and 16.

---

## 7. Assignment "kth position" theory — expect this in the practical

**Q: Why is `k == 1` always handled separately?**
Because inserting or deleting at position 1 changes the **head pointer** itself. For every other position you only modify a `next` pointer inside an existing node, but at position 1 there is no node number 0 to modify, so the head must be reassigned.

**Q: Where do you stop the loop when inserting at position k?**
At node number **k-1**, the node *before* the target position, because a singly linked list can only be modified going forward.

**Q: Why does the order of the two lines matter?**
```c
n->next = temp->next;    /* FIRST: attach the new node to the rest of the list */
temp->next = n;          /* THEN:  attach the previous node to the new node    */
```
If you reverse these, `temp->next` is overwritten before you have saved it, and **the entire rest of the list is lost** (a memory leak with unreachable nodes).

**Q: What is different in a circular list?**
When you insert or delete at position 1, you must also find the **last node** and update `last->next`, because it points to the head. That makes it an O(n) operation in a singly circular list — unless you keep a pointer to the last node instead of the first.

**Q: What is different in a doubly circular list?**
`head->prev` **is** the last node, so you can reach the tail in **O(1)** without traversing. Also there is no NULL anywhere, so you never need NULL checks on neighbours — but every operation must fix **four** pointers to keep both rings intact.

**Q: Time complexity of insert/delete at the kth position?**
**O(n)** in all four list types, because you must traverse k-1 nodes to get there. Only the pointer manipulation at the end is O(1). The best case is k=1 (O(1)) and the worst case is k=n (O(n)).

**Q: What if k is larger than the length of the list?**
Print an error — "Position out of range". Always validate `k >= 1` and `k <= length + 1` for insertion, `k <= length` for deletion. Examiners check for this.
