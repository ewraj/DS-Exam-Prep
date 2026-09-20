# VIVA — Exact Answers (say these out loud)

Answer format that scores: **one-line definition → how it works → one application.** Stop there. Let them ask more.

---

## 1. Monotonic Stack

**Definition:** A stack whose elements are kept in sorted order (either always increasing or always decreasing from bottom to top). Before pushing a new element, we pop everything that would violate that order.

**Why it exists:** It answers "next greater / next smaller element" type questions in **O(n)** instead of O(n²), because every element is pushed once and popped once.

**Two kinds:**
- *Monotonic increasing stack* (bottom → top increasing): pop while `top > new` → used to find **next smaller element**.
- *Monotonic decreasing stack* (bottom → top decreasing): pop while `top < new` → used to find **next greater element**.

**Working (Next Greater Element), say it like this:**
> Traverse the array from right to left. Pop from the stack while the top is smaller than or equal to the current element — those can never be an answer for anyone to my left, because I am bigger and closer. Whatever remains on top is the next greater element. Then push the current element.

**Complexity:** Time O(n), Space O(n).

**Applications:** Next greater/smaller element, Stock Span problem, Largest Rectangle in Histogram, Trapping Rain Water, daily temperatures.

**Code:** `lab/17_monotonic_stack.c`

---

## 2. Preprocessor Directive

**Definition:** A command that begins with `#` and is executed by the **preprocessor before compilation** — it does pure text substitution on the source file. It is not a C statement, so it has **no semicolon**.

**The four categories:**

| Type | Directives | Purpose |
|---|---|---|
| Macro | `#define`, `#undef` | text substitution |
| File inclusion | `#include` | paste a file's contents in |
| Conditional compilation | `#ifdef`, `#ifndef`, `#if`, `#else`, `#elif`, `#endif` | compile code selectively |
| Other | `#pragma`, `#error`, `#line` | compiler-specific instructions |

**Compilation stages (they love this follow-up):**
`Preprocessor → Compiler → Assembler → Linker → Loader`
Source `.c` → expanded `.i` → assembly `.s` → object `.o` → executable.

**`#include <stdio.h>` vs `#include "myfile.h"`:**
- `< >` → searches the **standard/system include directories**.
- `" "` → searches the **current directory first**, then the system directories. Used for your own header files.

---

## 3. Define Macro

**Definition:** A macro is a name defined with `#define` that the preprocessor replaces with its body everywhere it appears, before compilation.

**Two types:**

```c
/* 1. Object-like macro (symbolic constant) */
#define PI 3.14159
#define MAX 100

/* 2. Function-like macro (with arguments) */
#define SQUARE(x)  ((x)*(x))
#define MAX2(a,b)  ((a)>(b)?(a):(b))
```

**Why the extra brackets?** Because it is *text substitution*, not a function call.
`#define SQUARE(x) x*x` then `SQUARE(2+3)` expands to `2+3*2+3` = **11**, not 25.
With `((x)*(x))` it expands to `((2+3)*(2+3))` = **25**. Always wrap each parameter and the whole body in parentheses.

**Macro vs Function (guaranteed follow-up):**

| Macro | Function |
|---|---|
| Handled by preprocessor | Handled by compiler |
| Code is substituted inline → faster, no call overhead | Actual call, stack frame pushed |
| No type checking | Strict type checking |
| Increases program size (code duplicated) | Compact code |
| No return type, cannot be debugged easily | Has return type, debuggable |
| Arguments may be evaluated twice — side effects break it (`SQUARE(i++)`) | Argument evaluated once |

**Bonus terms:** `#undef PI` removes a macro. `#ifndef HEADER_H / #define HEADER_H / ... / #endif` is an **include guard**, which prevents a header being included twice.

---

## 4. Stack using a SINGLE queue  ⭐ (they asked this)

**Yes, it is possible.** The trick is to make the push operation reverse the queue.

