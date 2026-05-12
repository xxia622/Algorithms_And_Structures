# Priority Queue & Binary Heap — Deep Walkthrough

## Priority Queue ADT

A priority queue is like a regular queue, but instead of FIFO, each item has a **priority** and the highest-priority item is always served next.

```cpp
void Insert(T item);      // add with priority
T    ExtractMax();        // remove and return highest priority
T    Peek();              // view highest without removing
int  Size();
```

Think of an ER waiting room — a patient with a critical injury jumps the queue regardless of arrival time.

---

## The Binary Heap

The most common implementation of a priority queue. Two variants:
- **Max-heap**: parent ≥ both children (largest element at root)
- **Min-heap**: parent ≤ both children (smallest element at root)

We'll use max-heap throughout (same logic, reversed comparisons for min-heap).

### Two Properties

1. **Shape property:** Complete binary tree (all levels full except possibly the last, filled left-to-right)
2. **Heap property:** Every parent ≥ both its children

```
Valid max-heap:
        90
       /  \
      80   70
     / \  / \
    60 50 65 30
   / \
  20  40
```

---

## Array Representation

Because a heap is a complete binary tree, it maps perfectly to an array — no pointers needed.

```
Index:   0   1   2   3   4   5   6   7   8
Array: [90, 80, 70, 60, 50, 65, 30, 20, 40]
```

For node at index `i` (0-indexed):
```
Left child:  2i + 1
Right child: 2i + 2
Parent:      (i - 1) / 2   (integer division)
```

**Verify:**
- Node 60 is at index 3. Left child: 2(3)+1 = 7 → index 7 = 20 ✓
- Node 60's parent: (3-1)/2 = 1 → index 1 = 80 ✓

---

## Insert — Bubble Up

1. Add new element at the **end** of the array (next available spot in the last level, left-to-right)
2. **Bubble up:** while the new element > its parent, swap with parent

```
Insert 85 into heap:
Step 1 — Add at end (index 9):
        90
       /  \
      80   70
     / \  / \
    60 50 65 30
   / \ /
  20 40 85

Step 2 — 85 > parent(60) → swap:
        90
       /  \
      80   70
     / \  / \
    85 50 65 30    ← 85 and 60 swapped
   / \ /
  20 40 60

Step 3 — 85 > parent(80) → swap:
        90
       /  \
      85   70
     / \  / \
    80 50 65 30    ← 85 and 80 swapped
   / \ /
  20 40 60

Step 4 — 85 < parent(90) → stop.
```

**Complexity:** O(log N) — at most one swap per level.

---

## ExtractMax — Bubble Down

1. Save the root (max value) to return
2. Move the **last element** to the root
3. Remove the last element
4. **Bubble down:** while the root < either child, swap with the **larger** child

```
ExtractMax from:
        90
       /  \
      85   70
     / \  / \
    80 50 65 30
   / \ /
  20 40 60

Step 1 — Save 90, move 60 (last) to root:
        60
       /  \
      85   70
     / \  / \
    80 50 65 30
   / \
  20 40

Step 2 — 60 < max(85, 70)=85 → swap with 85:
        85
       /  \
      60   70
     / \  / \
    80 50 65 30
   / \
  20 40

Step 3 — 60 < max(80, 50)=80 → swap with 80:
        85
       /  \
      80   70
     / \  / \
    60 50 65 30
   / \
  20 40

Step 4 — 60 > max(20, 40) → stop.
Return 90.
```

**Always swap with the LARGER child** (in a max-heap), or you'd place a smaller value above a larger one and break the heap property.

**Complexity:** O(log N).

---

## BuildHeap — O(N) Not O(N log N)

Given an unsorted array, build a heap in-place.

**Naive approach:** Insert each element one by one → O(N log N).

**Better approach:** Start from the last internal node (index N/2 - 1) and bubble down each node.

```cpp
void BuildHeap(vector<int>& arr) {
    int n = arr.size();
    for (int i = n/2 - 1; i >= 0; i--)
        BubbleDown(arr, i, n);
}
```

**Why O(N)?**

- Nodes at the bottom (height 0) do 0 work — there are ~N/2 of them
- Nodes at height 1 do at most 1 swap — there are ~N/4 of them
- Nodes at height 2 do at most 2 swaps — there are ~N/8 of them
- Sum: N/2×0 + N/4×1 + N/8×2 + ... = N × Σ(h/2^h) = **O(N)**

This is a standard mathematical result — the sum converges to 2.

---

## Heap Sort

Use the heap to sort an array:
1. BuildHeap → O(N)
2. ExtractMax N times, placing each extracted element at the end → O(N log N)
3. Result: sorted array in-place

Total: **O(N log N)**. Not O(N) — don't confuse with BuildHeap.

---

## Complexity Summary

| Operation | Complexity |
|-----------|------------|
| Insert | O(log N) |
| ExtractMax / ExtractMin | O(log N) |
| Peek | O(1) |
| BuildHeap | **O(N)** |
| HeapSort | O(N log N) |

---

## Common Mistakes

**1. Swapping with the wrong child during bubble down:**
Always swap with the **larger** child (max-heap), not just any child larger than the parent. Swapping with the smaller child would violate heap property.

```
     50                 correct:      wrong:
    /  \                   80           60
   80  60     →           /  \         /  \
                         50  60       50  80
```

**2. Thinking BuildHeap is O(N log N):**
It's O(N). Only HeapSort is O(N log N).

**3. Getting parent/child indices wrong:**
For 0-indexed array:
- Parent of i = **(i−1)/2** (not i/2)
- Left child = **2i+1** (not 2i)

For 1-indexed (sometimes used in class):
- Parent of i = i/2
- Left child = 2i
- Right child = 2i+1

---

## Parent/Child Index Quick Reference (0-indexed)

| Node index | Parent | Left child | Right child |
|------------|--------|------------|-------------|
| 0 (root) | none | 1 | 2 |
| 1 | 0 | 3 | 4 |
| 2 | 0 | 5 | 6 |
| 3 | 1 | 7 | 8 |
| 4 | 1 | 9 | 10 |
| 7 | 3 | 15 | 16 |

---

## Key Takeaways

1. Max-heap: parent ≥ children; root = maximum element
2. Complete binary tree → stored as array with no pointers
3. Parent of i = **(i−1)/2**; left child = **2i+1**; right child = **2i+2** (0-indexed)
4. Insert: add at end → **bubble up** (swap with parent while larger)
5. ExtractMax: swap root ↔ last → remove last → **bubble down** (swap with LARGER child)
6. Bubble down: always swap with the **larger** child, not just any larger child
7. BuildHeap = **O(N)** — not O(N log N). HeapSort = O(N log N).
