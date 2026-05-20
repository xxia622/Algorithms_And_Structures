# CS 10C MT2 — Cheatsheet & Personal Weak Spots

Built from the 2026-05-19 evening drill session. Order = exam priority. Drill the **Weak Spots** section first thing tomorrow morning.

---

## ⚠ MY WEAK SPOTS (drill these first)

### 1. Recursive code: forgot `return` in front of recursive calls
- `if (key < n->key) return Contains(n->left, key);` — **MUST have `return`**, otherwise result is thrown away
- Applies to Insert, Contains, FindMin, anything returning a value

### 2. BST Insert base case: NULL POINTER DEREF
- `if (n == nullptr) { n->key = key; }` → **CRASH** (n is null, can't access ->key)
- Correct: `if (n == nullptr) return new Node{key, nullptr, nullptr};`

### 3. PercolateUp vs PercolateDown loop condition
- **PercolateDown** loops while `i <= heap_size` (going DOWN, boundary is bottom)
- **PercolateUp** loops while `i > 1` (going UP, boundary is the root)
- Direction matters!

### 4. AVL: always fix the LOWEST violation first
- After insertion, walk back UP from the inserted node
- Fix the FIRST node with BF ∉ {-1, 0, +1} you encounter
- Don't fix the higher one — often fixing the lower one resolves the upper one automatically

### 5. RB tree: check the UNCLE's color, not the parent's
- Uncle = grandparent's OTHER child
- NIL counts as BLACK
- Don't forget that

### 6. Tree traversals: pre-order ≠ level-order
- Pre-order is DEPTH-FIRST (dive into left subtree fully before going right)
- Level-order is BREADTH-FIRST (row by row)
- Tree `15→{8,22}, 8→{4,11}, 22→{_,25}`:
  - Pre-order: 15, 8, 4, 11, 22, 25 (dive deep)
  - Level-order: 15, 8, 22, 4, 11, 25 (row by row)

### 7. Tree properties: ROOT counts as internal if it has children
- Internal node = any node with children (INCLUDING the root)
- Leaf = no children
- On MT1: lost points for forgetting root in "list internal nodes"

### 8. Reconstruction: pre-order root vs post-order root
- Pre-order: root = FIRST element
- Post-order: root = LAST element

### 9. Quicksort: i starts at index 1, j starts at LAST index
- i = 1 (right after pivot at index 0)
- j = n - 1 (last valid index, not n - 2)

### 10. AVL rotation case: identify by NODE positions, not just BFs
- Same direction (LL or RR) → single rotation
- Zigzag (LR or RL) → double rotation
- If BFs are +2/+1 or -2/-1 → same direction
- If +2/-1 or -2/+1 → zigzag

---

## TREES — Traversals & Reconstruction

### The 4 traversals (mnemonic: position of N tells you when root is visited)
| Name | Order | When root visited | DFS or BFS? |
|------|-------|-------------------|-------------|
| Pre-order | NLR | Before subtrees (FIRST) | DFS |
| In-order | LNR | Between subtrees (MIDDLE) | DFS |
| Post-order | LRN | After subtrees (LAST) | DFS |
| Level-order | row-by-row | Top-to-bottom, left-to-right | BFS |

### Reconstruct from 2 traversals
1. Find root: pre-order's FIRST element OR post-order's LAST element
2. Find root in in-order → split into left/right subtree nodes
3. Recurse on each side
4. (In-order ALONE is not enough — need 2 traversals)

---

## RECURSIVE TREE FUNCTIONS (write cold)

### The 2-line skeleton
```cpp
if (n == nullptr) → base case answer
return [combine] (call(n->left), call(n->right))
```

### Height (Height(null) = -1)
```cpp
int Height(Node* n) {
    if (n == nullptr) return -1;
    return 1 + std::max(Height(n->left), Height(n->right));
}
```

### Contains
```cpp
bool Contains(Node* n, int key) {
    if (n == nullptr) return false;
    if (key < n->key) return Contains(n->left, key);
    if (key > n->key) return Contains(n->right, key);
    return true;
}
```

### Insert (returns root of subtree)
```cpp
Node* Insert(Node* n, int key) {
    if (n == nullptr) return new Node{key, nullptr, nullptr};
    if (key < n->key) n->left  = Insert(n->left,  key);
    else if (key > n->key) n->right = Insert(n->right, key);
    return n;
}
```

### Prog03 Insert with count
```cpp
Node* Insert(Node* n, int key) {
    if (n == nullptr) return new Node{key, 1, nullptr, nullptr};
    if (key == n->key) n->count++;
    else if (key < n->key) n->left  = Insert(n->left,  key);
    else                   n->right = Insert(n->right, key);
    return n;
}
```

### FindMin (always go left)
```cpp
Node* FindMin(Node* n) {
    if (n->left == nullptr) return n;
    return FindMin(n->left);
}
```

---

## BST PROPERTY CHECK

For EVERY node:
- ALL descendants in left subtree < node
- ALL descendants in right subtree > node
- (Not just direct children — applies to entire subtree)

A node can be a valid child but violate an ancestor's range. (e.g., 21 as descendant of 20's left subtree → violates 20's rule, not 10's rule).