**Idea:** After enqueuing the new element, rotate the queue: dequeue and re-enqueue the *previous* `size-1` elements, so the newest element comes to the front.

```
push(x):
    n = size of queue
    enqueue(x)
    repeat n times:
        enqueue( dequeue() )      // rotate old elements behind x

pop():   return dequeue()          // front is the newest = LIFO
top():   return front()
```

**Dry run:** push 1 → [1]. push 2: enqueue → [1,2], rotate 1 time → [2,1]. push 3: enqueue → [2,1,3], rotate 2 times → [3,2,1]. pop() → 3. Correct LIFO.

**Complexity:** push **O(n)**, pop **O(1)**. (Push-costly method.)

**Code:** `lab/13_stack_using_one_queue.c`

---

## 5. Stack using TWO queues

Two variants — know both and say which one you are doing.

**(a) Push costly — pop O(1)**
```
push(x): enqueue x into q2
         move all of q1 into q2
         swap names of q1 and q2      // q1 now holds stack order
pop():   dequeue from q1
```
push O(n), pop O(1).

**(b) Pop costly — push O(1)**
```
push(x): enqueue x into q1                     // O(1)
pop():   move (size-1) elements from q1 to q2
         dequeue the last one from q1 = answer
         swap q1 and q2
```
push O(1), pop O(n).

**Key sentence for viva:** "A queue is FIFO and a stack is LIFO, so one of the two operations must pay O(n) to reverse the order. You cannot get both in O(1)."

**Code:** `lab/14_stack_using_two_queues.c`

---

## 6. Queue using TWO stacks

**(a) Enqueue costly — dequeue O(1)**
```
enqueue(x): move all of s1 into s2
            push x onto s1
            move all of s2 back into s1     // oldest ends on top
dequeue():  pop from s1
```
enqueue O(n), dequeue O(1).

**(b) Dequeue costly — enqueue O(1)  ← preferred, say this one**
```
enqueue(x): push x onto s1                  // O(1)
dequeue():  if s2 is empty:
                pop everything from s1 and push into s2  (reverses order)
            pop from s2
```
enqueue O(1), dequeue **amortized O(1)** — each element is moved from s1 to s2 at most once over its lifetime, so n operations cost O(n) total.

**Say "amortized O(1)"** — that word alone usually ends the question.

**Code:** `lab/15_queue_using_two_stacks.c`

---

## 7. Linked List vs Array ⭐

| | Array | Linked List |
|---|---|---|
| Memory | **Contiguous** block | **Scattered / non-contiguous**, joined by pointers |
| Allocation | Static (compile time) or dynamic via malloc, but fixed size once made | Fully dynamic, grows/shrinks at run time |
| Size | Fixed — must know in advance | No fixed size |
| Access | **Random access O(1)** via index | **Sequential only O(n)** — must traverse from head |
| Insert/delete at beginning | O(n) — shift all elements | **O(1)** — just change pointers |
| Insert/delete at end | O(1) (if space) | O(n) singly (O(1) if tail pointer kept) |
| Memory per element | Only the data | Data **+ pointer** → extra overhead |
| Memory waste | Unused slots wasted; or overflow if too small | No waste, allocates exactly what is used |
| Cache performance | **Excellent** (locality of reference) | Poor — nodes scattered in heap |
| Binary search | Possible | Not practical |

**One-line answer:** "Array gives fast access but costly insertion and fixed size; linked list gives fast insertion/deletion and dynamic size but only sequential access and extra pointer memory."

---

## 8. Memory fetching — how in array vs linked list ⭐ (this is the one that separates people)

**Array:**
- One single **contiguous** block of memory.
- Address of element *i* is computed by a formula, not searched:
  `Address(A[i]) = Base_Address + i * size_of_element`
  (for a 0-based array; for lower bound LB: `Base + (i - LB) * w`)
- One arithmetic operation → **O(1) random access**.
- Because neighbours are physically adjacent, when the CPU fetches `A[0]` the whole **cache line** (typically 64 bytes) is pulled into cache, so `A[1], A[2]...` are already there. This is **spatial locality of reference** → very few cache misses → fast in practice.

