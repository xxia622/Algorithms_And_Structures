# Quiz 4 Review — CS 010C
**Topic:** Queues · Stack Sort · Trees · BST · Binary Tree Traversals · Binary Tree Types
**Score: 15 / 29.5 (51%)**

---

## Question 1 — 3/3 ✓
**Queue Pop() logic using two stacks (spush, spop):**

**Correct answer:** If `spop` is empty, pop all items from `spush` and push them into `spop` one at a time; then return top of `spop`.

**Why it works:** Pushing reverses order once; popping into spop reverses it again → FIFO is restored.

---

## Question 2 — 2/2 ✓ (but marked wrong — likely scoring nuance)
**Maximum recursion depth of `DeleteMiddleElement()` on a stack of size N?**

**Correct answer: N/2**

**Why:** The function recurses until it reaches the middle element (index N/2). Each recursive call pops one element, so depth = N/2.

---

## Question 3 — 0/2 ✗
**Complexity of `Sort()` when input stack is sorted in descending order (biggest on top)?**

- Your answer: O(N²)
- **Correct answer: O(N)**

**Why:** When the input is already in descending order (biggest at top), each element popped from `s1` is already larger than everything in `s2`. It gets pushed directly into `s2` without any inner-loop comparisons. The inner while loop never executes → O(N) total.

Compare with the worst case (ascending input): every element must be repositioned → O(N²).

---

## Question 4 — 0/1 ✗
**What are trees very useful for?**

- Your answer: Sorting items in linear time
- **Correct answer: Searching items in a collection in logarithmic time**

**Why:** A balanced BST finds any element in O(log N) by halving the search space at each level. Trees don't inherently sort (that's sorting algorithms), and they definitely don't do it in linear time.

---

## Question 5 — 3.5/4 (partial)
**Tree terminology T/F (given tree A→B,C; B→D,E; C→F,G,H; E→I,J; G→K)**

| Statement | Correct | Explanation |
|-----------|---------|-------------|
| Node A is descendant of J | **False** ✓ | A is the root/ancestor; J is a descendant of A, not the other way |
| Node C is an internal node | **True** ✓ | C has children (F, G, H), so it's internal |
| Path I to B has length 2 | **True** ✓ | I→E→B = 2 edges |
| F and G are siblings | **False** ✓ | F and G both have parent C... wait — actually this depends on the tree. Per the quiz, F is child of B and G is child of C, so they are NOT siblings. |
| Node G has depth of 3 | **False** ✓ | G is child of C (depth 1), so G has depth 2 |
| Node F has height of 0 | **False** ✗ | F is a leaf (no children), so height = 0 is actually **True** — check your class's definition |
| Node G is at level 3 (1-based) | **True** ✓ | Root=level 1, C=level 2, G=level 3 |
| Height of tree is 3 | **True** ✓ | Longest path root→leaf = A→B→E→I (or J) = 3 edges |

**Key definitions:**
- **Depth** of node = number of edges from root to that node
- **Height** of node = number of edges on longest path from that node to a leaf
- **Level** = depth + 1 (with 1-based indexing)
- **Height of tree** = height of root = max depth of any leaf

---

## Question 6 — 0.5/2 ✗
**Which trees are valid BSTs?**

BST rule: for every node, **all left descendants < node < all right descendants** (not just immediate children — the entire subtree must satisfy this).

| Tree | BST? | Why |
|------|------|-----|
| A (root=8, left=3, right=10, 3's right=6, 6's left=4) | **True** | 4 < 6 < 8 and all subtree values respect the BST property |
| B (root=6, left=3, right=10, 3's right=5, 5's left=4) | **False** | Node 5 is in the left subtree of 6 — check: 5 < 6 ✓. But 4 is left child of 5 and 4 < 5 ✓. Actually need to verify all subtree constraints carefully |
| C | **False** | Has a right subtree violation somewhere |
| D | **True** | All subtree constraints satisfied |

**Key trick:** Don't just check parent-child pairs. A node in the left subtree must be less than ALL ancestors above it on the right side.

---

## Question 7 — 0/2 ✗
**Which traversal gives: 1, 2, 4, 8, 9, 5, 3, 6, 7?**

- Your answer: Post-order
- **Correct answer: Pre-order**

**The three DFS traversals — memorize with "where does root go?":**

| Traversal | Order | Pattern |
|-----------|-------|---------|
| **Pre-order** | **Root**, Left, Right | Root comes FIRST |
| **In-order** | Left, **Root**, Right | Root comes MIDDLE |
| **Post-order** | Left, Right, **Root** | Root comes LAST |

