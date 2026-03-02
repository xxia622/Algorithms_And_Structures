### Order of Execution in Recursion

| Code Position | Phase | Execution Order |
| :--- | :--- | :--- |
| `cout` before `fun()` | Calling Phase | Ascending/Descending (Top-Down) |
| `cout` after `fun()` | Returning Phase | Reversed Order (Bottom-Up) |

**Key Insight**: In the returning phase, the values are printed as the function calls are popped from the stack, which is why the order is reversed.

Recursion has two phases: calling phase and returning phase

void fun(int n) {
    if (n > 0) {
        std::cout << n << " "; 
        fun(n - 1);       
    }
}
// n = 3 Output: 3 2 1

void fun(int n) {
    if (n > 0) {
        fun(n - 1);       
        cout << n << " "; 
    }
}
// n = 3 Output: 1 2 3
