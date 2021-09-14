# Dynamic Programming
## Dynamic Programming types of problems:
- Combinatoric problems
- Optimization problems
- Problems that ask if something is possible or not
## Framework for solving dynamic programming problems:
- Define the object function
- Identify base cases:
They're usually given in the problem statement.
- Write down a recurrence relation for the optimized objective function:
Consider you're at some position. Does it matter how you've got there? If not, use your position as the dimension for the cache array.
```C++
int cache[position]
// if it's a problem involving a grid:
int cache[row][col]
```
- What's the order of execution?
- Where to look for the answer?

