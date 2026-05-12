# Binary Search Trees (BST) — Deep Walkthrough

## The BST Property

For every node N:
- All values in the **left subtree** are **strictly less than** N
- All values in the **right subtree** are **strictly greater than** N

This applies to the **entire subtree**, not just direct children — the most common mistake.

```
        8          ← valid BST
       / \
      3   10
     / \    \
    1   6   14
       / \
      4   7
```

```
        8          ← INVALID BST
       / \
      3   10
     / \
    1   9          ← 9 > 8 but is in the left subtree of 8!
```

---

## Search

```cpp
Node* Find(Node* root, int key) {
    if (!root || root->key == key) return root;
    if (key < root->key) return Find(root->left, key);
    else                 return Find(root->right, key);
}
```

At each node, half the tree is eliminated. On a balanced tree: **O(log N)**. On a degenerate (sorted-insertion) tree: **O(N)**.

---

## Insert

```cpp
Node* Insert(Node* root, int key) {
    if (!root) return new Node{key};
    if (key < root->key) root->left  = Insert(root->left, key);
    else                 root->right = Insert(root->right, key);
    return root;
}
```

Always insert as a **leaf**. Walk down the tree following BST order until you hit a null spot.

**Example — Insert 5 into the tree above:**
```
8 → go left (5<8)
3 → go right (5>3)
6 → go left (5<6)
4 → go right (5>4)
null → insert here
```

Result: 5 becomes the right child of 4.

---

## Remove — Three Cases

This is the most complex BST operation. When deleting node N:

### Case 1: N is a leaf
Simply remove it. Parent's pointer set to null.
```
Remove 4:       8
               / \
              3   10
             / \    \
            1   6   14
               / \
              X   7     ← 4 is gone
```

### Case 2: N has one child
Replace N with its only child.
```
Remove 10:      8
               / \
              3   14    ← 14 moved up to replace 10
             / \
            1   6
               / \
              4   7
```

### Case 3: N has two children
Replace N's value with its **in-order successor** (minimum of its right subtree), then delete that successor node.

Why in-order successor? It's the smallest value larger than N — placing it at N's position preserves the BST property.

```
Remove 3:
  In-order successor of 3 = min of right subtree of 3
  Right subtree of 3: rooted at 6
  Min of that subtree: 4 (leftmost node)
  
  Replace 3 with 4, then delete 4 (which is a leaf):
        8
       / \
      4   10    ← 3 replaced by 4
     / \    \
    1   6   14
           \
            7
```

```cpp
Node* Remove(Node* root, int key) {
    if (!root) throw std::out_of_range("Not found");
    if (key < root->key)
        root->left = Remove(root->left, key);
    else if (key > root->key)
        root->right = Remove(root->right, key);
    else {
        if (!root->left)  return root->right;   // case 1 or 2
        if (!root->right) return root->left;    // case 2
        // case 3: find in-order successor
        Node* successor = FindMin(root->right);
        root->key = successor->key;
        root->right = Remove(root->right, successor->key);
    }
    return root;
}

Node* FindMin(Node* n) {
    while (n->left) n = n->left;
    return n;
}
```

---

## Lowest Common Ancestor (LCA)

The LCA of nodes A and B is the deepest node that is an ancestor of both.

**Algorithm (exploits BST property):**

```cpp
int LCA(Node* root, int a, int b) {
    if (!root) throw std::runtime_error("Not found");
    if (a < root->key && b < root->key)
        return LCA(root->left, a, b);    // both in left subtree
    if (a > root->key && b > root->key)
        return LCA(root->right, a, b);   // both in right subtree
    // they split here (or one of them IS this node)
    // verify both exist before returning
    return root->key;
}
```

**Key rule:** If one of the two values IS a node on the path, that node IS the LCA — no exception.

**Example on this BST:**
```
        42
       /  \
      21   84
     / \  /
    10 35 70
   /       \
  5        75
```

| Call | Result | Why |
|------|--------|-----|
| LCA(10, 35) | 21 | 10<21 and 35>21 → split at 21 |
| LCA(5, 21) | 21 | Both ≤ 21; 21 is on the path and IS one of the targets |
| LCA(70, 75) | 70 | 75 is a descendant of 70; 70 itself is the LCA |
| LCA(50, 84) | error | 50 is not in the BST |
| LCA(21, 84) | 42 | 21<42 and 84>42 → split at 42 |

---

## Complexity Analysis

| Operation | Balanced (O(log N)) | Degenerate (O(N)) |
|-----------|---------------------|-------------------|
| Find | O(log N) | O(N) |
| Insert | O(log N) | O(N) |
| Remove | O(log N) | O(N) |
| Print (in-order) | **Always O(N)** | **Always O(N)** |
| Max/Min | O(log N) | O(N) |

**When does a BST degrade?**
- Inserting in sorted order (ascending or descending) → linked list shape → O(N) height
- Random insertions → expected height O(log N)
- Random insert/delete pairs → height can drift toward O(√N) over time (Hibbard deletion issue)

**Print is always O(N)** regardless of balance because it must visit every node exactly once.

---

## In-Order Gives Sorted Output

For any BST, in-order traversal visits nodes in ascending sorted order:
```
BST:    8
       / \
      3   10
     / \    \
    1   6   14

In-order: 1, 3, 6, 8, 10, 14   ← sorted!
```

---

## Key Takeaways

1. BST property applies to the entire subtree, not just immediate children
2. Search/Insert/Remove: O(log N) balanced, O(N) degenerate
3. Remove case 3: replace with in-order successor (min of right subtree), then delete it
4. LCA: if one target IS an ancestor of the other, that ancestor IS the LCA
5. In-order traversal always gives sorted output on a BST
6. Print is always O(N) — must visit all N nodes regardless of tree shape
