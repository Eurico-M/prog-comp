#include <bits/stdc++.h>

using namespace std;

const int MAX = 200005;   // Capacity of Segment Tree
const int MAX_ST = MAX*4;

const vector<int> NEUTRAL = {};    // Neutral element

typedef vector<int> st_value; // type of segment tree value

int n;               // Number of elements in the segtree
st_value v[MAX];     // Array of values
st_value st[MAX_ST]; // Segtree (in this case storing interval sums)

int max_middle(vector<int> v, int t) {
    int max = t;
    for (auto it = v.begin() + 1; it < v.end() - 1; it++) {
        if (*it > max) {
            max = *it;
        }
    }
    return max;
}

// Merge contents of nodes a and b
st_value merge(st_value a, st_value b) {
    vector<int> r_temp;

    for (auto x : a) {
        r_temp.push_back(x);
    }
    for (auto x : b) {
        r_temp.push_back(x);
    }

    vector<int> r;
    int last_a = a.size() - 1;
    int first_b = a.size();
    int temp_max = 0;

    if (r_temp[last_a] > 0 && r_temp[first_b] > 0) {
        temp_max = r_temp[last_a] + r_temp[first_b];
        r_temp.erase(r.begin() + last_a, r.begin() + first_b + 1);
    }

    int max = max_middle(r_temp, temp_max);

    r.push_back(r_temp.front());
    r.push_back(max);
    r.push_back(r_temp.back());

    return r;
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

int max_vector(vector<int> v) {
    int m = 0;
    for (auto x : v) {
        if (x > m) {
            m = x;
        }
    }
    return m;
}


int main() {
    int q;
    cin >> n >> q;

    for (int i=1; i<=n; i++) {
        int number;
        cin >> number;

        if (has_fortytwo(number)) {
            v[i] = {1};
            //cout << number << " has 42!\n";
        } else {
            v[i] = {0};
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

            vector<int> update_vector = {update_value};
            update(1, 1, n, a, update_vector);

        } else {
            vector<int> q_result = query(1, 1, n, a, b);
            cout << max_vector(q_result) << endl;
        }
    }

    return 0;
}
