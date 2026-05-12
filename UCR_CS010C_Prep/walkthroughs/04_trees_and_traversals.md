# Trees & Traversals — Deep Walkthrough

## What Is a Tree?

A tree is a hierarchical data structure where each node has exactly one parent (except the root, which has none) and zero or more children.

```
            A          ← root
           / \
          B   C        ← internal nodes
         / \ / \
        D  E F  G      ← D, F are leaves; E, G have children
          / \   \
         I   J   K     ← leaves
```

---

## Terminology (every definition matters on exams)

| Term | Definition | Example (tree above) |
|------|-----------|----------------------|
| **Root** | Node with no parent | A |
| **Leaf** | Node with no children | D, I, J, F, K |
| **Internal node** | Node with at least one child | A, B, C, E, G |
| **Parent** | Node directly above | B is parent of D, E |
| **Child** | Node directly below | D and E are children of B |
| **Siblings** | Nodes sharing the same parent | D and E are siblings; F and G are siblings (same parent C) |
| **Ancestor** | Any node on path from root to that node | A, B are ancestors of I |
| **Descendant** | Any node reachable downward | I, J, E are descendants of B |
| **Depth of node** | Number of edges from root to that node | depth(A)=0, depth(B)=1, depth(I)=3 |
| **Level** | Depth + 1 (1-based) | A is level 1, B is level 2 |
| **Height of node** | Edges on longest path from node to a leaf | height(A)=3, height(E)=1, height(I)=0 |
| **Height of tree** | Height of root | 3 |
| **Path** | Sequence of nodes connected by edges | A→B→E→I |
| **Path length** | Number of edges in the path | path(I, B) has length 2 (I→E→B) |

### Common Confusion: Depth vs Height vs Level

```
Node A: depth=0, level=1, height=3
Node B: depth=1, level=2, height=2
Node I: depth=3, level=4, height=0  ← leaf, height is always 0
```

- Depth counts DOWN from root
- Height counts UP from the lowest descendant leaf
- Level = Depth + 1 (1-indexed from root)

---

## Binary Tree Types

A **binary tree** has at most 2 children per node (left and right).

### Full Binary Tree
Every node has exactly **0 or 2** children. No node has exactly 1 child.
```
     1
    / \
   2   3
  / \
 4   5
```
✓ Full: 1 has 2 children, 2 has 2 children, 3/4/5 are leaves (0 children).

```
     1
    / \
   2   3
  /
 4
```
✗ Not full: node 2 has exactly 1 child.

### Complete Binary Tree
All levels are **fully filled** except possibly the last, which is filled **left-to-right**.
```
      1
    /   \
   2     3
  / \   /
 4   5 6
```
✓ Complete: last level filled left-to-right (6 is to the left).

```
      1
    /   \
   2     3
  / \     \
 4   5     7
```
✗ Not complete: 7 is a right child with no left sibling at that level.

### Perfect Binary Tree
ALL internal nodes have exactly 2 children AND all leaves are at the **same depth**.
```
      1
    /   \
   2     3
  / \   / \
 4   5 6   7
```
✓ Perfect: all leaves (4,5,6,7) are at depth 2.

**Relationship:** Perfect ⊂ Complete ⊂ Full (every perfect is complete is full, but not vice versa).

### Quick Test
- Remove node 9 from `[1→2,3; 2→4,5; 4→8,9; 3→6,7]`: is it complete?
  - Without 9: node 4 has only left child 8 → still filled left-to-right ✓ Complete
- Remove node 8 instead: is it complete?
  - Without 8: node 4 has only right child 9 → right child with no left sibling ✗ NOT complete

---

## The Four Traversals

Given this tree for all examples:
```
        1
       / \
      2   3
     / \ / \
    4  5 6  7
   / \
  8   9
```

### Pre-order (Root → Left → Right)
Visit root FIRST, then recurse left, then recurse right.
```
1, 2, 4, 8, 9, 5, 3, 6, 7
```
Memory trick: **PRE** = root is **before** its children.

```cpp
void PreOrder(Node* n) {
    if (!n) return;
    visit(n);          // root first
    PreOrder(n->left);
    PreOrder(n->right);
}
```

### In-order (Left → Root → Right)
Recurse left, visit root, recurse right.
```
8, 4, 9, 2, 5, 1, 6, 3, 7
```
On a BST, in-order gives you elements in **sorted order**. Memory trick: **IN** = root is **in between** children.

```cpp
void InOrder(Node* n) {
    if (!n) return;
    InOrder(n->left);
    visit(n);          // root in middle
    InOrder(n->right);
}
```

### Post-order (Left → Right → Root)
Recurse left, recurse right, visit root last.
```
8, 9, 4, 5, 2, 6, 7, 3, 1
```
Memory trick: **POST** = root is **after** its children. Useful for deletion (delete children before parent).

```cpp
void PostOrder(Node* n) {
    if (!n) return;
    PostOrder(n->left);
    PostOrder(n->right);
    visit(n);          // root last
}
```

### Level-order (BFS — row by row)
Visit all nodes at depth 0, then depth 1, then depth 2, etc.
```
1, 2, 3, 4, 5, 6, 7, 8, 9
```
Uses a **queue** (not recursion).

```cpp
void LevelOrder(Node* root) {
    Queue<Node*> q;
    q.Push(root);
    while (!q.Empty()) {
        Node* cur = q.Top(); q.Pop();
        visit(cur);
        if (cur->left)  q.Push(cur->left);   // push left first
        if (cur->right) q.Push(cur->right);
    }
}
```

If you push **right first** instead of left, the sequence reverses within each level:
```
Right-first: 1, 3, 2, 7, 6, 5, 4, 9, 8
```

---

## Traversal Identification Trick

Given a sequence, how do you identify the traversal?

1. Is the root (value 1) first? → **Pre-order**
2. Is the root last? → **Post-order**
3. Is the root in the middle with sorted subtrees on each side? → **In-order** (on a BST)
4. Do nodes appear level by level? → **Level-order**

**Example:** Sequence `8, 9, 4, 5, 2, 6, 7, 3, 1` → root (1) is last → **Post-order**

---

## Key Takeaways

1. Depth = edges from root down; Height = edges to furthest leaf below; Level = Depth + 1
2. Leaf height = 0; NIL height = -1 (used in AVL calculations)
3. Full: 0 or 2 children. Complete: filled left-to-right. Perfect: all leaves same depth.
4. Pre: root first. In: root middle. Post: root last. Level: BFS row by row.
5. In-order on a BST always yields a sorted sequence.
6. Level-order uses a queue; the other three use recursion (or an explicit stack).
