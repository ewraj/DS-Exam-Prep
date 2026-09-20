# Data Structures — Viva + Lab Exam Prep

Syllabus covered: Unit 1 (arrays, stacks, recursion) and Unit 2 (queues, linked lists) — everything up to linked list.

## Study in this order

### Tonight (viva is tomorrow) — ~2 hours
1. `viva/01-VIVA-ANSWERS.md` — every question you were told they ask, answered in speakable form. Read it fully, out loud.
2. `viva/02-NIGHT-BEFORE-CHEATSHEET.md` — last 20 minutes before you walk in.
3. Skim `lab/08_singly_linked_list.c` and `lab/02_stack_array.c`. If you can write those two from memory, the viva code questions are handled.

### Before the lab exam
Work through `lab/` in number order. Type each one yourself once — do not just read it.

## Files

| File | Syllabus | Topic |
|---|---|---|
| `lab/01_array_basics.c` | 16 a–d, 17 a–b | sum of evens, union, intersection, reverse, max, dynamic array |
| `lab/02_stack_array.c` | 17 c | stack using array |
| `lab/03_queue_array.c` | 18 a | queue using array |
| `lab/04_circular_queue.c` | Unit 2 | circular queue |
| `lab/05_infix_to_postfix.c` | 18 b | infix → postfix |
| `lab/06_evaluate_postfix.c` | 18 c | postfix evaluation |
| `lab/07_list_left_right.c` | 19 b | list with left/right pointers, search + delete, "Unsuccessful Search" |
| `lab/08_singly_linked_list.c` | 19, 20 b | singly LL — insert, delete, search, reverse ⭐ master this |
| `lab/09_string_list_alphabetical.c` | 20 a | insert strings in alphabetical order |
| `lab/10_doubly_linked_list.c` | 20 c | doubly LL — insert, delete, display |
| `lab/11_circular_linked_list.c` | 21 | circular LL — insert, delete, display |
| `lab/12_stack_queue_linked_list.c` | 22 a, 22 c | stack and queue using linked list |
| `lab/13_stack_using_one_queue.c` | viva | stack from a SINGLE queue ⭐ |
| `lab/14_stack_using_two_queues.c` | viva | stack from two queues ⭐ |
| `lab/15_queue_using_two_stacks.c` | viva | queue from two stacks ⭐ |
| `lab/16_queue_double_pointers.c` | 22 b | queue using double pointers |
| `lab/17_monotonic_stack.c` | viva | monotonic stack, next greater/smaller, stock span ⭐ |
| `lab/18_recursion_hanoi_polynomial.c` | Unit 1, 2 | recursion, tail recursion, Tower of Hanoi, polynomial addition, sparse matrix |

## Running the programs

**There is no C compiler installed on this machine** — I checked for gcc, clang, cc, tcc and cl, and found none. So these programs are written and reviewed but **not compile-tested**. Pick one:

**Option A — install MinGW-w64 (recommended, ~5 min)**
```powershell
winget install -e --id BrechtSanders.WinLibs.POSIX.UCRT
```
Restart the terminal, then:
```powershell
cd "C:\Users\win 11\DS-Exam-Prep\lab"
gcc 08_singly_linked_list.c -o a.exe
.\a.exe
```
`06_evaluate_postfix.c` needs the maths library: `gcc 06_evaluate_postfix.c -o e.exe -lm`

**Option B — Code::Blocks / Dev-C++ / Turbo C**, whatever your lab uses. Open the `.c` file and press build+run. These programs use only ANSI C (declarations at the top of blocks, no `//` comments in the code bodies), so they compile on old Turbo C too.

**Option C — an online compiler** (onlinegdb.com) — paste and run. Fastest if you just want to see output tonight.

Tell me once you've picked one and I'll compile all 18 and fix anything that breaks.

## Style note

Every program follows the exact pattern examiners expect: `#define MAX`, global structure, `createNode()` with a NULL check after `malloc`, a `switch` menu in `main`, and `free()` on delete. Overflow and underflow are always handled — examiners check for that specifically.
