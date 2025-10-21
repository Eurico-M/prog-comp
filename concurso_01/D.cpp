#include <bits/stdc++.h>

using namespace std;

const int MAX = 200005;   // Capacity of Segment Tree
const int MAX_ST = MAX*4;

const tuple<int, int, int> NEUTRAL = {0,0,0};    // Neutral element

typedef tuple<int, int, int> st_value; // type of segment tree value

int n;               // Number of elements in the segtree
st_value v[MAX];     // Array of values
st_value st[MAX_ST]; // Segtree (in this case storing interval sums)

// Merge contents of nodes a and b
st_value merge(st_value a, st_value b) {
    int left_res, value_res, right_res;
    int left_a, value_a, right_a;
    int left_b, value_b, right_b;
    tie(left_a, value_a, right_a) = a;
    tie(left_b, value_b, right_b) = b;

    if (right_a == 1 && left_b == 1) {
        value_res = value_a + value_b;
        left_res = left_a;
        right_res = right_b;
    } else {
        value_res = max(value_a, value_b);
        if (value_a > value_b) {
            left_res = 1;
            right_res = 0;
        } else if (value_a < value_b) {
            left_res = 0;
            right_res = 1;
        } else {
            left_res = left_a;
            right_res = right_b;
        }
    }

    tuple<int,int,int> result;
    result = make_tuple(left_res, value_res, right_res);

    return result;

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

bool has_fortytwo(int n) {
    while (n > 10) {
        if (n == 42 || n % 100 == 42) {
            return true;
        } else {
            n = n / 10;
        }
    }
    return false;
}

int main() {
    int q;
    cin >> n >> q;

    for (int i=1; i<=n; i++) {
        int number;
        cin >> number;

        if (has_fortytwo(number)) {
            v[i] = {1,1,1};
            //cout << number << " has 42!\n";
        } else {
            v[i] = {0,0,0};
        }
    }

    build(1, 1, n);

    // cout << "Segtree (array):\n";
    // for (int x = 1; x <= 2 * n - 1; x++) {
    //     auto t = st[x];
    //     cout << x << ":[";
    //     cout << get<0>(t) << "," << get<1>(t) << "," << get<2>(t) << "] ";
    // }
    // cout << "\n";

    for (int i=1; i<=q; i++) {
        int op, a, b;
        cin >> op >> a >> b;
        if (op == 1) {
            int update_value;
            if (has_fortytwo(b)) {
                update_value = 1;
                //cout << b << " has 42!\n";
            } else {
                update_value = 0;
            }

            tuple<int,int,int> update_tuple = {update_value, update_value, update_value};
            update(1, 1, n, a, update_tuple);

        } else {
            tuple<int,int,int> q_result = query(1, 1, n, a, b);
            int result = get<1>(q_result);
            cout << result << endl;
        }
    }

    return 0;
}
