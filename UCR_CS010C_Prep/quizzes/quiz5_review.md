# Quiz 5 Review — CS 010C
**Topic:** BST (LCA, Deletion, Complexity) · AVL Trees · Balance Factors · Rotations
**Score: 18.38 / 28 (65.6%)**

---

## Question 1 — 3/5 ✗ (partial)
**LCA (Lowest Common Ancestor) calls on this BST:**
```
        42
       /  \
      21   84
     / \  /
    10 35 70
   /       \
  5        75
```

**LCA algorithm in a BST:** Start at root. If both values are less than current node → go left. If both are greater → go right. Otherwise (they split, or one equals current) → current node is the LCA.

| Call | Your Answer | Correct | Explanation |
|------|-------------|---------|-------------|
| LCA(10, 35) | 21 | **21** ✓ | 10 < 21 and 35 > 21 → they split at 21 |
| LCA(70, 75) | Exception | **70** ✗ | 75 is in the right subtree of 70, so 70 IS the LCA of itself and its descendant |
| LCA(5, 21) | Exception | **21** ✗ | 21 is an ancestor of 5 AND is 21 itself → LCA = 21 |
| LCA(50, 84) | Exception | **Exception** ✓ | 50 is not in the BST → error |
| LCA(21, 84) | 42 | **42** ✓ | 21 < 42 and 84 > 42 → split at 42 |

**Key rule:** If one of the two nodes IS an ancestor of the other, the ancestor IS the LCA — it's not an error.

---

## Question 2 — 3/3 ✓
**Level-order traversal with right child pushed to queue first:**

Tree:
```
        10
       /  \
      6    15
     / \  /  \
    4   8 12  18
```

Normal level-order (left first): 10, 6, 15, 4, 8, 12, 18
Right-first level-order: **10, 15, 6, 18, 12, 8, 4** ✓

**Why:** Pushing right child before left reverses the order within each level.

---

## Question 3 — 1.5/3 ✗ (partial)
**BST operation complexities (starting from a balanced BST of 100 items):**

| Operation | Context | Correct Complexity | Explanation |
|-----------|---------|-------------------|-------------|
| `Print()` | After 100 random insertions | **O(N)** | Print visits every node exactly once — always O(N) regardless of balance |
| `Print()` | After random insert/delete pairs | **O(N)** | Still visits every node |
| `Max()` | After 100 random insertions | **O(lg N)** | Random insertions keep tree roughly balanced; Max follows rightmost path |
| `Max()` | After random insert/delete pairs | **O(N)** | Insert/delete pairs (especially inserting then deleting repeatedly) can skew the tree, degrading to O(N) |
| `Insert()` | After 100 random insertions | **O(lg N)** | Tree remains roughly balanced |
| `Insert()` | After random insert/delete pairs | **O(N)** | Tree may become unbalanced → O(N) worst case |

**Key insight:** Random insertions keep a BST roughly balanced (height ~lg N). But repeated insert/delete pairs (Hibbard deletion in particular) can skew the tree, causing height to drift toward O(√N) or O(N).

---

## Question 4 — 3/3 ✓
**BST deletion: remove node 3 from the tree below:**
```
        8
       / \
      3   10
     / \    \
    1   6   14
       / \  /
      4   7 13
```

**BST Remove strategy from lecture:** Replace with the **in-order successor** = minimum node of the right subtree.

- Node 3's right subtree: rooted at 6
- Min of that subtree: **4** (leftmost node)
- Replace 3 with 4, then delete node 4 (which is a leaf → simply remove)

**Correct result (Option A):**
```
        8
       / \
      4   10
     / \    \
    1   6   14
         \  /
          7 13
```

---

## Question 5 — 1.88/5 ✗ (partial)
**Balance factors for this BST:**
```
        25
       /  \
      10   30
     / \     \
    5  15    40
        \      \
        20     50
```

**Balance factor = height(left subtree) − height(right subtree)**

> Leaf nodes have height 0. Empty subtrees have height -1.

| Node | Left Height | Right Height | Balance Factor | Correct |
|------|-------------|--------------|----------------|---------|
| 5 | -1 | -1 | **0** | ✓ |
| 20 | -1 | -1 | **0** | ✓ |
| 50 | -1 | -1 | **0** | ✓ |
| 15 | -1 | 0 (node 20) | **-1** | (right heavy) |
| 40 | -1 | 0 (node 50) | **-1** | (right heavy) |
| 10 | 0 (node 5) | 1 (15→20) | **-1** | (right heavy) |
| 30 | -1 | 1 (40→50) | **-2** | (right heavy, unbalanced!) |
| 25 | 2 (10→15→20) | 2 (30→40→50) | **0** | (balanced) |

**Common mistake:** Getting the sign wrong. Balance factor = LEFT − RIGHT. If the right side is taller, the balance factor is **negative**.

---

## Question 6 — 0/3 ✗
**What additional property does each AVL tree node store compared to a BST node?**

- Your answer: Balance factor
- **Correct answer: Height**

**Why:** The implementation stores the **height** of each node. The balance factor is then *computed* as `height(left) − height(right)` when needed. Storing height is simpler to maintain during rotations (just recompute from children's heights). Storing balance factor directly would require updating multiple ancestors on every rotation.

---

## Question 7 — 3/3 ✓
**AVL rebalancing: tree with root=15, left subtree rooted at 7 (7→right=9→right=12), right subtree rooted at 22.**

Node 7 has balance factor −2 (right-heavy). Node 9 has balance factor −1 (right-heavy).

**Case: Right-Right → Left rotation between 7 and 9**

After rotation: 9 becomes the new left child of 15, with 7 as its left child and 12 as its right child. ✓

---

## Question 8 — 3/3 ✓
**Insert 55 into this AVL tree:**
```
      30
     /  \
    20   50
   / \     \
  10 25    60
```

After inserting 55: 60 now has a left child (55). Node 50's right subtree (60→55) is right-left heavy.

**Case: Right-Left → Right rotation (55 and 60) then Left rotation (50 and 55)**

- Right rotate between 55 and 60: 55 becomes parent of 60
- Left rotate between 50 and 55: 55 becomes child of 30, 50 becomes 55's left child, 60 becomes 55's right child

**Correct answer:** Right rotation between 55 and 60, then left rotation between 50 and 55 ✓

---

## AVL Rotation Summary (Critical for Quiz 6)

| Imbalance Case | Balance Factors | Fix |
|----------------|-----------------|-----|
| Left-Left | Node: +2, Left child: +1 | Single **right** rotation |
| Right-Right | Node: −2, Right child: −1 | Single **left** rotation |
| Left-Right | Node: +2, Left child: −1 | **Left** rotate child, then **right** rotate node |
| Right-Left | Node: −2, Right child: +1 | **Right** rotate child, then **left** rotate node |

**Memory trick:** The case name tells you the shape; the fix is the opposite direction first (for double rotations), then the main rotation.

---

## Key Takeaways from Quiz 5
1. **LCA**: if one node is an ancestor of the other, the ancestor IS the LCA — no exception
2. **Balance factor = Left height − Right height** (negative = right-heavy)
3. **AVL stores height**, not balance factor — balance factor is computed on the fly
4. After insert/delete pairs, BST can degrade to O(N) — random insertions alone keep it O(log N)
5. BST Remove: replace with **in-order successor** (min of right subtree), then delete that leaf
6. Know all four AVL rotation cases and when to apply each