---

## AVL TREES

### Balance Factor formula
```
BF(node) = Height(node->left) - Height(node->right)
Height(null) = -1
Height(node) = 1 + max(Height(left), Height(right))
```

Use only DIRECT children's heights (not grandchildren).

### Valid AVL: every node's BF ∈ {-1, 0, +1}

### 4 rotation cases
| BF of unbalanced | BF of child | Case | Fix |
|------------------|-------------|------|-----|
| +2 | +1 | LL | Right rotate unbalanced |
| +2 | -1 | LR | Left rotate child, then right rotate unbalanced |
| -2 | -1 | RR | Left rotate unbalanced |
| -2 | +1 | RL | Right rotate child, then left rotate unbalanced |

### Pattern: middle value always becomes the new root
- LL: 30,20,10 → 20 root
- RR: 10,20,30 → 20 root
- LR: 30,10,20 → 20 root
- RL: 10,30,20 → 20 root

---

## RED-BLACK TREES

### 5 Properties (memorize)
1. Every node is RED or BLACK
2. Root is BLACK
3. Every NIL is BLACK
4. RED nodes have BLACK children (no consecutive reds)
5. Every root-to-NIL path has the same number of BLACK nodes

### Insertion (new node always RED)
```
Parent BLACK              → done
Parent RED, uncle RED     → RECOLOR (P→B, U→B, G→R), recurse on G
Parent RED, uncle BLACK   → ROTATE + swap colors
```

NIL counts as BLACK.

