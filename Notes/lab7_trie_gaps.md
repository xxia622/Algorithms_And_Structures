# Lab 7 — Trie: Mistakes & Knowledge Gaps

## C++ Syntax Learned
- **`ClassName::Method`** — scope resolution for defining methods outside a class
- **`->` vs `.`** — pointers use `->`, regular objects use `.`
- **Initializer lists** — `: member(value)` syntax in constructors
- **`new ClassName()`** — heap allocation
- **`= delete`** — explicitly disabling a method (copy constructor, assignment operator)

## Concepts That Were New
- **Class vs object** — was calling methods on `TrieNode` (the class blueprint) instead of `node` (an instance). Biggest recurring confusion of the lab.
- **Constructors** — C++ doesn't auto-initialize variables; constructor is where you set defaults yourself
- **Pointer as a walking cursor** — `node = node->Get(c)` moves a pointer through a data structure; tried `c + 1` initially thinking you increment the character
- **Rule of Three** — destructor, copy constructor, copy assignment; all needed when managing heap memory
- **Memory leaks** — `new` without `delete` leaks memory; the destructor cleans it up
- **Stack vs heap** — `TrieNode root` (stack, auto-managed) vs `new TrieNode()` (heap, manually managed)

## Things That Clicked Quickly
- `c - 'a'` for char-to-index once hinted
- Range-based for loops
- Overall trie logic once the walking pointer concept clicked

## Big Picture Takeaway
Pointers are the core of C++ data structures. Almost every mistake today traced back to not fully understanding what a pointer is and how to use one. Drill this before the next lab.

## Result
Score: 30.25 / 30
