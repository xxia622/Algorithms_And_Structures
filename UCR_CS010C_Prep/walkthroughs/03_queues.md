# Queues — Deep Walkthrough

## The Core Idea

A queue is a **FIFO** (First In, First Out) container. Think of a line at a store — first person in line is the first to be served.

```
Enqueue 3:  Enqueue 7:  Enqueue 1:  Dequeue:  Dequeue:
front back  front back  front back
[3]         [3][7]      [3][7][1]   [7][1]    [1]
 ↑    ↑      ↑      ↑    ↑      ↑    ↑    ↑    ↑   ↑
 F    B      F      B    F      B    F    B    F   B
```

---

## Interface

```cpp
void Push(const T& item);  // enqueue — add to back
T    Pop();                // dequeue — remove from front and return
T    Top();                // view front without removing
int  Size();
bool Empty();
```

---

## Queue Using Two Stacks

This is the classic CS interview / lab question. You simulate a queue using two stacks: `sPush` and `sPop`.

**Mental model:**
- `sPush` is the "inbox" — new items arrive here
- `sPop` is the "outbox" — items leave from here
- When the outbox is empty, flip the entire inbox into it (reversal restores FIFO order)

```cpp
template<typename T>
class Queue {
    Stack<T> sPush, sPop;
public:
    void Push(const T& item) {
        sPush.Push(item);          // always push to sPush
    }

    T Pop() {
        if (sPop.Size() == 0) {    // outbox empty — refill it
            while (sPush.Size() != 0) {
                sPop.Push(sPush.Top());
                sPush.Pop();
            }
        }
        T top = sPop.Top();
        sPop.Pop();
        return top;
    }
};
```

**Why does this work?**

When you transfer from sPush to sPop, the order is reversed:
```
sPush (top→): [C, B, A]   →   sPop (top→): [A, B, C]
```
A was inserted first (it's at the bottom of sPush). After transfer, A is at the top of sPop. Popping sPop gives A first — exactly FIFO.

**Trace: Push A, B, C, then Pop twice**
```
Push A: sPush=[A]          sPop=[]
Push B: sPush=[B,A]        sPop=[]
Push C: sPush=[C,B,A]      sPop=[]
Pop:    sPop empty → transfer → sPush=[], sPop=[A,B,C]
        pop sPop.Top()=A. Return A. sPop=[B,C]
Pop:    sPop not empty → pop sPop.Top()=B. Return B. sPop=[C]
```

**Complexity:**
- Each element is pushed to sPush once and popped from sPush once (during the transfer) and pushed to sPop once and popped from sPop once.
- Amortized: **O(1)** per operation
- Worst case single Pop (triggers full transfer): O(N)

**Common mistake — wrong condition order:**
```cpp
// Wrong: checks sPush when you should check sPop
if (sPush.Size() != 0) { ... }

// Correct: only transfer when sPop is empty
if (sPop.Size() == 0) { ... }
```

---

## Applications of Queues

### 1. Level-Order (BFS) Tree Traversal

```cpp
void LevelOrder(Node* root) {
    if (!root) return;
    Queue<Node*> q;
    q.Push(root);
    while (!q.Empty()) {
        Node* cur = q.Top();
        q.Pop();
        visit(cur);
        if (cur->left)  q.Push(cur->left);
        if (cur->right) q.Push(cur->right);
    }
}
```

Push left child first → left-to-right level order.
Push right child first → right-to-left level order.

### 2. Producer-Consumer / Task Scheduling

Tasks arrive and are processed in order — classic FIFO use case.

---

## Queue vs Stack — Side by Side

| Property | Stack | Queue |
|----------|-------|-------|
| Order | LIFO | FIFO |
| Add | Push (top) | Push (back) |
| Remove | Pop (top) | Pop (front) |
| Use case | DFS, recursion, undo | BFS, scheduling, buffers |

---

## Key Takeaways

1. FIFO — first in, first out
2. Two-stack queue: sPush is inbox, sPop is outbox; transfer only when sPop is empty
3. Transfer condition: `if (sPop.Size() == 0)` then `while (sPush.Size() != 0)`
4. Amortized O(1) per operation; worst-case single op is O(N)
5. Level-order traversal uses a queue (BFS); DFS uses a stack (or recursion)
