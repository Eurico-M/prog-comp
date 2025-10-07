// Example solution for CSES: Dynamic Range Sum Queries
// Pedro Ribeiro (DCC/FCUP)
// O((n+q) log n) using segment trees (with arrays)

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
