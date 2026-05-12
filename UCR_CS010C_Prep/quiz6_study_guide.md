# Quiz 6 Study Guide — CS 010C

**Topics:** Red-Black Trees · Left-Leaning Red-Black Trees · Splay Trees · B-Trees · Priority Queue / Binary Heap

---

## 1. Red-Black Trees (RBT)

### The 5 Properties (memorize these)
1. Every node is **red** or **black**
2. The **root** is always **black**
3. Every **NIL leaf** is **black**
4. If a node is **red**, both its children are **black** (no two consecutive reds)
5. All paths from any node to its descendant NIL leaves have the **same number of black nodes** (black-height)

### Key Facts
- Height is at most **2 log(N+1)** → all operations O(log N) guaranteed
- Insertion always starts by adding a **red** node
- After insertion you may need: **recoloring** and/or **rotations**

### Insertion Cases (after adding a red node)
| Case | Situation | Fix |
|------|-----------|-----|
| 1 | Uncle is **red** | Recolor parent + uncle → black, grandparent → red; move up |
| 2 | Uncle is **black**, node is **inner** child (zig-zag) | Rotate parent toward grandparent first, then apply Case 3 |
| 3 | Uncle is **black**, node is **outer** child (zig-zig) | Rotate grandparent, swap colors of parent & grandparent |

### Common Trick Questions
- "Is the root red after insertion?" → **No**, always recolor root black at the end
- "Can a red node have a red parent?" → **No** (violates property 4)
- "What's the black-height of a NIL node?" → **0**

---

## 2. Left-Leaning Red-Black Trees (LLRB)

### What Makes It Different
- Red links only appear on the **left** side
- Simpler implementation than standard RBT
- Corresponds 1-to-1 with **2-3 trees**

### Three Fixing Operations (applied bottom-up on insert)
```
1. Right child red, left child black  →  ROTATE LEFT
2. Left child red AND left-left red   →  ROTATE RIGHT
3. Both children red                  →  FLIP COLORS
```

### Insertion Walk-through Example
Insert 1, 2, 3 into an empty LLRB:
```
Insert 1: [1B]
Insert 2: right child is red → rotate left → [2B, left=1R]
Insert 3: right child is red → rotate left → [3B, left=2R]; left-left is red → rotate right → [2B, left=1R, right=3R]; both children red → flip colors → root recolored black
Final: [2B, left=1B, right=3B]
```

### Key Invariant
> In an LLRB, a 2-node = black node; a 3-node = black node with a red left child.

---

## 3. Splay Trees

### Core Idea
Every time you **access** a node (search, insert, delete), you **splay** it to the root using rotations. No color or height stored — self-adjusting BST.

### Three Splay Cases
| Case | When | Operation |
|------|------|-----------|
| **Zig** | Node's parent is the root | Single rotation (left or right) |
| **Zig-Zig** | Node and parent are both left (or both right) children | Rotate **grandparent** first, then **parent** |
| **Zig-Zag** | Node is left child, parent is right (or vice versa) | Rotate **parent** first, then **grandparent** |

### Zig-Zig vs Zig-Zag — the critical distinction
```
Zig-Zig (same direction):     Zig-Zag (opposite direction):
    G                               G
   /                               /
  P           rotate G, then P    P       rotate P, then G
 /                                  \
X                                    X
```

### Complexity
- Single operation: **O(N)** worst case
- Amortized over M operations: **O(M log N)**
- Recently accessed nodes stay near the root → excellent cache locality

### Common Questions
- "What does splay do after a find()?" → Brings the found node to the root
- "What if the key is not found?" → Splays the **last visited node** to the root
- "Why is zig-zig different from two zig steps?" → Zig-zig rotates the grandparent first, which is necessary to achieve O(log N) amortized (two zig steps would give O(N) amortized for pathological inputs)

---

## 4. B-Trees

### Definition — Order M B-tree
- Every node has **at most M children** (M−1 keys)
- Every **non-root** node has **at least ⌈M/2⌉ children**
- Root has **at least 2 children** (if it is not a leaf)
- All **leaves are at the same level**
- A node with k children has **k−1 keys**

