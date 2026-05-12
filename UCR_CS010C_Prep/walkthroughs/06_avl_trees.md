# AVL Trees — Deep Walkthrough

## Why AVL?

A plain BST degenerates to O(N) with sorted insertions. AVL trees enforce a strict balance condition so height stays O(log N) always — guaranteed, not just on average.

Named after Adelson-Velsky and Landis (1962) — the first self-balancing BST ever invented.

---

## The Balance Condition

Every node stores its **height** (longest path down to a leaf).

**Balance factor** = height(left subtree) − height(right subtree)

An AVL tree requires: **balance factor ∈ {-1, 0, +1}** for every node.

```
height of empty subtree = -1
height of leaf = 0
height of node = 1 + max(height(left), height(right))
```

**Important:** AVL stores **height**, not balance factor. Balance factor is computed on the fly from heights.

```
      8  (height=3, bf=0)
     / \
    3   10  (height=1, bf=0)
   / \    \
  1   6   14  (height=0, bf=0)
```

---

## Balance Factor Examples

```
        25  (bf = height(left) - height(right) = 2 - 2 = 0)
       /  \
      10   30  (bf = 1 - 1 = 0)    (bf = -1 - 1 = -2) ← UNBALANCED
     / \     \
    5  15    40  (bf = -1 - 0 = -1)
        \      \
        20     50
```

Computing node 10's balance factor:
- left subtree (5): height = 0
- right subtree (15→20): height = 1
- bf = 0 - 1 = **-1** (right-heavy, but within range)

Computing node 30's balance factor:
- left subtree: empty → height = -1
- right subtree (40→50): height = 1
- bf = -1 - 1 = **-2** → UNBALANCED, needs rebalancing

---

## The Four Rotation Cases

When a node's balance factor reaches ±2 after insertion, you apply one of four fixes.

The case is determined by:
1. Which side is heavy (left: bf=+2, right: bf=-2)
2. Which side the child is heavy on

### Case 1: Left-Left (LL) — Right Rotation

Node is left-heavy (+2), left child is also left-heavy (+1).

```
      C  bf=+2              B
     /                     / \
    B  bf=+1      →       A   C
   /
  A
```

**Right rotate on C:** B moves up, C moves down-right, B's old right child (if any) becomes C's left child.

### Case 2: Right-Right (RR) — Left Rotation

Node is right-heavy (-2), right child is also right-heavy (-1).

```
  A  bf=-2                  B
   \                       / \
    B  bf=-1      →       A   C
     \
      C
```

**Left rotate on A:** B moves up, A moves down-left.

### Case 3: Left-Right (LR) — Left then Right Rotation

Node is left-heavy (+2), left child is right-heavy (-1). The path bends (zig-zag left).

```
    C  bf=+2         C  bf=+2           B
   /                /                  / \
  A  bf=-1  →     B          →        A   C
   \             /
    B           A
```

**Step 1:** Left rotate on A → straightens the zig-zag
**Step 2:** Right rotate on C → same as LL case

### Case 4: Right-Left (RL) — Right then Left Rotation

Node is right-heavy (-2), right child is left-heavy (+1). The path bends (zig-zag right).

```
  A  bf=-2         A  bf=-2              B
   \                \                   / \
    C  bf=+1  →      B          →      A   C
   /                  \
  B                    C
```

**Step 1:** Right rotate on C → straightens the zig-zag
**Step 2:** Left rotate on A → same as RR case

---

## Rotation Summary Table

| bf of node | bf of heavy child | Case | Fix |
|------------|------------------|------|-----|
| +2 | +1 or 0 | Left-Left | Right rotate node |
| -2 | -1 or 0 | Right-Right | Left rotate node |
| +2 | -1 | Left-Right | Left rotate child, Right rotate node |
| -2 | +1 | Right-Left | Right rotate child, Left rotate node |

**Memory trick:** The case name is the shape of the imbalance. The fix always involves rotating toward the opposite direction of the heavy side.

---

## Full Insertion Example

Insert 1, 2, 3, 4, 5 into an AVL tree:

**Insert 1:** `[1]` — balanced

**Insert 2:**
```
  1 (bf=-1)
   \
    2
```
Balanced. bf=-1 is fine.

**Insert 3:**
```
  1 (bf=-2) ← UNBALANCED
   \
    2 (bf=-1)
     \
      3
```
Right-Right case → Left rotate on 1:
```
    2
   / \
  1   3
```
All bf=0. ✓

**Insert 4:**
```
    2 (bf=-1)
   / \
  1   3 (bf=-1)
       \
        4
```
Balanced. ✓

**Insert 5:**
```
    2 (bf=-2) ← UNBALANCED
   / \
  1   3 (bf=-2) ← also -2 but fix starts at lowest unbalanced
       \
        4 (bf=-1)
         \
          5
```
Lowest unbalanced node = 3. Right-Right → Left rotate on 3:
```
    2 (bf=-1)
   / \
  1   4
     / \
    3   5
```
Balanced. ✓

---

## Complexity

| Operation | Complexity |
|-----------|------------|
| Find | O(log N) |
| Insert | O(log N) |
| Remove | O(log N) |
| Height | O(log N) always — guaranteed |

AVL guarantees O(log N) height because:
- Balance factor ∈ {-1, 0, +1} at every node
- This bounds height to ~1.44 log₂(N) in the worst case

---

## AVL vs BST vs RBT

| Property | BST | AVL | Red-Black |
|----------|-----|-----|-----------|
| Balance guarantee | None | Strict (≤1.44 log N) | Looser (≤2 log N) |
| Stored per node | key, children | key, children, **height** | key, children, **color** |
| Rotations per insert | 0 | At most 2 | At most 2 |
| Rotations per delete | 0 | O(log N) | At most 3 |
| Best for | Static data | Read-heavy | Write-heavy |

---

## Key Takeaways

1. AVL stores **height** in each node, NOT the balance factor
2. Balance factor = height(left) − height(right). Valid range: {-1, 0, +1}
3. Empty subtree has height -1; leaf has height 0
4. **Positive** bf = left-heavy. **Negative** bf = right-heavy
5. LL/RR: single rotation. LR/RL: double rotation (fix child first, then node)
6. After any insertion, update heights and check balance factors bottom-up
