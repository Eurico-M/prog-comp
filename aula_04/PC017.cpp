// Usar uma segtree para guardar o máximo.
//
// Fazer uma pesquisa binária na segtree para encontrar o valor mais à esquerda por defeito
// que for maior ou igual que o número de turistas que procura quarto.
//
// Fazer um update da segtree na posição encontrada na pesquisa anterior, com o valor da
// diferença entre o número de turistas e o número de quartos livres.
//
// O(n.log n)

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
    return max(a,b);
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
    for (int i=1; i<=n; i++) {
        int h;
        cin >> h;
        v[i] = h;
    }

    build(1, 1, n);

    for (int i = 0; i < q; i++) {
        int tourists;
        cin >> tourists;

        if (st[1] < tourists) {
            cout << 0;

        } else {
            // binary search na segment tree
            int cur = 1;
            int start = 1;
            int end = n;
            // cout << "start binary search cur=" << cur << "\n";
            while (start != end) {
                int middle = start + (end-start)/2;

                if (st[2 * cur] >= tourists) {
                    cur = 2 * cur;
                    end = middle;

                } else {
                    cur = 2 * cur + 1;
                    start = middle + 1;
                }
                // cout << "cur=" << cur << "\n";
            }

            cout << start;

            update(1, 1, n, start, st[cur] - tourists);

            // cout << "Segtree (array):\n";
            // for (int x = 1; x <= 2 * n - 1; x++) {
            //     cout << st[x] << " ";
            // }
            // cout << "\n";
        }

        if (i < q - 1) {
            cout << " ";
        }
    }

    cout << "\n";

    return 0;
}
