# Stacks — Deep Walkthrough

## The Core Idea

A stack is a **LIFO** (Last In, First Out) container. Think of a stack of plates — you can only add or remove from the top.

```
Push 3:   Push 7:   Push 1:   Pop:    Pop:
  [ ]      [7]      [1]      [7]      [3]
  [3]      [3]      [7]      [3]      [ ]
           [ ]      [3]
                    [ ]
  top=3   top=7   top=1    top=7    top=3
```

---

## Interface

```cpp
void  Push(const T& item);   // add to top
void  Pop();                 // remove from top (no return)
T&    Top();                 // view top without removing
int   Size();
bool  Empty();
```

---

## Two Implementations

### Array-based Stack
```
[3][7][1][ ][ ]
         ↑
       top index = 2
```
- `Push`: place at `top+1`, increment top
- `Pop`: decrement top
- `Top`: return `arr[top]`
- All operations: O(1)
- Fixed max size (unless you use a dynamic array / vector)

### Linked-list-based Stack
```
top
 ↓
[1] → [7] → [3] → nullptr
```
- `Push`: insert at front
- `Pop`: remove from front
- `Top`: read head's data
- All operations: O(1)
- Dynamic size, no cap

---

## Applications

### 1. Postfix (Reverse Polish Notation) Evaluation

Postfix avoids parentheses by placing operators after their operands.

**Algorithm:**
- If token is a **number** → push it
- If token is an **operator** → pop two values, apply operator, push result
- At the end, the stack has one value: the answer

**Order matters:** `second_popped OPERATOR first_popped`

**Example: `7 4 3 * 1 5 + / *`**
```
Token   Action              Stack (top →)
7       push 7              [7]
4       push 4              [7, 4]
3       push 3              [7, 4, 3]
*       pop 3,4 → 4*3=12   [7, 12]
1       push 1              [7, 12, 1]
5       push 5              [7, 12, 1, 5]
+       pop 5,1 → 1+5=6    [7, 12, 6]
/       pop 6,12 → 12/6=2  [7, 2]
*       pop 2,7 → 7*2=14   [14]
Result: 14
```

Common mistake: `7 4 3 * 1 5 + / *` → 105 (forgetting order of division). Always: **second popped** OP **first popped**.

### 2. Balanced Parentheses Check
```cpp
bool isBalanced(string s) {
    Stack<char> st;
    for (char c : s) {
        if (c == '(' || c == '{' || c == '[')
            st.Push(c);
        else if (c == ')' || c == '}' || c == ']') {
            if (st.Empty()) return false;
            char top = st.Top(); st.Pop();
            if ((c==')' && top!='(') ||
                (c=='}' && top!='{') ||
                (c==']' && top!='[')) return false;
        }
    }
    return st.Empty();
}
```

### 3. Function Call Stack
Every function call pushes a stack frame (local variables, return address). Recursion is literally the call stack.

---

## Stack Sort

Sort a stack using only one extra stack:

```cpp
Stack<T> Sort(Stack<T>& s1) {
    Stack<T> s2;
    while (s1.Size() != 0) {
        T item = s1.Top();
        s1.Pop();
        while (s2.Size() && s2.Top() < item)  {
            s1.Push(s2.Top());   // push s2's top back to s1
            s2.Pop();
        }
        s2.Push(item);           // item goes in sorted position in s2
    }
    return s2;  // s2 is sorted, largest on top
}
```

**Complexity:**
- Worst case (ascending input): O(N²) — every item must be repositioned
- Best case (descending input): **O(N)** — each item slides directly into s2 without any inner-loop work

---

## Delete Middle Element (Recursion)

```cpp
void DeleteMiddleElement(Stack<T>& s, unsigned int n, unsigned int curr = 0) {
    if (s.Size() == 0) return;
    T item = s.Top();
    s.Pop();
    DeleteMiddleElement(s, n, curr + 1);  // recurse down
    if (curr != n / 2)
        s.Push(item);   // put everything back EXCEPT the middle
}
```

**How it works:**
- Recurse until you've popped N/2 elements (the middle)
- On the way back up, push everything except the middle element
- Max recursion depth = N/2

**Trace for stack [5,4,3,2,1] (top=1), n=5:**
```
curr=0: pop 1, recurse
curr=1: pop 2, recurse
curr=2: pop 3, recurse  ← n/2 = 2, so DON'T push 3 back
curr=3: pop 4, recurse
curr=4: pop 5, s is empty → return
unwind curr=4: curr(4) != 2 → push 5
unwind curr=3: curr(3) != 2 → push 4
unwind curr=2: curr(2) == 2 → skip (3 is deleted)
unwind curr=1: curr(1) != 2 → push 2
unwind curr=0: curr(0) != 2 → push 1
Result: [5,4,2,1] — 3 (middle) is gone
```

---

## Key Takeaways

1. LIFO — last in, first out
2. All operations (push, pop, top) are O(1)
3. Postfix: pop two, apply op, push result. Order: `second_popped OP first_popped`
4. Sort(): worst O(N²), best (descending input) O(N)
5. DeleteMiddle: recursion depth = N/2, not N
