# Quiz 6 Practice Exam — CS 010C
**Topics:** Red-Black Trees · Left-Leaning Red-Black Trees · Splay Trees · B-Trees · Priority Queue / Binary Heap
**28 pts | 8 Questions | 30 Minutes**

> Answers and explanations are included at the end of each question. Cover them while taking the practice exam, then check your work.

---

## Question 1 — 5 pts
### Red-Black Tree Properties

For each statement about Red-Black Trees, select **True** or **False**:

**(a)** Every newly inserted node starts as **red**.

**(b)** In a valid RBT, a red node can have one red child and one black child.

**(c)** All paths from any node to its descendant NIL leaves must have the same number of **black** nodes.

**(d)** The root of a Red-Black Tree can temporarily be red during insertion before being fixed.

**(e)** A Red-Black Tree guarantees O(log N) worst-case for all operations.

---

<details>
<summary>Answers</summary>

| Statement | Answer | Explanation |
|-----------|--------|-------------|
| (a) Every new node starts red | **True** | Inserting red preserves black-height automatically; we then fix red-red violations |
| (b) Red node can have one red, one black child | **False** | Property 4: if a node is red, **both** children must be black — no exceptions |
| (c) Same number of black nodes on all root-to-NIL paths | **True** | This is property 5 (black-height invariant) — note it is **black** nodes, not total nodes |
| (d) Root can be temporarily red | **True** | If the root ends up red after fixes, we simply recolor it black at the end |
| (e) O(log N) worst-case guaranteed | **True** | Height ≤ 2 log(N+1), so all operations are O(log N) |

</details>

---

## Question 2 — 3 pts
### Red-Black Tree — Insertion Case

Insert key **15** into the following Red-Black Tree (B = black, R = red):

```
        10(B)
       /      \
     5(B)    20(B)
             /
           15(R)  ← just inserted
```

Node 15 was inserted as red. Its parent (20) is black. What action is required?

- A) Recolor 20 to red and 15 to black
- B) Left rotation between 10 and 20
- C) No fix needed — the tree is already valid
- D) Right rotation between 20 and 15, then recolor

---

<details>
<summary>Answer</summary>

**Correct: C — No fix needed.**

The newly inserted node (15) is red, and its parent (20) is **black**. A red-red violation only occurs when a red node's parent is also red. Since the parent is black here, no fix is required. The tree satisfies all five RBT properties.

**Key check after any RBT insertion:** Is the parent of the new red node also red? If yes → fix. If no → done.

</details>

---

## Question 3 — 3 pts
### Left-Leaning Red-Black Tree — Fixing Operations

In an LLRB tree, match each situation to the correct fixing operation:

| Situation | Fixing Operation |
|-----------|-----------------|
| Right child is red, left child is black | ? |
| Left child is red AND left-left grandchild is also red | ? |
| Both left and right children are red | ? |

**Options:** `Rotate Left`, `Rotate Right`, `Flip Colors`

---

<details>
<summary>Answers</summary>

| Situation | Fixing Operation | Why |
|-----------|-----------------|-----|
| Right child red, left child black | **Rotate Left** | LLRB only allows red links on the left — rotate to move the red link to the left side |
| Left child red AND left-left also red | **Rotate Right** | Two consecutive left reds = a 4-node that needs splitting — rotate right to balance |
| Both children red | **Flip Colors** | Corresponds to splitting a 4-node in a 2-3-4 tree — push the "split" up to the parent |

**Memory tip:** Apply these three checks **bottom-up** after every insertion, in this order.

</details>

---

## Question 4 — 3 pts
### Splay Tree — Identifying the Splay Case

For each scenario, identify whether the splay operation is **Zig**, **Zig-Zig**, or **Zig-Zag**:

**(a)** Node X is the left child of node P, and P is the **root**.

**(b)** Node X is the left child of P, and P is the left child of grandparent G.

**(c)** Node X is the right child of P, and P is the left child of grandparent G.

---

<details>
<summary>Answers</summary>

| Case | Answer | Explanation |
|------|--------|-------------|
| (a) X is left child of root P | **Zig** | Parent is the root → single rotation (right-rotate P) |
| (b) X and P are both left children | **Zig-Zig** | Same direction (left-left) → rotate grandparent G first, then parent P |
| (c) X is right child, P is left child | **Zig-Zag** | Opposite directions → rotate parent P first, then grandparent G |

**Critical distinction — Zig-Zig vs two Zig steps:**
Zig-Zig rotates the **grandparent first**, then the parent. This is NOT the same as doing two individual zig rotations. The grandparent-first order is what achieves O(log N) amortized performance. Two zig steps on a degenerate (chain) tree would give O(N) amortized.

</details>

---

## Question 5 — 3 pts
### Splay Tree — After a Failed Search

Consider the following splay tree:

```
        20
       /  \
     10    30
    /  \
   5    15
```

We search for key **12** (which does not exist in the tree). What is true after the search completes?

- A) The tree is unchanged because the key was not found
- B) The last node visited during the search (15) is splayed to the root
- C) Node 10 is splayed to the root because it is the closest key
- D) An exception is thrown and the tree is unchanged

---

<details>
<summary>Answer</summary>

**Correct: B — Node 15 is splayed to the root.**