**Linked list:**
- Nodes are allocated **individually on the heap** by `malloc`, so they can be anywhere in memory, in any order.
- There is no formula. To reach the i-th node you must start at `head` and follow `i` pointer dereferences → **O(n) sequential access**.
- Every hop is a **pointer dereference to an unpredictable address** → likely a **cache miss** each time, and the CPU cannot prefetch. So even when both are O(n) for traversal, an array traversal is measurably faster.
- Extra memory: each node stores a pointer (4 or 8 bytes) beyond the data.

**The killer line:** "In an array the address is *calculated*; in a linked list the address is *followed*."

**2D array address calculation** (likely follow-up, for `A[i][j]`, base B, element size w, m rows × n cols):
- **Row-major** (C uses this): `B + ((i - LB1) * n + (j - LB2)) * w`
- **Column-major**: `B + ((j - LB2) * m + (i - LB1)) * w`

---

## 9. Singly vs Doubly Linked List

**Singly LL:** each node has `data` + `next`. Traversal in one direction only.
**Doubly LL:** each node has `prev` + `data` + `next`. Traversal in both directions.

**Advantages of Doubly over Singly:**
1. Can be traversed in **both directions** (forward and backward).
2. **Deletion is easier** — given a pointer to the node, you can delete it in O(1); in a singly list you need the previous node, so you must traverse from the head.
3. Insertion **before** a given node is O(1).
4. Operations like reverse traversal / implementing a deque are natural.

**Disadvantages of Doubly:**
1. **Extra memory** for the `prev` pointer in every node.
2. **More pointer manipulation** — every insert/delete updates two pointers instead of one, so more code and more chance of bugs.
3. Slightly slower operations due to the extra pointer maintenance.

**Advantage of Singly:** less memory, simpler code.

---

## 10. Circular Linked List — how to make it, working, difference, applications

**Definition:** A linked list in which the **last node points back to the first node** instead of to NULL. There is no NULL at the end, so the list forms a closed ring.

**How to make it:** take a normal singly linked list and set `last->next = head`. (A circular *doubly* linked list additionally has `head->prev = last`.)

**Working — the key difference in code:**
- In a singly list you traverse with `while (temp != NULL)`.
- In a circular list `temp` is never NULL, so you traverse with **`do { ... temp = temp->next; } while (temp != head);`**
- If you write `while(temp != NULL)` on a circular list you get an **infinite loop** — that is the classic exam trap.

**How is it different from a singly LL:**

| Singly LL | Circular LL |
|---|---|
| Last node's `next` = NULL | Last node's `next` = head |
| Has a definite end | No end — forms a ring |
| From a given node you can reach only the nodes after it | From **any** node you can reach **every** node |
| Traverse with `while(p != NULL)` | Traverse with `do..while(p != head)` |
| Cannot loop back to start without restarting | Naturally loops back |

**Tip:** It is often better to keep a pointer to the **last** node rather than the first, because then `last->next` is the head — giving O(1) insertion at *both* ends.

**Applications of circular linked list:**
1. **Round-robin CPU scheduling** — each process gets a time slice and the OS cycles endlessly through the ready queue.
2. **Circular queue** implementation.
3. Multiplayer/turn-based games — passing turns around players repeatedly.
4. Music/video playlist on repeat, image carousels/slideshows.
5. **Buffering** — circular buffers for streaming data.
6. Managing computer memory allocation (free list traversal).
7. Fibonacci heap implementation.

---

## 11. Applications of ALL (rapid-fire answers)

**Stack (LIFO):**
1. Function call management — the **call stack**, storing activation records / return addresses.
2. **Recursion** (implemented using the system stack).
3. **Expression conversion** — infix → postfix/prefix.
4. **Expression evaluation** — postfix/prefix evaluation.
5. **Parenthesis / bracket matching** in compilers.
6. **Undo–redo** in editors; **back button** in browsers.
7. **Backtracking** — maze solving, N-Queens, DFS.
8. Reversing a string or a linked list.
9. Tower of Hanoi.
10. Syntax parsing in compilers.

