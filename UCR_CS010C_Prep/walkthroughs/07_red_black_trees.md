# Red-Black Trees — Deep Walkthrough

## Why Red-Black Trees?

AVL trees are strictly balanced but require O(log N) rotations on deletion. Red-Black Trees (RBT) use a looser balance condition, guaranteeing O(log N) with fewer rotations on average — making them faster for insert/delete-heavy workloads.

Used in: C++ `std::map` / `std::set`, Java `TreeMap`, Linux kernel process scheduler.

---

## The 5 Properties

1. Every node is **red** or **black**
2. The **root** is always **black**
3. Every **NIL leaf** is **black** (treat null pointers as black sentinel nodes)
4. If a node is **red**, both its children are **black** (no two consecutive reds)
5. All paths from any node to its descendant NIL leaves have the **same number of black nodes** (black-height)

Properties 4 + 5 together guarantee: height ≤ **2 log(N+1)**

- Property 5 → all paths have the same black count (say, `b`)
- Property 4 → between any two black nodes there's at most one red
- So longest path ≤ 2b, shortest path ≥ b → height bounded

---

## Rotations (same as AVL)

### Left Rotation on X
```
    X                Y
   / \              / \
  A   Y    →      X   C
     / \         / \
    B   C       A   B
```

### Right Rotation on Y
```
      Y              X
     / \            / \
    X   C    →    A   Y
   / \               / \
  A   B             B   C
```

Rotations preserve BST order — in-order traversal is unchanged.

---

## Insertion — Always Start Red

**Rule:** Always insert the new node as **RED**.

Why red? Adding a red node never violates Property 5 (black-count stays the same). It might violate Property 4 (double red). That's easier to fix.

After inserting, check if parent is red. If not — done. If yes — you have a double-red and must fix it.

Use this terminology:
- `N` = new node (red)
- `P` = parent (red — the problem)
- `G` = grandparent (must be black, since the tree was valid before)
- `U` = uncle (G's other child)

---

## Three Fixing Cases

### Case 1 — Uncle is RED → Recolor

```
        G(B)                G(R) ← push problem up
       /    \              /    \
      P(R)  U(R)   →    P(B)  U(B)
     /                  /
    N(R)               N(R)
```

Recolor P and U to black, G to red. Now repeat the check at G (G might be a double-red with its parent). If G is the root, just force it back to black.

### Case 2 — Uncle is BLACK, N is an inner child (Zig-Zag) → Rotate P

Inner child: P is G's left child but N is P's right child (or vice versa).

```
    G(B)             G(B)
   /                /
  P(R)    →        N(R)      ← now apply Case 3
   \              /
    N(R)         P(R)
```

Rotate P toward G (left rotate if N is P's right child). This converts zig-zag to zig-zig → fall into Case 3.

### Case 3 — Uncle is BLACK, N is an outer child (Zig-Zig) → Rotate G + Recolor

Outer child: both P and N are on the same side.

```
      G(B)                P(B)
     /                   /    \
    P(R)      →         N(R)   G(R)
   /
  N(R)
```

Right rotate G (P takes G's position). Swap colors: P becomes black, G becomes red. Done — no more double-red.

---

## Case Decision Tree

```
Insert N (red)
  ↓
Parent is black? → Done ✓
Parent is red (double-red):
  ↓
Look at uncle U:
  U is RED → Case 1: Recolor P+U→black, G→red. Move up to G. Repeat.
  U is BLACK or NIL:
    N is inner child? (zig-zag)
      YES → Case 2: Rotate P. Now zig-zig → Case 3.
      NO  → Case 3: Rotate G. Swap colors P↔G. Done ✓
```

---

## Full Example — Insert 10, 20, 30, 15, 25, 27

**Insert 10:** `[10B]` (root → black)

**Insert 20:** 20 > 10 → right child, red. Parent 10 is black → done.
```
  10B
    \
    20R
```

**Insert 30:** 30 > 20 → right child of 20, red. Parent 20 is red → double-red.
Uncle of 30 = left child of 10 = NIL (black). N(30) is outer child (right-right).
**Case 3:** Left rotate on 10, swap colors.
```
Before:   10B          After rotate+recolor:    20B
            \                                  /   \
            20R                              10R   30R
              \
              30R
```

**Insert 15:** 15 < 20 → left, 15 > 10 → right child of 10 (red). Parent 10 is red → double-red.
Uncle of 15 = 30 (red). **Case 1:** Recolor 10→black, 30→black, 20→red. 20 is root → force black.
```
    20B
   /   \
  10B  30B
    \
    15R
```

**Insert 25:** 25 > 20 → right, 25 < 30 → left child of 30 (red). Parent 30 is black → done.
```
    20B
   /   \
  10B  30B
    \  /
   15R 25R
```

**Insert 27:** 27 > 25 → right child of 25 (red). Parent 25 is red → double-red.
Uncle of 27 = NIL (black, left child of 30). N(27) is outer (right-right of 30).
Wait — P=25 is left child of 30, N=27 is right child of 25 → **zig-zag (inner child)**.
**Case 2:** Left rotate on 25. Then Case 3: right rotate on 30, swap colors.
```
After Case 2 (left rotate 25):
    20B
   /   \
  10B  30B
    \  /
   15R 27R
       /
      25R

After Case 3 (right rotate 30, recolor):
    20B
   /   \
  10B  27B
    \  /  \
   15R 25R 30R
```

---

## Deletion — Overview

1. Delete using BST rules (replace with in-order successor if 2 children)
2. If deleted node was **red** → done, no violation
3. If deleted node was **black** → one path lost a black node → fix with cases involving the sibling

Deletion cases are more complex than insertion. The key idea: a "double-black" placeholder marks the path that's short by one black. You resolve it by borrowing from the sibling or pushing the problem up.

---

## Complexity

| Operation | Complexity |
|-----------|------------|
| Find | O(log N) |
| Insert | O(log N), ≤ 2 rotations |
| Delete | O(log N), ≤ 3 rotations |
| Height | ≤ 2 log(N+1) |

---

## Key Takeaways

1. 5 properties — memorize them. Property 4 (no double-red) + Property 5 (equal black-height) enforce balance
2. Always insert as **red**
3. Fix is determined by the **uncle's color**: red → recolor (Case 1), black → rotate (Cases 2/3)
4. Case 2 (zig-zag): rotate parent first to get to Case 3
5. Case 3 (zig-zig): rotate grandparent, swap colors
6. After all insertions, root is always forced back to black
7. RBT stores **color** per node (1 bit); AVL stores **height** (integer)