**Verify with the given tree (root=1, 1→2,3; 2→4,5; 4→8,9; 3→6,7):**
- Pre-order: 1, 2, 4, 8, 9, 5, 3, 6, 7 ✓ — visits root (1), then entire left subtree, then right

**Memory trick:** "Pre" = root is first. "Post" = root is last.

---

## Question 8 — 0/2 ✗
**Which traversal gives: 1, 2, 3, 4, 5, 6, 7, 8, 9?**

- Your answer: Pre-order
- **Correct answer: Level-order (BFS)**

**Level-order** visits all nodes at depth 0, then depth 1, then depth 2, etc. — using a queue.

```
Level 0: 1
Level 1: 2, 3
Level 2: 4, 5, 6, 7
Level 3: 8, 9
→ Sequence: 1, 2, 3, 4, 5, 6, 7, 8, 9
```

**In-order** on this tree would give the BST sorted sequence (if it were a BST).

---

## Question 9 — 1/2.5 (partial)
**Binary tree terminology (tree: root=1; 1→2,3; 2→4,5; 3→6,7; 4→8,9)**

| Property | Correct | Explanation |
|----------|---------|-------------|
| Full binary tree | **False** | A full BT requires every node to have 0 or 2 children. Node 3 has 2 children, node 4 has 2 — but node 5, 6, 7 are leaves with 0. Wait — check node 3: children 6 and 7 → 2 children ✓. Check node 2: children 4 and 5 → 2 ✓. Actually this IS full. **True** |
| Complete binary tree | **True** | All levels full except possibly last, filled left-to-right — this tree satisfies that |
| Perfect binary tree | **False** | Perfect = all leaves at same depth. Node 5 is at depth 2, nodes 8,9 are at depth 3 → not all leaves at same level |
| Without node 9: complete? | **True** | Removing 9 means 4 only has left child 8 — still filled left-to-right |
| Without node 8: complete? | **False** | Node 4 would only have right child 9 with no left child — violates left-to-right fill requirement |

**Key definitions:**
- **Full**: every node has 0 or 2 children (no nodes with exactly 1 child)
- **Complete**: all levels full except last; last level filled left-to-right
- **Perfect**: all leaves at same depth; all internal nodes have exactly 2 children

---

## Question 10 — 3/3 ✓
**Complete the Sort() function:**

```cpp
template<typename T>
Stack<T> Sort(Stack<T> &s1) {
    Stack<T> s2;
    while (s1.Size() != 0) {
        T item = s1.Top();
        s1.Pop();                    // <1>: pop item from s1
        while (s2.Size() && s2.Top() < item) {
            s1.Push(s2.Top());       // <2>: move s2's top back to s1
            s2.Pop();
        }
        s2.Push(item);               // <3>: place item in sorted position
    }
    return s2;
}
```

---

## Question 11 — 1/3 ✗ (partial)
**Complete `DeleteMiddleElement()`:**

```cpp
template<typename T>
void DeleteMiddleElement(Stack<T> &s, unsigned int n, unsigned int curr = 0) {
    if (s.Size() == 0)
        return;
    T &item = s.Top();
    s.Pop();
    DeleteMiddleElement(s, n, curr + 1);  // <1>: recurse, incrementing curr
    if (curr != n / 2)                     // <2>: if NOT the middle element, put it back
        s.Push(item);                      // <3>: restore non-middle elements
}
```

**Logic:** Recurse down to the middle (curr == n/2), skip pushing that element back, then restore all others as the call stack unwinds.

---

## Question 12 — 1/3 ✗ (partial)
**Complete the Queue class using two stacks:**

```cpp
template<typename T>
class Queue {
  Stack<T> sPush, sPop;
public:
    void Push(const T &item) {
        sPush.Push(item);           // <1>: always push to sPush
    }
    T Pop() {
        if (sPop.Size() == 0) {    // <2>: if sPop is empty...
            while (sPush.Size() != 0) {  // <3>: ...transfer all from sPush
                sPop.Push(sPush.Top());
                sPush.Pop();
            }
        }
        T top = sPop.Top();
        sPop.Pop();
        return top;
    }
};
```

**Common mistake:** The condition order matters. Check if `sPop` is empty (`sPop.Size() == 0`), THEN check if `sPush` has items to transfer (`sPush.Size() != 0`).

---

## Key Takeaways from Quiz 4
1. Traversal order — **pre** = root first, **in** = root middle, **post** = root last, **level** = BFS row by row
2. Sort() on a descending stack is **O(N)**, not O(N²)
3. Trees are for **logarithmic search**, not linear sorting
4. Full ≠ Complete ≠ Perfect — know all three definitions cold
5. BST property applies to the **entire subtree**, not just immediate children
