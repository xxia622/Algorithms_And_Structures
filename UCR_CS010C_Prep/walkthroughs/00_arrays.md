# Arrays — Deep Walkthrough

## Fixed Arrays

A fixed array is a contiguous block of memory allocated at compile time (or at the time of declaration). Size cannot change.

```cpp
int arr[5] = {10, 20, 30, 40, 50};
```

### Memory Layout

Every element sits right next to the previous one in memory:

```
Address:  1000  1004  1008  1012  1016
Value:    [ 10] [ 20] [ 30] [ 40] [ 50]
Index:       0     1     2     3     4
```

Because of this layout, the address of element i is always:
```
address(i) = base_address + i × sizeof(element)
```

This is why random access is **O(1)** — no traversal, just arithmetic.

### Operations

| Operation | Complexity | Why |
|-----------|-----------|-----|
| Access by index | O(1) | Direct address calculation |
| Search (unsorted) | O(N) | Must scan linearly |
| Search (sorted) | O(log N) | Binary search |
| Insert at end | O(1) | If space exists |
| Insert in middle | O(N) | Must shift all elements right |
| Delete in middle | O(N) | Must shift all elements left |

### Insert Example — Shifting Right
```
Insert 25 at index 2:
Before: [10, 20, 30, 40, 50]
Shift:  [10, 20, 30, 30, 40, 50]  ← copy 30,40,50 one spot right
Place:  [10, 20, 25, 30, 40, 50]
```
Every element from index 2 onward must move — O(N) in the worst case.

### Limitations
- **Fixed size**: must know max size at compile time (or allocation time)
- **Wasted space**: if you allocate 100 slots but use 3, 97 are wasted
- **Stack allocation**: large fixed arrays can cause stack overflow

---

## Dynamic Arrays (`std::vector`)

A dynamic array solves the fixed-size problem by automatically resizing when full.

### Capacity vs Size

```
size     = number of elements currently stored
capacity = total slots currently allocated

size ≤ capacity always
```

```
After push_back(10), push_back(20), push_back(30):

Internal buffer (capacity=4):
[ 10 | 20 | 30 | __ ]
  ↑_________↑    ↑
  size = 3        unused slot
```

### The Doubling Strategy

When size == capacity and you push a new element:
1. Allocate a new buffer of size **2 × capacity**
2. Copy all existing elements to the new buffer
3. Free the old buffer
4. Insert the new element

```
capacity=2, size=2: [10, 20]
push_back(30):
  → allocate new buffer of size 4
  → copy: [10, 20, __, __]
  → insert: [10, 20, 30, __]
  → capacity=4, size=3

push_back(40): [10, 20, 30, 40]  capacity=4, size=4
push_back(50):
  → allocate new buffer of size 8
  → copy: [10, 20, 30, 40, __, __, __, __]
  → insert: [10, 20, 30, 40, 50, __, __, __]
  → capacity=8, size=5
```

### Why Doubling Gives Amortized O(1) Append

Consider N push_back operations. How many total copies happen?

```
Resize at size 1  → copy 1  element
Resize at size 2  → copy 2  elements
Resize at size 4  → copy 4  elements
Resize at size 8  → copy 8  elements
...
Resize at size N  → copy N  elements
Total copies = 1 + 2 + 4 + 8 + ... + N = 2N - 1 = O(N)
```

O(N) total copies across N insertions → **O(1) amortized per insertion**.

If you grew by 1 each time instead of doubling:
```
Resize at size 1 → copy 1
Resize at size 2 → copy 2
Resize at size 3 → copy 3
...
Resize at size N → copy N
Total = 1+2+3+...+N = N(N+1)/2 = O(N²)
```
O(N²) total → O(N) amortized per insertion. Much worse.

### Operations

| Operation | Complexity | Notes |
|-----------|-----------|-------|
| Access by index | O(1) | Same as fixed array |
| push_back | **O(1) amortized** | Occasional O(N) resize, but rare |
| pop_back | O(1) | Just decrement size |
| Insert at front/middle | O(N) | Must shift elements |
| Delete at front/middle | O(N) | Must shift elements |
| Search (unsorted) | O(N) | |
| Search (sorted) | O(log N) | Binary search |

---

## Array vs Linked List — The Full Comparison

| Property | Fixed Array | Dynamic Array | Singly Linked | Doubly Linked |
|----------|-------------|---------------|--------------|--------------|
| Memory layout | Contiguous | Contiguous | Scattered | Scattered |
| Random access | O(1) | O(1) | O(N) | O(N) |
| Insert at front | O(N) | O(N) | **O(1)** | **O(1)** |
| Insert at back | O(1)* | O(1) amortized | O(N) / O(1)† | O(N) / O(1)† |
| Insert in middle | O(N) | O(N) | O(N) find + O(1) link | O(N) find + O(1) link |
| Delete anywhere | O(N) | O(N) | O(N) | O(N) / O(1)‡ |
| Cache performance | Excellent | Excellent | Poor | Poor |
| Size flexibility | Fixed | Dynamic | Dynamic | Dynamic |
| Extra memory | None | Unused capacity | 1 pointer/node | 2 pointers/node |

*if space exists. †with tail pointer. ‡O(1) if you already have a pointer to the node.

### Why `std::vector` Beats Linked Lists for Most Use Cases

1. **Cache locality**: vector elements are contiguous — the CPU prefetches them efficiently. Linked list nodes are scattered in memory → cache misses on every traversal.
2. **Lower overhead**: no pointers per element — just the data.
3. **Random access**: O(1) vs O(N).
4. **Same asymptotic cost** for append (amortized O(1) both ways with tail pointer).

Unless you need O(1) front insertion, frequent mid-list operations with a known pointer, or truly unbounded growth with no wasted space — prefer `std::vector`.

---

## `std::vector` in Practice

```cpp
#include <vector>

vector<int> v;
v.push_back(10);         // append
v.push_back(20);
v[1] = 99;               // O(1) access
v.pop_back();            // remove last

cout << v.size();        // number of elements
cout << v.capacity();    // allocated slots

v.reserve(100);          // pre-allocate 100 slots (avoids repeated resizes)
```

**`reserve()` tip:** If you know you'll insert N elements, call `v.reserve(N)` first. Eliminates all resizes → O(N) total instead of O(N) amortized.

---

## Key Takeaways

1. Fixed arrays: O(1) access via address arithmetic; O(N) insert/delete due to shifting
2. Dynamic arrays double capacity on resize → O(1) amortized push_back
3. **Doubling is critical** — growing by 1 gives O(N) amortized, which is much worse
4. `std::vector` is preferred over linked lists for most workloads due to cache locality
5. `size` = elements stored; `capacity` = slots allocated; size ≤ capacity always
6. `reserve(N)` avoids repeated resizes when final size is known ahead of time
