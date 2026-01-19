#set page(
  paper: "a4",
  flipped: true,
  columns: 2
)

#set text(
  size: 8pt
)

== Counting Sort

```
count[max size] ← frequencies array
For i = 0 to n − 1 do
  count[v [i]] + + (one more v[i] element)
i = 0
For j = min size to max size do
  While count[j] > 0 do
    v [i] = j (put element on array)
    count[j] −− (one less element of that size)
    i + + (increments first free position on the array)
```
== A possible RadixSort (starting on the least significant digit)
```
bucket[10] ← array of lists of numbers (one per digit)
For pos = 1 to max number digits do
  For i = 0 to n − 1 do (for each number)
    Put v [i]in bucket[digit position pos(v [i])]
  For i = 0 to 9 do (for each possible digit)
    While size(bucket[i]) > 0 do
      Take first number of bucket[i] and add it to v []
```
== Binary search on a sorted array
```
bsearch(v, low, high, key)
  While (low ≤ high ) do
    middle = low + (high − low )/2
    If (key == v [middle]) return(middle)
    Else If (key < v [middle]) high = middle − 1
    Else low = middle + 1
  return(-1)
```
== Binary search for smallest k such that condition(k) is ”yes”
```
bsearch(low, high, condition)
While (low < high ) do
  middle = low + (high − low )/2
  If (condition(middle) == yes)) high = middle
  Else low = middle + 1
If (condition(low ) == no) return(-1)
return(low)
```
== Ternary search
```
// a: left edge of interval
// b: right edge of interval
// f: function
// epsilon: tolerance
input a, b, f, epsilon
l ← a
r ← b
while (r-l > epsilon)
    m1 ← (2*l + r)/3
    m2 ← (l + 2*r)/3
    if f(m1) < f(m2)
        l ← m1
    else
        r ← m2
print r
```
== Segment tree
```cpp
// Pedro Ribeiro (DCC/FCUP)

#include <bits/stdc++.h>
using namespace std;

// -----------------------------------------------------------------
// An example simple segment tree implementation with arrays
// -----------------------------------------------------------------

const int MAX = 200005;   // Capacity of Segment Tree
const int MAX_ST = MAX*4;

const int NEUTRAL = 0;    // Neutral element

typedef int64_t st_value; // type of segment tree value

int n;               // Number of elements in the segtree
st_value v[MAX];     // Array of values
st_value st[MAX_ST]; // Segtree (in this case storing interval sums)

// Merge contents of nodes a and b
st_value merge(st_value a, st_value b) {
  return a+b;
}

// Build initial segtree (in position pos, interval [start,end])
void build(int pos, int start, int end) {
  if (start == end) {
    st[pos] = v[start];
  } else {      
    int middle = start + (end-start)/2;
    build(pos*2, start, middle);
    build(pos*2+1, middle+1, end);
    st[pos] = merge(st[pos*2], st[pos*2+1]);
  }  
}

// Update node n to value v
void update(int pos, int start, int end, int n, st_value v) {
  if (start > n || end < n) return;
  if (start == end) {
    st[pos] = v;
  } else {      
    int middle = start + (end-start)/2;
    update(pos*2, start, middle, n, v);
    update(pos*2+1, middle+1, end, n, v);
    st[pos] = merge(st[pos*2], st[pos*2+1]);
  }  
}

// Make a query of interval [a,b]
st_value query(int pos, int start, int end, int a, int b) {
  if (start>b || end<a) return NEUTRAL;
  if (start>=a && end<=b) return st[pos];
  
  int middle = start + (end-start)/2;
  st_value l = query(pos*2, start, middle, a, b);
  st_value r = query(pos*2+1, middle+1, end, a, b);
  return merge(l, r);
}

// ---------------------------------------------------------

int main() {
  int q;
  cin >> n >> q;
  for (int i=1; i<=n; i++)
    cin >> v[i];
    
  build(1, 1, n);

  for (int i=1; i<=q; i++) {
    int op, a, b;
    cin >> op >> a >> b;
    if (op == 1) update(1, 1, n, a, b);
    else cout << query(1, 1, n, a, b) << endl;
  }
  
  return 0;
}
```
== Binary Indexed Tree
```cpp
vector<int> tree;
int maxIdx;

int read(int idx) {
  int sum = 0;
  while (idx > 0) {
    sum += tree[idx];
    idx -= (idx & -idx);
  }
  return sum;
}

void update(int idx, int val) {
  while (idx <= MaxIdx) {
    tree[idx] += val;
    idx += (idx & -idx);
  }
}

int sum(int l, int r) { // Range Query
  return read(r) - read(l - 1);
}

int readSingle(int idx) { // Read the actual number, not cumulative 
  int sum = tree[idx]; // this sum will be decreased
  if (idx > 0) { // the special case
    int z = idx - (idx & -idx);
    idx--; // idx is not important anymore, so instead y, you can use idx
    while (idx != z) { // at some iteration idx (y) will become z
      sum -= tree[idx];
      // substruct tree frequency which is between y and "the same path"
      idx -= (idx & -idx);
    }
  }
  return sum;
}

void scale(int c) { // Scale entire tree by c
  for (int i = 1; i <= MaxIdx; i++)
    tree[i] = tree[i] / c;
}

```
== Kadane
```py
def max_subarray(numbers):
    """Find the largest sum of any contiguous subarray."""
    best_sum = float('-inf')
    current_sum = 0
    for x in numbers:
        current_sum = max(x, current_sum + x)
        best_sum = max(best_sum, current_sum)
    return best_sum
```