**Queue (FIFO):**
1. **CPU scheduling**, disk scheduling, job scheduling in OS.
2. **Printer spooling**.
3. **BFS** (Breadth First Search) in graphs/trees.
4. Handling interrupts, IO buffers, pipes.
5. Call center / ticket counter waiting lines.
6. Data transfer between two asynchronous processes (buffering).
7. Round-robin scheduling (circular queue).

**Circular Queue:** Round-robin scheduling, traffic light systems, memory management, CPU scheduling — solves the false-overflow problem of a linear queue.

**Priority Queue:** Dijkstra's shortest path, Prim's MST, Huffman coding, OS process scheduling by priority, A* search, emergency room triage.

**Dequeue (Double Ended Queue):** Undo operations, browser history, sliding window maximum, job stealing algorithms, palindrome checking.

**Linked List:**
1. Implementing stacks, queues, graphs (adjacency list).
2. **Dynamic memory allocation** (free-block list).
3. **Polynomial representation and arithmetic**.
4. **Sparse matrix** representation.
5. Music playlist / image viewer (next-previous).
6. Undo functionality, browser back-forward (doubly LL).
7. Hash table chaining (collision handling).
8. Large number (big-integer) arithmetic.

**Array:**
1. Storing and accessing a fixed collection of data.
2. Implementing other structures — stacks, queues, heaps, hash tables, matrices.
3. Lookup tables, database records.
4. Binary search (needs random access).
5. Sorting algorithms.

---

## 12. JNUT / Rapid Fire Bank

**Why is the stack called LIFO?** Insertion (push) and deletion (pop) both happen at the same end, the **top**, so the last element inserted is the first removed.

**Stack overflow / underflow?** Overflow = push onto a full stack (`top == MAX-1`). Underflow = pop from an empty stack (`top == -1`).

**Initial value of top?** `top = -1` for an empty stack (when using 0-based indexing).

**Queue overflow/underflow?** Linear queue: overflow when `rear == MAX-1`, underflow when `front == -1 || front > rear`. Empty condition in circular queue: `front == -1`; full condition: `(rear+1) % MAX == front`.

**Why circular queue?** In a linear queue, after several deletions `front` moves forward and those front slots are wasted — `rear` hits `MAX-1` and reports overflow even though the queue has free space. This is **false/logical overflow**. A circular queue wraps `rear` around using `rear = (rear+1) % MAX` and reuses them.

**Data structure vs data type?** A data type defines the kind of value and operations (int, float). A data structure is a way of **organising and storing** data in memory so it can be used efficiently.

**Linear vs non-linear data structure?** Linear: elements in a sequence, one after another — array, stack, queue, linked list. Non-linear: hierarchical/ many-to-many relationships — tree, graph.

**Static vs dynamic memory allocation?**
Static: memory allocated at compile time, on the **stack**, fixed size, freed automatically (e.g. `int a[10];`).
Dynamic: allocated at run time, on the **heap**, size decided at run time, must be freed with `free()` (e.g. `malloc`).

**malloc vs calloc vs realloc vs free?**
- `malloc(n*sizeof(int))` — one argument, allocates a block, contents are **garbage**.
- `calloc(n, sizeof(int))` — two arguments, allocates and **initialises everything to zero**. Slightly slower.
- `realloc(ptr, newsize)` — resizes an already allocated block, preserving contents.
- `free(ptr)` — releases memory back to the heap. All return `void*`; return **NULL** on failure.

**What is a pointer?** A variable that stores the **memory address** of another variable.

**NULL pointer vs dangling pointer vs wild pointer?**
- NULL pointer: points to nothing, value 0.
- Dangling pointer: points to memory that has already been freed/deallocated.
- Wild pointer: uninitialised pointer pointing to a random address.