### Common Variants
| Name | Order | Keys per node | Children per node |
|------|-------|---------------|-------------------|
| 2-3 tree | 3 | 1–2 | 2–3 |
| 2-3-4 tree | 4 | 1–3 | 2–4 |

### Insertion
1. Find the correct leaf, insert the key there
2. If node **overflows** (has M keys): **split** — push the median key up to the parent
3. Repeat up the tree if the parent also overflows
4. If the **root splits**, tree height increases by 1

### Example: Inserting into a full 2-3 tree node
```
Node [3, 7] receives key 5:
→ [3, 5, 7]  (overflow — 3 keys in an order-3 node)
→ Split: median 5 goes to parent; children become [3] and [7]
```

### Deletion
- **Leaf node**: remove directly
- **Internal node**: replace with in-order predecessor/successor, then delete that leaf
- **Underflow** (too few keys): **borrow** from a sibling or **merge** with a sibling + parent key

### Why B-Trees?
- Designed for **disk storage** — each node fits in one disk block, minimizing I/O
- Height is O(log_M N) — extremely shallow for large M (e.g., M=1000 → height ≤ 3 for millions of keys)

---

## 5. Priority Queue / Binary Heap

### Priority Queue ADT
- `Insert(item)` — add an element with a priority
- `ExtractMax()` / `ExtractMin()` — remove and return the highest-priority element
- `Peek()` — view highest-priority element without removing

### Binary Max-Heap Properties
1. **Complete binary tree** (all levels full except possibly the last, filled left-to-right)
2. **Heap property**: every parent ≥ its children

### Array Representation (0-indexed)
```
Parent of i:       (i - 1) / 2
Left child of i:   2i + 1
Right child of i:  2i + 2
```

### Operations & Complexity
| Operation | How | Complexity |
|-----------|-----|------------|
| Insert | Add at end, **bubble up** (swap with parent while larger) | O(log N) |
| ExtractMax | Swap root ↔ last element, remove last, **bubble down** | O(log N) |
| Peek | Return root | O(1) |
| BuildHeap | Call heapify from bottom up (n/2 → 0) | **O(N)** |

> **Common mistake:** BuildHeap is O(N), NOT O(N log N). The O(N log N) figure applies to HeapSort (which also does N extractions on top of the build).

### Bubble Up vs Bubble Down
```
Bubble Up   (Insert):   compare with parent → swap if node > parent
Bubble Down (Extract):  compare with BOTH children → swap with the LARGER child
```

---

## Practice Questions

**Q1.** Which of these violates a Red-Black Tree property?
- a) Root is black
- b) Red nodes must have black children
- c) All paths to NIL have the same number of **total** nodes
- d) NIL leaves are black

> **Answer: c** — It's the number of **black** nodes that must be equal, not total nodes.

**Q2.** In an LLRB tree, when do you flip colors?
- a) Left child is red
- b) Right child is red
- c) Both children are red
- d) Neither child is red

> **Answer: c** — Both children being red corresponds to a 4-node in a 2-3-4 tree; flipping colors pushes the "split" up.

**Q3.** In a splay tree, after searching for a key that does NOT exist, what happens?
- a) Nothing changes
- b) The last node visited is splayed to the root
- c) The tree is rebuilt from scratch
- d) An exception is thrown

> **Answer: b** — The splay operation always runs on the last accessed node, even if the target wasn't found.

**Q4.** In a 2-3-4 tree (order 4), what is the minimum number of children a non-root internal node must have?
- a) 1
- b) 2
- c) 3
- d) 4

> **Answer: b** — Minimum children = ⌈M/2⌉ = ⌈4/2⌉ = 2.

**Q5.** What is the time complexity of BuildHeap on N elements?
- a) O(N log N)
- b) O(N²)
- c) O(N)
- d) O(log N)

> **Answer: c** — O(N). Even though individual heapify calls are O(log N), most nodes are near the bottom and do very little work. The sum telescopes to O(N).

**Q6.** In a max-heap stored as an array (0-indexed), where is the parent of the node at index 7?
- a) Index 2
- b) Index 3
- c) Index 6
- d) Index 14

> **Answer: b** — Parent of i = (7 - 1) / 2 = 3 (integer division).
