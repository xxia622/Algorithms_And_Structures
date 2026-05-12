# Quiz 3 Review — CS 010C
**Topic:** Doubly Linked Lists · Stacks · Postfix Evaluation · Makefiles · Unit Testing
**Score: 11 / 28 (39%)**

---

## Question 1 — 3/3 ✓
**Doubly vs singly linked list: which public methods must be modified?**

**Correct answer:** `Insert()` and `Remove()` were modified; `Size()`, `Get()`, `Find()` stayed (almost) the same.

**Why:** Insert and Remove must now also update the `prev` pointer on affected nodes. The other methods only traverse or count — they don't touch link structure.

---

## Question 2 — 2/5 ✗ (partial)
**Complete the `Remove()` function for a doubly linked list.**

```cpp
void Remove(const unsigned int pos) {
    if (pos >= cur_size)
        throw std::out_of_range("Position out of range!");

    auto n = GetNode(pos);          // <1> — GetNode, not Get (returns node pointer)

    if (n->next != nullptr)
        n->next->prev = n->prev;    // <2> — tell next node to skip over n
    else
        tail = n->prev;             // <3> — n was the tail; update tail

    if (n->prev != nullptr)
        n->prev->next = std::move(n->next);  // <4> — tell prev node to skip over n
    else
        head = std::move(n->next);  // <5> — n was the head; update head

    cur_size--;
}
```

**Key insight:** Always handle BOTH directions. When removing node n:
- The node **after** n (`n->next`) must point its `prev` back to `n->prev`
- The node **before** n (`n->prev`) must point its `next` forward to `n->next`
- If either neighbor doesn't exist, update `head` or `tail` instead

---

## Question 3 — 2/5 ✗ (partial)
**Unit testing outcomes after:**
```cpp
ListDoublyLinked l;
l.Insert(5, 0);   // list: [5]
l.Insert(15, 0);  // list: [15, 5]
l.Insert(30, l.Size());  // list: [15, 5, 30]
```

| Test | Your Answer | Correct | Explanation |
|------|-------------|---------|-------------|
| `ASSERT_EQ(l.Size(), 3)` | Succeeds | **Succeeds** ✓ | Three insertions → size 3 |
| `ASSERT_EQ(l.Get(15), 0)` | Succeeds | **Fails** ✗ | `Get(index)` takes an index, not a value. Index 15 is out of range → throws, doesn't return 0 |
| `ASSERT_EQ(l.Find(30), 2)` | Succeeds | **Succeeds** ✓ | 30 is at index 2 |
| `ASSERT_EQ(l.Find(99), -1)` | Fails | **Succeeds** ✗ | 99 not in list → Find returns -1, so -1 == -1 is true |
| `ASSERT_THROW(l.Get(3), std::out_of_range)` | Fails | **Succeeds** ✗ | Index 3 is out of range (indices 0-2 only) → throws as expected |

**Key lesson:** `Get(i)` is index-based. `Find(v)` is value-based. Don't confuse them.

---

## Question 4 — 2/2 ✓
**When inserting into a singly linked list without a tail pointer, what two cases differ?**

**Correct answer:** Insertion at the **beginning** vs. insertion **anywhere else**.

**Why:** Inserting at position 0 modifies `head`. All other positions just update a `next` pointer mid-list. The tail case doesn't need special treatment because the loop naturally reaches it — it's just O(N).

---

## Question 5 — 0/2 ✗
**How to make end-insertion O(1) without changing other complexities?**

- Your answer: Transform into a doubly linked list
- **Correct answer: Maintain a tail pointer**

**Why:** A doubly linked list lets you traverse backwards, but you still don't know where the end is without a tail pointer — Insert at end is still O(N). A `tail` pointer directly points to the last node, making `Insert(size)` O(1) with no impact on other operations.

---

## Question 6 — 0/2 ✗
**Recommended sequence container in the C++ standard library?**

- Your answer: `std::forward_list`
- **Correct answer: `std::vector`**

**Why:** Unless you have a specific reason (frequent mid-list insertions, need for O(1) prepend), `std::vector` is preferred. It has better cache performance due to contiguous memory, and O(1) amortized append. `forward_list` is a singly linked list — rarely the right default choice.

---

## Question 7 — 0/3 ✗
**Evaluate postfix expression: `7 4 3 * 1 5 + / *`**

- Your answer: 105
- **Correct answer: 14**

**Stack trace:**
```
Token   Stack (top →)
7       [7]
4       [7, 4]
3       [7, 4, 3]
*       [7, 12]         (4 * 3 = 12)
1       [7, 12, 1]
5       [7, 12, 1, 5]
+       [7, 12, 6]      (1 + 5 = 6)
/       [7, 2]          (12 / 6 = 2)
*       [14]            (7 * 2 = 14)
```

**Rule:** When you see an operator, pop two values: `second_popped OP first_popped`.

---

## Question 8 — 0/2 ✗
**When running `make` with no arguments, which target executes?**

- Your answer: All targets in order
- **Correct answer: The first target in the file**

**Why:** `make` with no target defaults to the **first target** listed in the Makefile. This is why the first target is conventionally named `all` — it's a convention, not a requirement.

---

## Question 9 — 0/2 ✗
**Makefile rule structure:**
```makefile
<target>: <dependencies>
    <command>
```

| Slot | Correct Term |
|------|-------------|
| `<1>` | **target** |
| `<2>` | **dependencies** |
| `<3>` | **command** |

**Remember:** Target → what to build. Dependencies → what it needs. Command → how to build it (must be indented with a **tab**, not spaces).

---

## Question 10 — 2/2 ✓
**Which statement best describes unit testing?**

**Correct answer:** It checks small parts of the program individually to verify correctness and reduce the chance of future regressions.

---

## Key Takeaways from Quiz 3
1. `Get(i)` = index-based; `Find(v)` = value-based — don't mix them up
2. Tail pointer = O(1) end-insertion; doubly linked alone does not
3. Postfix: pop two, apply operator, push result — track the order carefully
4. `make` with no args → **first target**, not all targets
5. Default STL sequence container → **`std::vector`**, not list variants
