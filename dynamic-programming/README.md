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
## Classic Dynamic Programming problems:
- Unbounded Knapsack (repeating items)
- 0/1 Knapsack
- Fractional Knapsack
- Largest Increasing Subsequence (LIS)
- Fibonacci-style/Combinatorics problems
- MCM
- Longest Common Substring (LCS)
### 0/1 Knapsack:
Sources: [geeksforgeeks](https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/) | [back to back SWE's video](https://youtu.be/xCbYmUPvc2Q) | [CSDojo's video](https://youtu.be/xOlhR_2QCXY)

Using the framework for solving this kind of problem, we'll define the object function for this problem. That would be ``f(n, C)`` that would give us the maximum total value in the knapsack with capacity C and number of items n.

The base cases would be:

When n = 0-i.e., when the number of items would be zero. In that case our maximum value would also be zero.

When C = 0-i.e, when the knapsack's capacity is equal do zero. In that case we cannot store any items so our maximum value would also be zero. So we have:
```
f(0, C) = 0 ; for any C
f(n, 0) = 0 ; for any n
```
We also have a constraint: the item can only be stored if it fits the knapsack, otherwise we cannot use it:
```
if weight[n] > C : return f(n-1, C)
```
Now we have to find the recurrence relation that solves one subproblem and extend it. The recurrence relation is as follows:

We have to maximize between two choices: we either use the current item or we don't use it.

So it would be roughly: ``max(includeIth, excludeIth)``

When we use the item we're gonna add its value and reduce its weight from the capacity:
```
includeIth = value[n] + f(n-1, C - weight[n])
```
When we don't use it we just reduce number of items by one:
```
excludeIth = f(n-1, C)
```
So our recurrence relation would be:
```
f(n, C) = max(value[n] + f(n-1, C - weight[n]), f(n-1, C))
```
To turn it into a dynamic programming solution we'd use a 2 dimensional table to store our previous work in cache[n+1][C+1]<br>
The order could be top down or bottom up, its up to you.

Using this recurrence relation with prefixes ``(n-1)`` the order of execution for the outer loop is from ``0 to n-1``  and from ``0 to C-1`` for the nested loop.

The answer is at ``f(n, C)``

We could also use suffixes ``(n+1)``, the difference would be that our order of execution for the outer loop would be from ``n-1 to 0`` and our answer would be at ``f(0, C)``

Top down C++ implementation using recursion:
``` C++
int knapSack(int numItems, int capacity, int weight[], int value[], int cache[][]) {
  int result;
  // using our cache table to remember
  if (cache[numItems][capacity] != -1)
    return cache[numItems][capacity];
  // base cases
  if (numItems == 0 || capacity == 0)
    result = 0;
  // if it weighs more than capacity we cannot use the item
  else if (weight[numItems-1] > capacity)
    result = knapSack(numItems - 1, capacity, weight, value, cache);
  else {
    int includeIth, excludeIth;
    includeIth = value[numItems-1] + knapSack(numItems - 1, capacity - weight[numItems - 1], weight, value, cache);
    excludeIth = knapSack(numItems - 1, capacity, weight, value, cache);
    result = max(includeIth, excludeIth);
  }
  cache[numItems][capacity] = result;
  return result;
}

int main () {
  int numItems, capacity;
  cin >> numItems >> capacity;
  int weight[numItems+1];
  int value[numItems+1];
  int cache[numItems+1][capacity+1];
  
  // set dummy value to cache
  memset(cache, -1, sizeof(cache));

  // get input
  for(int i = 0; i < numItems; i++)
    cin >> weight[i] >> value[i];
    
  cout << knapSack(numItems, capacity, weight, value, cache) << endl;
  return 0;
}
```

Bottom up C++ implementation:
``` C++
// time: O(n*C)
// space: O(n*C)
int knapSack(int numItems, int capacity, int weight[], int value[]) {
  int result, includeIth, excludeIth, currWeight, currValue;
  int cache[numItems+1][capacity+1];
  // initialize cache
  memset(cache, 0, sizeof(cache));
  
  for(int i = 0; i <= numItems; i++) {
    for(int w = 0; w <= capacity; w++) {
      currWeight = weight[i-1];
      currValue = value[i-1];
      // base cases
      if (i == 0 || w == 0)
        cache[i][w] = 0;
      // if it weighs more than capacity we cannot use the item
      else if (currWeight > w)
        cache[i][w] = cache[i-1][w];
      else {
        includeIth = currValue + cache[i-1][w - currWeight];
        excludeIth = cache[i-1][w];
        cache[i][w] = max(includeIth, excludeIth);
      }
    }
  }
  
  result = cache[numItems][capacity];
  return result;
}

int main () {
  int numItems, capacity;
  cin >> numItems >> capacity;
  int weight[numItems+1];
  int value[numItems+1];

  // get input
  for(int i = 0; i < numItems; i++)
    cin >> weight[i] >> value[i];
    
  cout << knapSack(numItems, capacity, weight, value) << endl;
  return 0;
}
```
## How to find our solution?
One way to find our solution is iterate through our memoization table. We define a vector to store our solution. If our solution includes the last item then we add it to the vector and decrease its weight from the capacity, if not we keep looking. We keep looping while our iterator and the current capacity are greater than zero:
``` C++
vector<int> solution;

// populate solution:
for (int i = numItems, w = capacity; i > 0 && w > 0; i--) {
  currWeight = weights[i-1];
  currValue = profits[i-1];

  include = currValue + cache[i-1][w-currWeight];

  if (cache[i][w] == include) {
    solution.push_back(currWeight);
    w -= currWeight;
  }
}
```
## Optimizing space
If you take a closer look at the code, you'll notice that in any given iteration we are only using the rows `cache[i]` and `cache[i-1]`. That means that instead of using n+1 rows we can answer the problem with only 2 rows. However we have to copy the second row into the first one at every iteration of the inner loop:
``` C++
// time: O(n*C)
// space: O(C)
int knapSack(int numItems, int capacity, int weight[], int value[]) {
  int result, includeIth, excludeIth, currWeight, currValue;
  vector<vector<int>> cache(2, vector<int>(capacity+1));
  
  for(int i = 1; i <= numItems; i++) {
    for(int w = 1; w <= capacity; w++) {
      if(w != 1) cache[0] = cache[1];
      currWeight = weight[i-1];
      currValue = value[i-1];
      // if it weighs more than capacity we cannot use the item
      if (currWeight > w)
        cache[1][w] = cache[0][w];
      else {
        includeIth = currValue + cache[0][w - currWeight];
        excludeIth = cache[0][w];
        cache[1][w] = max(includeIth, excludeIth);
      }
    }
  }
  
  result = cache[1][capacity];
  return result;
}

```
We can optimize this code even more using pointers so we don't have to spend linear time copying the array:
``` C++
// time: O(n*C)
// space: O(C)
int knapSack(int numItems, int capacity, int weight[], int value[]) {
  int result, includeIth, excludeIth, currWeight, currValue;
  vector<vector<int>> cache(2, vector<int>(capacity+1));
  vector<int> *ptr0, *ptr1, *aux;
  
  for(int i = 1; i <= numItems; i++) {
    for(int w = 1; w <= capacity; w++) {
      if(w != 1) {
        aux = ptr0;
        ptr0 = ptr1;
        ptr1 = aux;
      }
      currWeight = weight[i-1];
      currValue = value[i-1];
      // if it weighs more than capacity we cannot use the item
      if (currWeight > w)
        (*ptr1)[w] = (*ptr0)[w];
      else {
        includeIth = currValue + (*ptr0)[w - currWeight];
        excludeIth = (*ptr0)[w];
        (*ptr1)[w] = max(includeIth, excludeIth);
      }
    }
  }
  
  result = (*ptr1)[capacity];
  return result;
}

```
