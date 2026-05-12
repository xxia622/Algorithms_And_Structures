# Linked Lists — Deep Walkthrough

## Why Not Just Use Arrays?

Arrays are contiguous in memory — great for random access (O(1) by index), but terrible for insertion/deletion in the middle because you have to shift everything. Linked lists trade random access for O(1) insert/delete at a known position.

| Operation | Array | Linked List |
|-----------|-------|-------------|
| Access by index | O(1) | O(N) |
| Insert at front | O(N) | O(1) |
| Insert at end (no tail) | O(1) amortized | O(N) |
| Insert at end (with tail) | O(1) amortized | O(1) |
| Insert in middle | O(N) | O(N) to find, O(1) to link |
| Delete | O(N) | O(N) to find, O(1) to unlink |

---

## Singly Linked List

### Node Structure
```cpp
struct Node {
    int data;
    Node* next;
};
```

Each node holds data and a pointer to the next node. The last node's `next` is `nullptr`.

```
head
 |
[5] → [15] → [30] → nullptr
```

### Key Operations

**Insert at front (position 0):**
```cpp
void InsertFront(int val) {
    Node* n = new Node{val, head};
    head = n;
    cur_size++;
}
```
New node's `next` points to old head. Head updated to new node.

**Insert anywhere else:**
```cpp
void Insert(int val, int pos) {
    if (pos == 0) { InsertFront(val); return; }
    Node* prev = GetNode(pos - 1);   // walk to node before position
    Node* n = new Node{val, prev->next};
    prev->next = n;
    cur_size++;
}
```

**Why two cases?** Position 0 modifies `head`. Any other position just rewires a `next` pointer mid-list — `head` is untouched.

**Remove:**
```cpp
void Remove(int pos) {
    if (pos == 0) { head = head->next; cur_size--; return; }
    Node* prev = GetNode(pos - 1);
    prev->next = prev->next->next;   // skip over the target node
    cur_size--;
}
```

**Find:**
```cpp
int Find(int val) {
    Node* cur = head;
    int idx = 0;
    while (cur != nullptr) {
        if (cur->data == val) return idx;
        cur = cur->next;
        idx++;
    }
    return -1;   // not found
}
```

### The Tail Pointer Problem

Without a tail pointer, inserting at the end requires walking the entire list: O(N).

**Fix:** maintain a `tail` pointer alongside `head`.

```cpp
Node* head = nullptr;
Node* tail = nullptr;
```

Now `Insert(val, size)` just does:
```cpp
Node* n = new Node{val, nullptr};
if (tail) tail->next = n;
else head = n;
tail = n;
cur_size++;
```
O(1) — no traversal needed. Other operations (Get, Find, Remove) are unaffected.

**Important:** Making the list doubly linked does NOT automatically give you O(1) end-insertion. You still need a tail pointer for that.

---

## Doubly Linked List

### Node Structure
```cpp
struct Node {
    int data;
    Node* next;
    Node* prev;   // new: pointer going backwards
};
```

```
head                              tail
 |                                 |
[5] ⇄ [15] ⇄ [30] → nullptr
```

Each node points forward (next) AND backward (prev). This enables:
- Traversal in both directions
- O(1) removal if you already have a pointer to the node (no need to find the previous node)

### What Methods Change vs Singly?

| Method | Change? |
|--------|---------|
| Size() | No |
| Get() | No |
| Find() | No |
| Insert() | Yes — must set prev pointers |
| Remove() | Yes — must update both directions |

### Insert (doubly linked)
```cpp
void Insert(int val, int pos) {
    Node* n = new Node{val, nullptr, nullptr};
    if (pos == 0) {
        n->next = head;
        if (head) head->prev = n;
        head = n;
        if (cur_size == 0) tail = n;
    } else {
        Node* prev = GetNode(pos - 1);
        n->next = prev->next;
        n->prev = prev;
        if (prev->next) prev->next->prev = n;
        else tail = n;           // n is the new last node
        prev->next = n;
    }
    cur_size++;
}
```

### Remove (doubly linked)
```cpp
void Remove(int pos) {
    Node* n = GetNode(pos);

    if (n->next != nullptr)
        n->next->prev = n->prev;   // tell next node to skip n backward
    else
        tail = n->prev;            // n was the tail

    if (n->prev != nullptr)
        n->prev->next = n->next;   // tell prev node to skip n forward
    else
        head = n->next;            // n was the head

    delete n;
    cur_size--;
}
```

**Always handle both directions.** When removing n:
- The node after n must update its `prev`
- The node before n must update its `next`
- If either neighbor doesn't exist, update `head` or `tail` instead

---

## Common Mistakes

**1. Mixing up Get(index) and Find(value)**
- `Get(2)` → returns the value at index 2
- `Find(30)` → returns the index where value 30 is stored

**2. Off-by-one on the tail**
- When inserting at position `size`, the new node becomes the tail
- When removing the last node, tail must be updated to `n->prev`

**3. Forgetting to update prev when inserting**
```cpp
// Wrong — sets next->prev to the old node, not n
prev->next = n;
n->next = prev->next;

// Correct — set n->next->prev before relinking
n->next = prev->next;
if (n->next) n->next->prev = n;
prev->next = n;
n->prev = prev;
```

---

## Memory Model

```
head                                 tail
 ↓                                    ↓
[prev=null|5|next=●]→[prev=●|15|next=●]→[prev=●|30|next=null]
           ↑_________↑          ↑_________↑
```

Walking forward: follow `next` pointers
Walking backward: follow `prev` pointers

---

## Key Takeaways

1. Singly linked: two insert cases (front vs. rest) because only front modifies `head`
2. Tail pointer → O(1) end-insertion, no other costs
3. Doubly linked: `Insert()` and `Remove()` must update both `next` and `prev`
4. `Remove()` always check both: does `n->next` exist? does `n->prev` exist?
5. Default STL sequence container → `std::vector` (contiguous memory, better cache performance)
