# Algorithm Analysis — Deep Walkthrough

## Why Analyze Algorithms?

Two programs that solve the same problem can have wildly different performance. We want a way to describe performance that is:
- **Independent of hardware** (a fast computer doesn't make a bad algorithm good)
- **Independent of language / implementation details**
- **Focused on how performance scales** as input size N grows

The answer is asymptotic analysis — describe the growth rate of runtime as N → ∞.

---

## The Three Symbols

### Big-O — Upper Bound (Worst Case)

> f(N) = O(g(N)) means f grows **no faster than** g.

Formal definition:
```
f(N) = O(g(N))  if and only if  ∃ c > 0, N₀ > 0 such that:
    f(N) ≤ c · g(N)   for all N ≥ N₀
```

In plain English: after some point N₀, g(N) (scaled by a constant c) is always an upper ceiling for f(N).

**This is the most commonly used symbol** — it gives a worst-case guarantee.

### Big-Ω (Omega) — Lower Bound (Best Case)

> f(N) = Ω(g(N)) means f grows **at least as fast as** g.

Formal definition:
```
f(N) = Ω(g(N))  if and only if  ∃ c > 0, N₀ > 0 such that:
    f(N) ≥ c · g(N)   for all N ≥ N₀
```

Used to describe the best case or a lower bound on any algorithm for a problem.
Example: any comparison-based sort must do at least Ω(N log N) comparisons.

### Big-Θ (Theta) — Tight Bound (Exact Growth Rate)

> f(N) = Θ(g(N)) means f grows **exactly as fast as** g (up to constants).

Formal definition:
```
f(N) = Θ(g(N))  if and only if  ∃ c₁, c₂ > 0, N₀ > 0 such that:
    c₁ · g(N) ≤ f(N) ≤ c₂ · g(N)   for all N ≥ N₀
```

Equivalently: **f(N) = Θ(g(N)) iff f(N) = O(g(N)) AND f(N) = Ω(g(N))**.

Big-Θ is the most precise — it sandwiches f between two scaled versions of g.

---

## Visualizing the Three Bounds

```
f(N)
 |          c₂·g(N)  ← upper bound (Big-O)
 |         /
 |   f(N) /           f(N) stays between c₁·g and c₂·g → Θ
 |       X
 |      / \
 |     /   c₁·g(N)  ← lower bound (Big-Ω)
 |____/_______________
                     N₀       N →
```

---

## The Formal Big-O Proof

To prove f(N) = O(g(N)), you must **find specific values of c and N₀** and show the inequality holds.

### Proof Structure
```
Claim: f(N) = O(g(N))
Proof: Choose c = ___ and N₀ = ___.
       For all N ≥ N₀:
           f(N) ≤ c · g(N)    [show this algebraically]
       Therefore f(N) = O(g(N)). □
```

### Example 1: Prove 3N² + 5N + 2 = O(N²)

**Claim:** 3N² + 5N + 2 = O(N²)

**Strategy:** bound each term by N²:
```
For N ≥ 1:
  5N  ≤ 5N²     (since N ≤ N² for N ≥ 1)
  2   ≤ 2N²     (since 1 ≤ N² for N ≥ 1)

So: 3N² + 5N + 2 ≤ 3N² + 5N² + 2N²
                  = 10N²
```

**Choose c = 10, N₀ = 1.**

Proof: For all N ≥ 1:
```
3N² + 5N + 2 ≤ 3N² + 5N² + 2N² = 10N²
```
Therefore 3N² + 5N + 2 = O(N²). □

### Example 2: Prove 5N³ + 3N = O(N³)

For N ≥ 1: 3N ≤ 3N³

So: 5N³ + 3N ≤ 5N³ + 3N³ = 8N³

**Choose c = 8, N₀ = 1.**

For all N ≥ 1: 5N³ + 3N ≤ 8N³. □

### Example 3: Prove N² ≠ O(N) (disproof)

**Claim:** N² = O(N) is FALSE.

Suppose for contradiction that ∃ c, N₀ such that N² ≤ c·N for all N ≥ N₀.

Then N ≤ c for all N ≥ N₀. But N grows without bound — contradiction. □

### Example 4: Prove 2N + 10 = O(N)

For N ≥ 10:
```
2N + 10 ≤ 2N + N = 3N    (since 10 ≤ N when N ≥ 10)
```

**Choose c = 3, N₀ = 10.**

For all N ≥ 10: 2N + 10 ≤ 3N. □

---

## Common Growth Rates (Slowest to Fastest)

```
O(1) < O(log N) < O(√N) < O(N) < O(N log N) < O(N²) < O(N³) < O(2^N) < O(N!)
```

| Name | Complexity | Example |
|------|-----------|---------|
| Constant | O(1) | Array access, push/pop |
| Logarithmic | O(log N) | Binary search, BST find |
| Linear | O(N) | Linear scan, tree print |
| Linearithmic | O(N log N) | Merge sort, heap sort |
| Quadratic | O(N²) | Nested loops, insertion sort |
| Cubic | O(N³) | Triple nested loops |
| Exponential | O(2^N) | Recursive Fibonacci (naive) |

---

## Dropping Constants and Lower-Order Terms

The rules:
1. **Drop constants:** O(5N) = O(N), O(100) = O(1)
2. **Drop lower-order terms:** O(N² + N) = O(N²), O(N log N + N) = O(N log N)

**Why?** For large N, the dominant term overwhelms everything else:

```
N = 1,000,000:
  N²     = 1,000,000,000,000
  N      =         1,000,000   ← less than 0.0001% of N²
  100    =               100   ← noise
```

The constant factor matters in practice (hardware, cache, etc.) but for asymptotic analysis — comparing algorithm classes — we ignore it.

---

## Analyzing Code — Rules

### Rule 1: Sequence of statements
Add the complexities:
```cpp
for (int i = 0; i < N; i++) { ... }   // O(N)
for (int i = 0; i < N; i++) { ... }   // O(N)
// Total: O(N) + O(N) = O(N)
```

### Rule 2: Nested loops
Multiply:
```cpp
for (int i = 0; i < N; i++)           // O(N)
    for (int j = 0; j < N; j++) { }   // O(N)
// Total: O(N) × O(N) = O(N²)
```

### Rule 3: If-else
Take the worst case:
```cpp
if (condition)
    O(N) block;
else
    O(N²) block;
// Total: O(N²)
```

### Rule 4: Logarithmic — halving the input
```cpp
int i = N;
while (i > 1) {
    i = i / 2;   // halves each time
}
// Total: O(log N)
```
After k iterations: N / 2^k = 1 → k = log₂N iterations.

### Full Example
```cpp
for (int i = 0; i < N; i++) {           // outer: N times
    for (int j = i; j < N; j++) {       // inner: N-i times
        sum += arr[j];
    }
}
```
Inner loop runs: N + (N-1) + (N-2) + ... + 1 = N(N+1)/2 = **O(N²)**

---

## Amortized Analysis

When a single operation is occasionally expensive but rarely so, we spread the cost across all operations.

**Example: dynamic array push_back**

| Push # | Cost | Why |
|--------|------|-----|
| 1 | 1 | just insert |
| 2 | 1 | just insert |
| 3 | 1+2=3 | insert + copy 2 elements (resize) |
| 4 | 1 | just insert |
| 5 | 1+4=5 | insert + copy 4 elements (resize) |
| 6,7,8 | 1 each | just insert |
| 9 | 1+8=9 | insert + copy 8 elements (resize) |

Total cost for N pushes = N + (1+2+4+...+N/2) = N + N - 1 ≈ 2N = **O(N)**

Amortized cost per operation = O(N)/N = **O(1)**

---

## Big-O vs Big-Ω vs Big-Θ — When to Use Each

| Symbol | Meaning | Use when... |
|--------|---------|-------------|
| O | Upper bound | Describing worst-case runtime (most common) |
| Ω | Lower bound | Proving a problem can't be solved faster |
| Θ | Tight bound | You know both upper and lower bounds match |

**Example for binary search:**
- O(log N) — worst case is log N comparisons
- Ω(1) — best case finds it immediately (target is the middle element)
- Θ(log N) is NOT correct for binary search because the best case is O(1), not O(log N)

**Example for merge sort:**
- O(N log N) — worst case
- Ω(N log N) — best case (even a sorted array requires N log N)
- Θ(N log N) — tight bound (best and worst are the same order)

---

## Key Takeaways

1. Big-O = upper bound (worst case). Big-Ω = lower bound (best case). Big-Θ = tight (both match).
2. Formal Big-O proof: find explicit **c** and **N₀** such that f(N) ≤ c·g(N) for all N ≥ N₀
3. Drop constants and lower-order terms — only the dominant term matters
4. Sequence → add. Nested loops → multiply. Halving → log N.
5. Amortized O(1) ≠ O(1) every time — it means O(1) on average over many operations
6. f(N) = Θ(g(N)) iff f(N) = O(g(N)) AND f(N) = Ω(g(N))
