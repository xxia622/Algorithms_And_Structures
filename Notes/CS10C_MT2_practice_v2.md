# CS 10C MT2 — Custom Practice Exam (6 questions, ~90 min)

Built to mirror Ty's actual MT2 format per his email: 6 questions, mix of coding + FRQ/drawing, in-class, closed-everything.

Topics emphasized based on Ty's emphasis: **recursion + trees, lab content (BST/Splay/Trie), code from lectures**. Includes LLRB + Splay (NOT in official practice).

**Try each cold first — solutions at bottom. Don't peek.**

---

## Q1 (15 pts) — BST Recursive Code

A binary search tree has the following node definition:

```cpp
struct Node {
  int key;
  Node* left;
  Node* right;
};
```

Write the recursive function `int CountInRange(Node* n, int low, int high)` that returns the number of keys in the BST that fall in the inclusive range `[low, high]`. **Use the BST property to prune subtrees that cannot contain valid keys** (i.e., do not visit subtrees you can rule out).

```cpp
int CountInRange(Node* n, int low, int high) {

}
```

---

## Q2 (15 pts) — AVL Insertion with Rotations

Starting from an empty AVL tree, insert the following keys in order:

```
50, 30, 20, 40, 70, 80, 75
```

For **each insertion that triggers a rotation**, state:
- Which node became unbalanced
- The type of rotation (single left, single right, left-right double, or right-left double)
- Draw the tree immediately after the rotation completes

(You don't need to redraw the tree for insertions that don't trigger rotations — just show the final tree after all 7 insertions.)

---

## Q3 (15 pts) — Red-Black Tree Insertion

Consider the following valid red-black tree:

```
        50 (B)
       /     \
    30 (B)   70 (B)
    /   \
 20(R)  40(R)
```

**Part A (8 pts):** Insert **10** into this tree. Show the resulting tree, clearly labeling each node as RED or BLACK. Explain what fix (if any) was needed (recolor and/or rotation).

**Part B (7 pts):** Starting from the result of Part A, now insert **5**. Show the resulting tree with colors. Explain the fix.

---

## Q4 (15 pts) — Heaps (Floyd's + ExtractMax)

Given the unsorted array (index 0 unused):

```
[_, 4, 10, 3, 5, 1, 2]
```

**Part A (8 pts):** Build a **max-heap** using **Floyd's method** in O(N). Starting from the last internal node, show each PercolateDown step (write the array after each swap). Draw the final max-heap as a tree.

**Part B (7 pts):** From the max-heap you built, perform **ExtractMax twice**. After each extraction, show the resulting heap array AND list the extracted value. (Reminder: ExtractMax swaps root with last element, shrinks the heap, then PercolateDown on the new root.)

---

## Q5 (15 pts) — Splay Tree

Splay trees apply rotations after every operation to bring the accessed node to the root.

**Part A (5 pts):** List all 6 splay rotation cases (use the same naming convention as your Lab 6 implementation).

**Part B (10 pts):** Consider the following splay tree:

```
       10
      /  \
     5    20
    /
   3
```

Perform `Splay(3)` on this tree. Show each intermediate step (the tree after each rotation). State the splay case being applied.

---

## Q6 (10 pts) — Sorting + LLRB

**Part A (5 pts) — Quicksort partition:**

Trace one complete partition step of quicksort on `[4, 8, 2, 9, 1, 6, 3]`, using the **leftmost element as pivot**. Use left `i` and right `j` scanning pointers. Show the array after each swap and identify the final position of the pivot.

**Part B (5 pts) — LLRB validity:**

The following tree is a red-black tree. Is it also a valid **Left-Leaning Red-Black (LLRB)** tree? If not, identify the LLRB-specific property that is violated.

```
       20 (B)
      /     \
   10 (B)  40 (R)
```

---

---

# SOLUTIONS

(Don't read until you've attempted each question cold.)

---

## Q1 Solution

```cpp
int CountInRange(Node* n, int low, int high) {
    if (n == nullptr) return 0;
    if (n->key < low)  return CountInRange(n->right, low, high);   // prune left
    if (n->key > high) return CountInRange(n->left,  low, high);   // prune right
    // n->key is in range
    return 1 + CountInRange(n->left, low, high) + CountInRange(n->right, low, high);
}
```

**Key insight:** if `n->key < low`, the entire left subtree is also < low → skip it. If `n->key > high`, the entire right subtree is > high → skip it. This is the BST property at work.

**Common mistakes:**
- Forgetting `return` in front of recursive calls → result thrown away
- Not pruning (visiting both children every time) → still correct but loses style points
- Forgetting to add 1 when current node is in range

---

## Q2 Solution

Trace each insertion:

```
Insert 50:  [50]   no rotation
Insert 30:  50
           /
          30                       no rotation, BF(50)=+1

Insert 20:  50
           /
          30
         /
        20         BF(20)=0, BF(30)=+1, BF(50)=+2 → VIOLATION at 50
                   Case: LL (BF(50)=+2, BF(30)=+1, same direction)
                   Fix: Single right rotation on 50

  After rotation:    30
                    /  \
                   20   50

Insert 40:        30
                 /  \
                20   50
                    /
                   40       no rotation

Insert 70:        30
                 /  \
                20   50
                    /\
                   40 70    no rotation, BF(50)=0, BF(30)=-1

Insert 80:        30
                 /  \
                20   50
                    /\
                   40 70
                       \
                       80    BF(70)=-1, BF(50)=-1, BF(30)=-2 → VIOLATION at 30
                             Case: RR (BF(30)=-2, BF(50)=-1, same direction)
                             Fix: Single left rotation on 30

  After rotation:        50
                        /  \
                       30   70
                      /\     \
                     20 40   80

Insert 75:             50
                      /  \
                     30   70
                    /\     \
                   20 40   80
                           /
                          75       BF(80)=+1, BF(70)=-2 → VIOLATION at 70
                                    Case: RL (BF(70)=-2, BF(80)=+1, opposite directions)
                                    Fix: Right rotate 80, then left rotate 70

  After rotations:       50
                        /  \
                       30   75
                      /\    /\
                     20 40 70 80
```

**Final tree (after all 7 insertions):**
```
        50
       /  \
      30   75
     /\    /\
    20 40 70 80
```

**Rotations summary:** LL at 50 (after inserting 20), RR at 30 (after inserting 80), RL at 70 (after inserting 75).

---

## Q3 Solution

**Part A — Insert 10:**

- BST insertion: 10 < 50 → left to 30; 10 < 30 → left to 20; 10 < 20 → left. Insert as RED at left child of 20.
- Parent (20) is RED → violation.
- Grandparent = 30. Uncle = 30's other child = 40 (RED).
- **Uncle is RED → RECOLOR:** parent (20) → B, uncle (40) → B, grandparent (30) → R.

```
        50 (B)
       /     \
    30 (R)   70 (B)
    /   \
 20(B)  40(B)
 /
10(R)
```

- Recurse on grandparent (30). 30 is RED, parent 50 is BLACK → no further violation. Done.

**Part B — Insert 5 (starting from the tree above):**

- BST insertion: 5 < 50 → left to 30; 5 < 30 → left to 20; 5 < 20 → left to 10; 5 < 10 → left. Insert as RED at left child of 10.
- Parent (10) is RED → violation.
- Grandparent = 20. Uncle = 20's other child = NIL (BLACK).
- **Uncle is BLACK → ROTATE.**
- 5 is LEFT of 10. 10 is LEFT of 20. Same direction → **LL case → single right rotation on 20**.
- Color swap: P (10) and G (20) swap → 10 becomes BLACK, 20 becomes RED.

After right rotate on 20 + color swap:

```
        50 (B)
       /     \
    30 (R)   70 (B)
    /   \
 10(B)  40(B)
 /\
5(R)20(R)
```

Verify properties: root black ✓, no consecutive reds ✓, black-heights all 2 ✓.

---

## Q4 Solution

**Part A — Floyd's heapify on `[_, 4, 10, 3, 5, 1, 2]` (n=6, last internal = 3):**

```
Initial tree:        4
                    / \
                   10  3
                  /\   /
                 5 1  2

PercolateDown(3): node=3, only child at idx 6 (value 2). 3>2, no swap.

PercolateDown(2): node=10, children at idx 4 (5), idx 5 (1). Larger=5. 10>5, no swap.

PercolateDown(1): node=4, children at idx 2 (10), idx 3 (3). Larger=10. Swap.
  → [_, 10, 4, 3, 5, 1, 2]
  Now at idx 2 (value 4). Children at idx 4 (5), idx 5 (1). Larger=5. Swap.
  → [_, 10, 5, 3, 4, 1, 2]
  Now at idx 4, no children. Stop.
```

**Final max-heap:** `[_, 10, 5, 3, 4, 1, 2]`

Tree:
```
       10
      /  \
     5    3
    /\   /
   4 1  2
```

**Part B — ExtractMax twice:**

**ExtractMax #1:**
- Swap a[1] and a[6]: `[_, 2, 5, 3, 4, 1, 10]`. Extracted: **10**.
- Heap size now 5. PercolateDown(1):
  - Children at idx 2 (5), idx 3 (3). Larger=5. Swap.
  - `[_, 5, 2, 3, 4, 1, (10)]`
  - Now at idx 2 (value 2). Children at idx 4 (4), idx 5 (1). Larger=4. Swap.
  - `[_, 5, 4, 3, 2, 1, (10)]`
  - Now at idx 4, no children. Stop.

