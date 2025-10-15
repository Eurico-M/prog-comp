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

void print_seg_tree() {
    cout << "SegTree:\n";
    int level = 0;
    while (level <= (n / 2)) {
        int nr_nodes = pow(2,level);
        int node_number = nr_nodes;
        for (int i = 0; i < nr_nodes; i++) {
            cout << st[node_number] << " ";
            node_number++;
        }
        cout << "\n";
        level++;
    }
    cout << "----------\n";
}

// ---------------------------------------------------------

int main() {
    int q;
    cin >> n >> q;
    vector<int> sequence;
    sequence.push_back(0); // sentinela para sequence[0]

    for (int i = 0; i < n; i++) {
        int number;
        cin >> number;
        sequence.push_back(number);
    }

    for (int i = 0; i < q; i++) {
        int a, b, k;
        cin >> a >> b >> k;

        // cout << "sequence: ";
        // for (auto x : sequence) {
        //     cout << x << " ";
        // }
        // cout << "\n";

        // construir array v como se fosse um booleano (>k)
        for (int j = 1; j <= n; j++) {
            if (sequence[j] > k) {
                v[j] = 1;
            } else {
                v[j] = 0;
            }
        }

        build(1, 1, n);
        // print_seg_tree();
        // cout << "st array: ";
        // for (int x = 1; x <= 3*n; x++) {
        //     cout << st[x] << " ";
        // }
        // cout << "\n";

        cout << query(1, 1, n, a, b) << "\n";
    }

    return 0;
}