In a splay tree, **every access** (including failed searches) triggers a splay of the **last visited node**. The search for 12 would go: 20 → 10 → 15 (since 12 > 10, go right; 12 < 15, would go left but there's no left child → search ends at 15). Node 15 is then splayed to the root.

This is intentional: recently accessed regions of the tree move to the top for cache efficiency.

</details>

---

## Question 6 — 4 pts
### B-Tree Properties

Assume an **order-4 B-tree** (also called a 2-3-4 tree). Match each property to the correct value or answer True/False:

**(a)** Maximum number of keys in a single node: ?

**(b)** Minimum number of children a non-root internal node must have: ?

**(c)** All leaves are at the same level: True or False?

**(d)** When the root splits, the height of the tree **decreases**: True or False?

**Options for (a) and (b):** `1`, `2`, `3`, `4`

---

<details>
<summary>Answers</summary>

| Property | Answer | Explanation |
|----------|--------|-------------|
| (a) Max keys per node | **3** | Order M → max M−1 = 3 keys |
| (b) Min children for non-root internal node | **2** | Min children = ⌈M/2⌉ = ⌈4/2⌉ = 2 |
| (c) All leaves at same level | **True** | B-trees always grow/shrink from the root — leaves stay at the same depth |
| (d) Height decreases when root splits | **False** | When the root splits, the tree height **increases by 1** — a new root is created above the split |

</details>

---

## Question 7 — 3 pts
### B-Tree Insertion

Consider inserting key **25** into the following order-3 (2-3 tree) node structure. The leaf node targeted is:

```
[20, 30]  ← this node receives 25
```

This node already has 2 keys (the maximum for order-3). What happens?

- A) 25 is inserted at the end: [20, 30, 25], and the node is left as-is
- B) The node overflows to [20, 25, 30]; the median (25) is pushed up to the parent; the node splits into [20] and [30]
- C) 25 replaces 20 because it is smaller than 30
- D) The node borrows a key from a sibling instead of splitting

---

<details>
<summary>Answer</summary>

**Correct: B**

When a node receives more keys than the maximum (M−1), it **overflows**. The fix is:
1. Temporarily hold all keys: [20, 25, 30]
2. The **median** (25) is pushed up to the parent
3. The remaining keys split into two nodes: [20] (left) and [30] (right)

If the parent also overflows after receiving 25, the same process repeats up the tree. If the root overflows and splits, the tree grows taller by one level.

**Borrowing** only applies during **deletion** (to fix underflow), not insertion.

</details>

---

## Question 8 — 4 pts
### Priority Queue / Binary Heap — Complexities and Concepts

Match each operation or statement to the correct complexity or answer:

| Operation / Statement | Answer |
|-----------------------|--------|
| `Insert()` into a max-heap of N elements | ? |
| `ExtractMax()` from a max-heap of N elements | ? |
| `Peek()` (view max without removing) | ? |
| `BuildHeap()` from N unsorted elements | ? |
| Parent of node at index `i` (0-based array) | ? |
| Left child of node at index `i` (0-based array) | ? |

**Options for complexities:** `O(1)`, `O(log N)`, `O(N)`, `O(N log N)`
**Options for index formulas:** `(i-1)/2`, `2i+1`, `2i+2`, `i/2`, `i-1`

---

<details>
<summary>Answers</summary>

| Operation / Statement | Answer | Explanation |
|-----------------------|--------|-------------|
| `Insert()` | **O(log N)** | Add at end, bubble up — height of heap is log N |
| `ExtractMax()` | **O(log N)** | Swap root with last, remove, bubble down — height of heap is log N |
| `Peek()` | **O(1)** | Root is always at index 0 — constant time access |
| `BuildHeap()` | **O(N)** | Despite N heapify calls, most nodes are near the bottom and do little work; the sum telescopes to O(N) |
| Parent of index i | **(i-1)/2** | Integer division |
| Left child of index i | **2i+1** | Standard 0-based heap formula |

**Common exam trap:** BuildHeap is **O(N)**, not O(N log N). The O(N log N) figure is for **HeapSort**, which does BuildHeap O(N) + N ExtractMax calls each O(log N).

</details>

---

## Quick Reference — All Topics

### Red-Black Tree Insertion Cases
| Situation | Fix |
|-----------|-----|
| Uncle is **red** | Recolor parent + uncle → black, grandparent → red; recurse up |
| Uncle is **black**, node is **outer** child (zig-zig shape) | Rotate grandparent; swap colors of parent & grandparent |
| Uncle is **black**, node is **inner** child (zig-zag shape) | Rotate parent toward grandparent; then apply outer-child case |

### LLRB Fixes (apply in order, bottom-up)
```
1. Right child red, left child black  →  ROTATE LEFT
2. Left child red AND left-left red   →  ROTATE RIGHT
3. Both children red                  →  FLIP COLORS
```

### Splay Cases
| Shape | Case | Rotation Order |
|-------|------|---------------|
| Parent is root | Zig | Single rotation on parent |
| Same direction (LL or RR) | Zig-Zig | Rotate **grandparent** first, then parent |
| Opposite direction (LR or RL) | Zig-Zag | Rotate **parent** first, then grandparent |

### B-Tree (Order M) Key Numbers
- Max keys: **M − 1**
- Min keys (non-root): **⌈M/2⌉ − 1**
- Min children (non-root internal): **⌈M/2⌉**

### Heap Array (0-indexed)
```
Parent(i)      = (i - 1) / 2
LeftChild(i)   = 2i + 1
RightChild(i)  = 2i + 2
```

### Heap BubbleDown (for review)
```cpp
void BubbleDown(int i) {
    int largest = i;
    int left  = 2*i + 1;
    int right = 2*i + 2;
    if (left  < size && data[left]  > data[largest]) largest = left;
    if (right < size && data[right] > data[largest]) largest = right;
    if (largest != i) {
        swap(data[i], data[largest]);
        BubbleDown(largest);
    }
}
```
> **Note:** Always compare with **both** children and swap with the **larger** one (for max-heap).