**What is a memory leak?** Memory allocated with `malloc` that is never `free`d and whose pointer is lost — it stays reserved until the program ends.

**What is the self-referential structure?** A structure that contains a pointer to a structure of its own type — this is exactly what a linked-list node is:
```c
struct node { int data; struct node *next; };
```

**Why `struct node *next` and not `struct node next`?** Because the size of the structure would then be infinite/undefined — the compiler cannot determine it. A pointer has a fixed known size.

**Time complexity of linked list operations?** Search O(n), insert at head O(1), insert at end O(n), delete a given node in a singly LL O(n) (need previous), in a doubly LL O(1).

**What is ADT (Abstract Data Type)?** A model that defines **what operations** a data structure supports and their behaviour, **without specifying how** they are implemented. Stack ADT = push, pop, peek, isEmpty — whether it uses an array or a linked list is hidden.

**What is a sparse matrix?** A matrix in which most elements are zero. Storing all of it wastes space, so it is stored in **3-tuple (row, column, value)** form or using linked lists.

**Recursion vs Iteration?** Recursion: function calls itself, needs a base case, uses the system **stack**, more memory, cleaner code. Iteration: loops, no extra stack space, faster. Every recursion can be converted to iteration using an explicit stack.

**What is tail recursion?** A recursive call that is the **very last operation** in the function, with nothing left to compute after it returns. The compiler can optimise it into a loop, reusing the same stack frame (tail-call optimisation), so it uses O(1) stack instead of O(n).

**Tower of Hanoi moves?** `2^n - 1`. Recurrence: `T(n) = 2T(n-1) + 1`.

**Infix, prefix, postfix?**
- Infix: `A + B` (operator between operands) — how humans write it.
- Prefix / Polish: `+ A B` (operator before).
- Postfix / Reverse Polish: `A B +` (operator after).
- Postfix is used by machines because it **needs no parentheses and no precedence rules** — it can be evaluated in a single left-to-right pass with one stack.

**Operator precedence in the conversion?** `^` (highest, right-associative) > `*` `/` > `+` `-` (lowest). Parentheses override all.

**Time-space trade-off?** Solving a problem with less time usually needs more memory, and vice versa. Example: a lookup table/hash uses extra space to get O(1) time instead of O(n) searching.

**Big O, Omega, Theta?** O = upper bound (worst case), Ω = lower bound (best case), Θ = tight bound (both).

**What is a header node / header list?** A dummy first node that does not hold real data; it may store information like the count of nodes. It removes the special case of "inserting/deleting at the head", simplifying code. A **two-way header list** is a circular doubly linked list with a header node.

**Two-way header list?** A circular doubly linked list containing a header node — from the header you can move in both directions and every node is reachable.

**Generalized linked list?** A linked list where a node's data can itself be another linked list — used to represent polynomials in several variables, multi-dimensional structures, and lists like `(a, (b, c), d)`.

**Polynomial representation with a linked list?** Each node stores `coefficient`, `exponent`, and `next`. Terms are kept in decreasing order of exponent. Addition: traverse both lists, compare exponents — equal → add coefficients, otherwise copy the larger-exponent term.

**Array as a parameter / why is it passed by reference?** An array name decays to a pointer to its first element, so the function receives the address, not a copy. Changes inside the function affect the original array.

**What is an ordered list?** A list whose elements are maintained in sorted order at all times, so insertion must find the correct position.

**Difference between peek/top and pop?** `peek` returns the top element without removing it; `pop` removes and returns it.

**Can a stack be implemented using recursion?** Recursion *uses* a stack (the system call stack), so yes — recursion is an implicit stack.

**Which data structure is used for BFS / DFS?** BFS → Queue. DFS → Stack (or recursion).

**Complexity of push/pop?** O(1) for both, in array and linked-list implementations.

**Advantage of linked-list stack over array stack?** No fixed size limit — no overflow until heap memory is exhausted, and no wasted preallocated space.
