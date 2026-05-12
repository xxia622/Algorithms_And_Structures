# Splay Trees — Deep Walkthrough

## The Core Idea

A splay tree is a self-adjusting BST with one rule:

> **Every time you access a node, bring it to the root.**

No colors. No heights. No balance factors. Just rotations — called **splaying**.

Why it works: frequently accessed nodes float to the top and stay cheap to reach. The restructuring that brings a deep node up also tends to flatten the tree, keeping future operations fast.

---

## The Splay Operation — 3 Cases

When splaying node X toward the root, look at X's parent P and grandparent G.

---

### Case 1 — Zig (P is the root)
X's parent is the root → one single rotation. Done.

**X is left child of root → Right rotate:**
```
    P (root)            X (root)
   / \         →       / \
  X   C               A   P
 / \                      / \
A   B                    B   C
```

**X is right child of root → Left rotate:**
```
  P (root)                X (root)
 / \         →           / \
A   X                   P   C
   / \                 / \
  B   C               A   B
```

---

### Case 2 — Zig-Zig (X and P are on the SAME side)

Both left children, or both right children. The path is straight (no bend).

**Rotate GRANDPARENT first, then PARENT.**

**Both left (right-right rotations):**
```
      G                P                X
     /                / \              / \
    P          →     X   G     →      A   P
   /                / \ / \              / \
  X                A  B B  C            B   G
 / \                                       / \
A   B                                     B   C
```

Cleaner picture:
```
      G                   X
     / \                 / \
    P   D               A   P
   / \        →            / \
  X   C                   B   G
 / \                          / \
A   B                        C   D
```

**Why not two zig steps?** Rotating P first (not G) on a pathological input gives O(N) amortized. Rotating G first is what achieves O(log N) amortized. This is THE key distinction.

---

### Case 3 — Zig-Zag (X and P are on OPPOSITE sides)

X is P's right child but P is G's left (or vice versa). The path bends.

**Rotate PARENT first, then GRANDPARENT.**
(Same structure as AVL's LR/RL rotation.)

```
      G                G                X
     / \              / \              / \
    P   D            X   D           P   G
   / \       →      / \       →     / \ / \
  A   X            P   C           A  B C  D
     / \          / \
    B   C        A   B
```

---

## Case Summary

| Case | Condition | Fix |
|------|-----------|-----|
| Zig | P is the root | Single rotation |
| Zig-Zig | X and P same side | Rotate G first, then P |
| Zig-Zag | X and P opposite sides | Rotate P first, then G |

After each step, X is now 2 levels higher. Repeat until X is the root.

---

## Full Example — Splay on a Chain

Insert 1-5 in order → degenerate right chain:
```
1
 \
  2
   \
    3
     \
      4
       \
        5
```

**Find(3) → splay 3 to root:**

3's parent = 2, grandparent = 1. Both are left children (3 is right of 2, 2 is right of 1) → **Zig-Zig (both right)**.

Rotate 1 left first:
```
  2
 / \
1   3
     \
      4
       \
        5
```

Rotate 2 left:
```
    3
   / \
  2   4
 /     \
1       5
```

3 is now the root. The chain partially flattened.

---

## Operations

### Find(key)
```
1. BST search for key
2. Splay the found node to root (or last visited node if not found)
3. Return root's value (or null if not found)
```

After a failed search, the last visited node is splayed. This is useful — the tree restructures around the neighborhood of the search.

### Insert(key)
```
1. BST insert (as a leaf)
2. Splay the new node to root
```

### Delete(key)
```
1. Splay key to root (key must exist)
2. Split: left subtree L = everything < key, right subtree R = everything > key
3. Find max of L (splay it to root of L — it has no right child)
4. Set max(L)'s right child = R
5. Done — key is gone
```

```
Step 1: Splay 3 to root        Step 2: Split            Step 3: Splay max(L)=2  Step 4: Attach R
      3                        L=  2    R=  4               2
     / \               →          /        \        →      /         +    4
    2   4                         1          5             1               \
   /     \                                                                  5
  1       5                                                Result:
                                                               2
                                                              / \
                                                             1   4
                                                                  \
                                                                   5
```

---

## Why Zig-Zig Must Rotate Grandparent First

Consider a left-leaning chain: N → N-1 → ... → 2 → 1 (each is a left child).

**Two zig steps** (rotate parent, then grandparent — naive approach):

Accessing node 1 repeatedly:
- Each access moves 1 up by only 2 levels
- Tree height stays ~N/2 after access
- M accesses on this pattern: O(M × N) = O(MN). Amortized O(N) per op.

**Zig-zig** (rotate grandparent first):

Accessing node 1:
- The zig-zig step restructures the tree more aggressively
- After splaying 1 to root, the tree's height roughly halves
- Mathematically proven: M operations take O(M log N) total. Amortized O(log N) per op.

---

## Complexity

| Operation | Single worst case | Amortized |
|-----------|------------------|-----------|
| Find | O(N) | O(log N) |
| Insert | O(N) | O(log N) |
| Delete | O(N) | O(log N) |
| M operations total | O(MN) worst | **O(M log N)** |

Amortized analysis uses a potential function Φ = Σ log(size of subtree rooted at each node). Heavy nodes cost more to splay but decrease Φ, paying for future cheap operations.

---

## Splay Trees vs AVL vs RBT

| Property | Splay | AVL | RBT |
|----------|-------|-----|-----|
| Balance guarantee | Amortized O(log N) | Worst-case O(log N) | Worst-case O(log N) |
| Stored per node | Nothing extra | Height | Color |
| Best for | Repeated accesses (cache-friendly) | Read-heavy | Write-heavy |
| Recently accessed items | O(1) in practice | O(log N) always | O(log N) always |

---

## Key Takeaways

1. Every access splays the node to the root — no extra storage needed
2. Three cases: **Zig** (parent is root → single rotate), **Zig-Zig** (same side → rotate G then P), **Zig-Zag** (opposite side → rotate P then G)
3. Zig-zig MUST rotate grandparent first — rotating parent first gives O(N) amortized
4. Failed search → splay the **last visited node** to root
5. Amortized O(log N) per operation; individual ops can be O(N)
6. Best when access pattern has locality — hot items stay near root