### Notation
- N = New node (just inserted)
- P = Parent of N
- G = Grandparent (P's parent)
- U = Uncle (G's other child)

### Color swap rule (rotate case)
**Whoever ends up at the TOP of the rotated subtree becomes BLACK.**
- Single rotation (LL/RR): P at top → P becomes B, G becomes R
- Double rotation (LR/RL): N at top → N becomes B, G becomes R

### Root rule
After all fixes, color root BLACK (in case it became red from a recolor cascade).

---

## B-TREES

### Vocabulary (this was confusing — read carefully)
- **Record** = the actual data row (e.g., a student row, 512 bytes)
- **Key** = the search ID embedded in a record (8 bytes)
- **Pointer** = address of a child node (8 bytes)
- **Leaf node** = container holding many records
- **Internal node** = container holding pointers + keys (no records)

**Only leaves have records. Internal nodes are just signposts.**

### B-tree of order M
| Property | Value |
|----------|-------|
| Max children per internal node | M |
| Max keys per internal node | M - 1 |
| Min children per non-root internal node | ⌈M/2⌉ |
| Root can have | 2 to M children |
| All leaves at | same depth |

Why M-1 keys for M children? Keys are dividers between children. M children need M-1 dividers.

### Disk sizing formulas
```
L = page_size / record_size                    ← max records per leaf

8M + 8(M-1) ≤ page_size                        ← M pointers (8B) + M-1 keys (8B)
i.e., solve for M:  M ≤ (page_size + 8) / 16
```

For 4096-byte page, 8-byte keys/pointers, 512-byte records:
- L = 4096 / 512 = 8
- 16M ≤ 4104 → M = 256

### Disk accesses for N records
```
disk_accesses ≈ ⌈log_M(N / L)⌉ + 1
```
Examples:
- N=1M, L=8, M=256: ⌈log_256(125000)⌉ + 1 = 3 + 1 = **4 disk reads**

### Why B-trees exist
Disk reads are slow (~5ms each). Binary trees of 1M items need 20+ reads. B-trees with M=256 need ~4. Each node sized to exactly fit one disk page.

---

## BINARY HEAPS (1-indexed array)

### Index formulas
- parent(i) = i / 2
- left(i)   = 2i
- right(i)  = 2i + 1
- Last internal node = n / 2

### PercolateDown (max-heap)
```cpp
void PercolateDown(int i, int heap_size) {
    while (i <= heap_size) {
        int left = 2*i, right = 2*i + 1, larger = i;
        if (left  <= heap_size && data[left]  > data[larger]) larger = left;
        if (right <= heap_size && data[right] > data[larger]) larger = right;
        if (larger == i) return;
        std::swap(data[i], data[larger]);
        i = larger;
    }
}
```

### PercolateUp (max-heap)
```cpp
void PercolateUp(int i) {
    while (i > 1) {                    // ← NOT i <= heap_size!
        int parent = i / 2;
        if (data[parent] >= data[i]) return;
        std::swap(data[i], data[parent]);
        i = parent;
    }
}
```

### Floyd's heapify (O(n))
1. Start at index n/2 (last internal node)
2. PercolateDown
3. Walk backwards to index 1, PercolateDown each
4. Skip leaves (they're already trivially heaps)

### Heap sort (uses std)
```cpp
template <typename K>
void heapsort(std::vector<K> &a) {
    std::make_heap(a.begin(), a.end());
    for (unsigned i = 0; i < a.size(); i++)
        std::pop_heap(a.begin(), a.end() - i);
}
```
- `pop_heap` swaps max (at begin) to end, then re-heapifies [begin, end-1)
- Range shrinks each iteration: `end() - i`
- Produces ASCENDING order
- In place, NOT stable

---

## QUICKSORT PARTITION (Hoare-style, leftmost pivot)

### Goal
After partition: pivot is in its final sorted position, smaller stuff on left, larger stuff on right.

### Procedure
1. Pivot = a[0] (leftmost)
2. i = 1 (left scanner), j = n-1 (right scanner)
3. **i scans RIGHT while a[i] < pivot** (stops on ≥ pivot)
4. **j scans LEFT while a[j] > pivot** (stops on ≤ pivot)
5. If i < j: swap a[i] and a[j], then i++, j--
6. If i ≥ j: STOP. Swap pivot (a[0]) with a[j]. Done.

### Worked example: [5, 3, 8, 1, 7, 2], pivot=5
```
Initial:  [5, 3, 8, 1, 7, 2]   i=1, j=5
i scan: a[1]=3<5 → i=2, a[2]=8≥5 STOP
j scan: a[5]=2≤5 STOP
i<j → swap a[2]↔a[5]:  [5, 3, 2, 1, 7, 8]   i=3, j=4
i scan: a[3]=1<5 → i=4, a[4]=7≥5 STOP
j scan: a[4]=7>5 → j=3, a[3]=1≤5 STOP
i>j → STOP, swap pivot a[0]↔a[3]:  [1, 3, 2, 5, 7, 8]
```
Pivot 5 at index 3 = final sorted position.

---

## MERGE SORT

### Procedure
1. Split array in half recursively until each piece has 1 element
2. Merge pairs upward using two-pointer technique
3. When merging, take smaller. Ties go to LEFT (this is why stable).

### Worked example: [8, 3, 5, 1, 6, 2, 9, 7]
```
[8,3,5,1] | [6,2,9,7]
[8,3] [5,1] | [6,2] [9,7]
[8] [3] [5] [1] | [6] [2] [9] [7]

Merge: [3,8] [1,5] | [2,6] [7,9]
       [1,3,5,8]   | [2,6,7,9]
       [1,2,3,5,6,7,8,9]
```

---

## SORT COMPARISON TABLE (Q18)

| Algorithm | Best | Worst | Average | Stable | In-place |
|-----------|------|-------|---------|--------|----------|
| Selection | O(n²) | O(n²) | O(n²) | **No** | Yes |
| Insertion | O(n) | O(n²) | O(n²) | **Yes** | Yes |
| Merge | O(n log n) | O(n log n) | O(n log n) | **Yes** | **No** |
| Quicksort | O(n log n) | O(n²) | O(n log n) | **No** | Yes |
| Heapsort | O(n log n) | O(n log n) | O(n log n) | **No** | Yes |

### Justifications
- **Selection** always O(n²): must scan rest of array each pick, no early termination. Not stable: leapfrog swaps jump over equal elements.
- **Insertion** best O(n): already-sorted stops at first comparison each step. Stable: stops at equal, doesn't displace earlier equals.
- **Merge** always O(n log n): log n levels × n work per level. Not in-place: needs auxiliary array.
- **Quicksort** worst O(n²): pivot always min/max (already-sorted array with leftmost-pivot). Not stable: swaps cross equal elements.
- **Heapsort** O(n log n): O(n) build + n × O(log n) extractions. Not stable: heap ops shuffle equals.

---

## ON-EXAM PROCEDURE

1. **Read all 6 questions first.** Tag each: easy (≤5 min), medium (10 min), hard (15+ min). Do easy first.
2. **Show work for partial credit.** Even if final answer is wrong, the steps get points.
3. **For tree drawings:** draw clearly with `/` and `\` slashes, label nodes (color for RB).
4. **For trace questions:** show array after EACH step (not just the final).
5. **For code questions:** put `return` in front of every recursive call. Handle null base case first.
6. **For Big-O:** justify by analyzing each loop separately, then combine.
7. **No calculators allowed.** Practice mental arithmetic — division like 8208/24 = 342.

Bring: dark pen (Ty's exam rule), watch (for pacing), water.

90 minutes, 6 questions = ~15 min per question. Don't camp on one.
