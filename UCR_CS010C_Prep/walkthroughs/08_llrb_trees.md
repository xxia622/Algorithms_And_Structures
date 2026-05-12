# Left-Leaning Red-Black Trees (LLRB) — Deep Walkthrough

## What Makes LLRB Different?

Standard RBTs are powerful but have many cases to handle. LLRB is a restriction of RBT with one extra rule:

> **Red links only go LEFT.**

This restriction reduces the number of structural cases from ~40 to just 3, making implementation significantly simpler.

---

## Correspondence with 2-3 Trees

Every LLRB tree maps 1-to-1 with a 2-3 tree (order-3 B-tree):

```
2-node (one key):     3-node (two keys):
    [B]                  [A|B]
   / \                   /|\
                         / | \

In LLRB:
    B(black)             B(black)
   / \                  /
                        A(red)
```

A black node with a red left child = a 3-node. This correspondence is why the algorithm works — you're just implementing a 2-3 tree in binary tree form.

---

## The Three Operations

Applied bottom-up after any insertion. Check and apply in this order:

### 1. Rotate Left
**When:** Right child is red, left child is black (or null).

Fixes a red link leaning right — LLRB invariant violation.
```
    X(B)                Y(B)
   /    \              /    \
  A    Y(R)   →     X(R)    C
      /    \        /    \
     B      C      A      B
```

### 2. Rotate Right
**When:** Left child is red AND left-left grandchild is also red (two consecutive left reds).
```
      C(B)               B(B)
     /    \             /    \
   B(R)    D   →     A(R)   C(R)
   /                         \
 A(R)                         D
```
After rotating right, both children are now red → triggers flip colors.

### 3. Flip Colors
**When:** Both children are red.

Corresponds to splitting a 4-node in a 2-3-4 tree — push the middle key up.
```
      B(B)               B(R)   ← color propagates upward
     /    \             /    \
   A(R)  C(R)   →    A(B)  C(B)
```

---

## Insertion Algorithm

1. Insert new node as **red** (same as regular BST insert)
2. Walk back up, applying fixes at each level:
   - If right child red AND left child not red → **Rotate Left**
   - If left child red AND left-left red → **Rotate Right**
   - If both children red → **Flip Colors**
3. Force root to black

The three checks always happen in that order at every node on the way back up.

---

## Full Example — Insert 1, 2, 3, 4, 5

**Insert 1:**
```
[1B]   root → black
```

**Insert 2:** 2 > 1, becomes right child (red).
```
  1B
   \
   2R  ← right child is red → Rotate Left on 1
```
After left rotate:
```
  2B
 /
1R
```

**Insert 3:** 3 > 2, becomes right child of 2 (red).
```
  2B
 /  \
1R  3R  ← both children red → Flip Colors
```
After flip:
```
  2R   ← root → force black
 /  \
1B  3B
→
  2B
 /  \
1B  3B
```

**Insert 4:** 4 > 2 → right; 4 > 3 → right child of 3 (red).
```
  2B
 /  \
1B  3B
      \
      4R  ← right child red → Rotate Left on 3
```
After left rotate on 3:
```
  2B
 /  \
1B  4B
   /
  3R
```
Check 4: left child (3) is red, left-left (none) is not red → no right rotate needed. Done. ✓

**Insert 5:** 5 > 4 → right child of 4 (red).
```
  2B
 /  \
1B  4B
   /  \
  3R  5R  ← both children of 4 are red → Flip Colors on 4
```
After flip on 4:
```
  2B
 /  \
1B  4R   ← 4 is now red, check upward
   /  \
  3B  5B
```
Now at node 2: right child (4) is red, left child (1) is black → **Rotate Left on 2**.
```
    4B
   /  \
  2R   5B
 /  \
1B  3B
```
Check 4: left (2) is red, left-left (1) is black → no right rotate. Both children not both red → no flip. Done. ✓

Final tree:
```
    4B
   /  \
  2R   5B
 /  \
1B  3B
```

---

## Deletion — Brief Overview

Deletion in LLRB is done by temporarily allowing red-right nodes and 4-nodes, then fixing them on the way back up. The key insight:

- To delete a minimum: "borrow" a red node from the right before going left
- To delete any node: use the same approach recursively, then fix up on return

The fix-up on the way back is the same 3 operations (rotate left, rotate right, flip colors).

---

## Comparison: LLRB vs Standard RBT

| Property | Standard RBT | LLRB |
|----------|-------------|------|
| Red links | Left or right | Left only |
| Cases for insert | ~4 | 3 |
| Lines of code | ~100+ | ~30 |
| Corresponds to | 2-3-4 trees | 2-3 trees |
| Performance | Same | Same (same O complexity) |

---

## Key Takeaways

1. Extra rule beyond RBT: **red links lean left only**
2. Corresponds to 2-3 trees: black node = 2-node, black+red-left = 3-node
3. Three fixes in order: rotate left → rotate right → flip colors
4. Always insert as red; force root to black at end
5. Rotate Left: right child is red (illegal lean)
6. Rotate Right: left AND left-left are both red (two consecutive reds)
7. Flip Colors: both children are red (4-node → split and push up)
