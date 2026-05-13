# Lab 7 — Trie: Mistakes & Knowledge Gaps

## Syntax Gaps

- **`ClassName::MethodName`** — unfamiliar with scope resolution `::` for defining methods outside a class
- **`->` vs `.`** — was using `.` on pointers; pointers need `->`
- **Initializer lists** — `: member(value)` syntax was unfamiliar
- **`new TrieNode()`** — dynamically allocating objects on the heap was new

## Conceptual Gaps

- **Class vs object** — called methods on `TrieNode` (the class) instead of `node` (an instance). This was the biggest recurring confusion.
- **Constructors** — didn't know why members need to be initialized or what a constructor does
- **Pointer as a walking cursor** — the idea of `node = node->Get(c)` moving a pointer through a data structure was unfamiliar; tried `c + 1` thinking you increment the character
- **Return types** — returned `SearchPrefix(word)` (a pointer) directly from a `bool` function without converting

## Things Clicked Quickly

- `c - 'a'` for char-to-index once hinted
- Range-based for loops
- Overall trie logic once the walking pointer concept clicked

## What to Review

- Pointers and `->` — comes up constantly in CS 10C
- Stack vs heap (`new` keyword)
- How classes, instances, and methods relate to each other
