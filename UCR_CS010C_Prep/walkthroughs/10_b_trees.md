# B-Trees — Deep Walkthrough

## Why B-Trees?

Every data structure so far assumes nodes fit in RAM. What if your data is on disk?

A disk read fetches an entire **block** (~4KB–16KB). If each tree node = one block, you want to minimize the number of nodes you visit → minimize tree height → maximize the number of keys per node.

B-Trees solve this by putting **many keys in each node** — the tree stays very short even for billions of records.

---

## Definition — Order M B-Tree

1. Every node has **at most M children** (and at most M−1 keys)
2. Every **non-root** node has **at least ⌈M/2⌉ children** (at least ⌈M/2⌉−1 keys)
3. **Root** has at least 2 children if it's not a leaf
4. All **leaves are at the same level**
5. A node with k children has exactly **k−1 keys**

The keys in a node act like separators: for a node with keys [k1, k2, k3]:
- Child 0: values < k1
- Child 1: k1 < values < k2
- Child 2: k2 < values < k3
- Child 3: values > k3

---

## Common Variants

### 2-3 Tree (Order 3)
- 1 or 2 keys per node
- 2 or 3 children per internal node
- Min children: ⌈3/2⌉ = 2

```
Node types:
  2-node: [k1]      3-node: [k1|k2]
           / \               / | \
```

### 2-3-4 Tree (Order 4)
- 1, 2, or 3 keys per node
- 2, 3, or 4 children per internal node
- Min children: ⌈4/2⌉ = 2
- Corresponds to Red-Black Trees

---

## Search

Exactly like BST search, but at each node you scan through the keys:

```
At node with keys [k1, k2, ..., km]:
  if target < k1  → go to child 0
  if target == k1 → found!
  if k1 < target < k2 → go to child 1
  ...
  if target > km  → go to child m
```

Height of B-tree = O(log_M N), so search does O(log_M N) disk reads.

For M=1000: a tree of 1 billion records has height ≤ 3. Incredible.

---

## Insertion

1. Search for where the key belongs (always insert into a leaf)
2. Insert key into the leaf node
3. If the node now has M keys (overflow) → **split**

### Splitting a Node

When a node overflows (has M keys), split it:
- Take the **median** key (middle key)
- Left half stays as left node
- Right half becomes new right node
- Median gets **pushed up** to the parent

If the parent also overflows → split the parent. Propagate up. If the root splits → tree height increases by 1.

### Example: Insert into a 2-3 tree (M=3)

Start:
```
        [20]
       /     \
   [10]      [30|40]
```

**Insert 35:**
35 > 20 → go right. 30 < 35 < 40 → insert into [30|40] → [30|35|40] → OVERFLOW (3 keys in order-3 = M keys).

Split [30|35|40]:
- Median = 35
- Left = [30], Right = [40]
- Push 35 up to parent

```
        [20|35]
       /   |   \
   [10]  [30]  [40]
```

**Insert 25:**
25 > 20, 25 < 35 → go to middle child [30].
Insert 25 into [30] → [25|30]. No overflow.

```
        [20|35]
       /   |   \
   [10]  [25|30]  [40]
```

**Insert 5:**
5 < 20 → go to [10]. Insert → [5|10]. No overflow.

```
          [20|35]
         /   |   \
   [5|10]  [25|30]  [40]
```

**Insert 15:**
15 < 20 → go to [5|10]. Insert → [5|10|15] → OVERFLOW.
Split: median=10, left=[5], right=[15], push 10 up.

```
       [10|20|35]   ← root now has 3 keys (M-1 = 2 keys max for M=3)
       /  |  |  \      OVERFLOW at root!
     [5] [15][25|30][40]
```

Root overflow! Split root:
- Median = 20
- Left = [10], Right = [35]
- New root = [20], height increases by 1

```
              [20]
             /    \
          [10]    [35]
          / \     / \
        [5] [15] [25|30] [40]
```

---

## Deletion

Three cases, similar to BST but with the underflow concern:

### Case 1: Key is in a leaf with extra keys
Just delete it directly (node still has ≥ ⌈M/2⌉−1 keys).

### Case 2: Key is in an internal node
Replace with **in-order predecessor** (max of left subtree) or **in-order successor** (min of right subtree), then delete that key from the leaf.

### Case 3: Underflow (leaf now has too few keys)
After deletion, if a node has < ⌈M/2⌉−1 keys:

**Option A — Borrow from a sibling:**
If a sibling has an extra key, rotate a key through the parent:
```
Parent: [20]         Parent: [18]
       /    \    →          /    \
   [10|18]  [25]         [10]   [20|25]
```
(18 moves up to parent, 20 comes down to the deficient node)

**Option B — Merge with sibling:**
If no sibling has extra keys, merge the deficient node with a sibling and pull a key down from the parent:
```
Parent: [20]         Parent: (empty, or propagate up)
       /    \    →
   [10]    [25]            [10|20|25]
```
Then check parent for underflow and repeat upward.

---

## Height and Complexity

| Operation | Complexity |
|-----------|------------|
| Search | O(log_M N) |
| Insert | O(log_M N) |
| Delete | O(log_M N) |

For M=1000 and N=10⁹: height ≤ log_1000(10⁹) = 3. Three disk reads to find anything.

**Height formula:**
- Max height: O(log_⌈M/2⌉ N)
- Min height: O(log_M N)

---

## B-Tree vs BST vs AVL

| Property | BST | AVL | B-Tree (M=3) |
|----------|-----|-----|-------------|
| Keys per node | 1 | 1 | 1–2 |
| Height | O(N) worst | O(log N) | O(log N) |
| Designed for | RAM | RAM | Disk |
| Fan-out | 2 | 2 | 2–3 |

---

## Key Takeaways

1. Order M: max M children, max M−1 keys; min ⌈M/2⌉ children (non-root)
2. All leaves at same level — height grows only when root splits
3. Insert: find leaf, insert, split if overflow, push median up
4. Median goes UP on split; children go LEFT and RIGHT
5. Delete: if underflow → borrow from sibling first, merge if no sibling can lend
6. Height = O(log_M N) — very short for large M, perfect for disk storage
7. 2-3 tree = order 3; 2-3-4 tree = order 4 (equivalent to RBT)