Heap after #1: `[_, 5, 4, 3, 2, 1]` (size 5). 10 is at idx 6 outside heap.

**ExtractMax #2:**
- Swap a[1] and a[5]: `[_, 1, 4, 3, 2, 5, 10]`. Extracted: **5**.
- Heap size now 4. PercolateDown(1):
  - Children at idx 2 (4), idx 3 (3). Larger=4. Swap.
  - `[_, 4, 1, 3, 2, (5), (10)]`
  - Now at idx 2 (value 1). Children at idx 4 (2). Larger=2. Swap.
  - `[_, 4, 2, 3, 1, (5), (10)]`
  - Now at idx 4, no children. Stop.

Heap after #2: `[_, 4, 2, 3, 1]` (size 4). 5 at idx 5, 10 at idx 6 outside heap.

Extracted in order: **10, 5**.

---

## Q5 Solution

**Part A — 6 splay cases:**

Assuming target node is N, parent P, grandparent G:

1. **Zig-Right:** P is root, N is right child → left rotate on root
2. **Zig-Left:** P is root, N is left child → right rotate on root
3. **Zig-Zig Left-Left:** N is left of P, P is left of G → right rotate G, then right rotate P
4. **Zig-Zig Right-Right:** N is right of P, P is right of G → left rotate G, then left rotate P
5. **Zig-Zag Right-Left:** N is right of P, P is left of G → left rotate P, then right rotate G
6. **Zig-Zag Left-Right:** N is left of P, P is right of G → right rotate P, then left rotate G

**Part B — Splay(3) on the given tree:**

```
Initial:
       10
      /  \
     5    20
    /
   3
```

- 3 is left child of 5. 5 is left child of 10. → **Case 3: Zig-Zig Left-Left.**
- Step 1: Right rotate on G (10). 5 takes 10's spot. 10 becomes 5's right child. 5's old right (null) becomes 10's left.

```
After right rotate on 10:
       5
      / \
     3   10
          \
          20
```

- Step 2: Right rotate on P (5, which is now the root). 3 takes 5's spot. 5 becomes 3's right child. 3's old right (null) becomes 5's left.

```
Final after Splay(3):
       3
        \
         5
          \
          10
            \
            20
```

Notice: 3 is now at the root, as expected from splay.

---

## Q6 Solution

**Part A — Quicksort partition on `[4, 8, 2, 9, 1, 6, 3]`, pivot = 4:**

```
Initial: [4, 8, 2, 9, 1, 6, 3]   i=1, j=6

i scan: a[1]=8 ≥ 4 STOP. i=1.
j scan: a[6]=3 ≤ 4 STOP. j=6.
i<j → swap a[1] and a[6]
       [4, 3, 2, 9, 1, 6, 8]   i=2, j=5

i scan: a[2]=2<4 → i=3. a[3]=9≥4 STOP. i=3.
j scan: a[5]=6>4 → j=4. a[4]=1≤4 STOP. j=4.
i<j (3<4) → swap a[3] and a[4]
       [4, 3, 2, 1, 9, 6, 8]   i=4, j=3

i scan: a[4]=9≥4 STOP. i=4.
j scan: a[3]=1≤4 STOP. j=3.
i>j → STOP, swap pivot (a[0]=4) with a[j]=a[3]=1
       [1, 3, 2, 4, 9, 6, 8]
```

**Final partitioned array:** `[1, 3, 2, 4, 9, 6, 8]`. Pivot 4 is now at **index 3** (its final sorted position). Left of pivot {1, 3, 2} all < 4. Right of pivot {9, 6, 8} all > 4.

**Part B — LLRB validity:**

Tree:
```
       20 (B)
      /     \
   10 (B)  40 (R)
```

This is a valid **red-black tree** (root black, no consecutive reds, all paths from root to NIL have 1 black node).

But it is **NOT a valid LLRB**. The LLRB-specific extra property:

**Red links must lean LEFT** (no right red links allowed).

Here, 40 is a RIGHT-leaning red node (it's the right child of 20). To fix this in LLRB, you would left-rotate at 20 so the red link leans left.

---

# DRILL NOTES FOR TOMORROW

After completing this practice exam, additional drill targets:

1. **Re-do MT1 Q3 (RemoveAllExceptFirst)** — write cleaner code without `Find` loop, use 2 pointers walking the list
2. **Write `Remove(Node*, int key)` for BST** — two-child case using in-order successor
3. **Write `PercolateDown(int i, int heap_size)`** — full implementation cold (from cheatsheet)
4. **Re-trace AVL sequence with multi-rotation:** insert 10, 20, 30, 40, 50, 25 — should trigger RR then a fixup
5. **Splay tree zig-zag case:** Splay(15) on `[10 / [5, 20 / [15, _]]]` — exercises left-right zig-zag
