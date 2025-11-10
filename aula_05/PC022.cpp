#include <bits/stdc++.h>
using namespace std;

vector<int> tree;
int maxIdx;

void print_vector(vector<int> v) {
    cout << "[";
    for (auto k : v) {
        cout << " " << k;
    }
    cout << " ]\n";
}

int read(int idx) {
    int sum = 0;
    while (idx > 0) {
        sum += tree[idx];
        idx -= (idx & -idx);
    }
    return sum;
}

void update(int idx, int val) {
    while (idx <= maxIdx) {
        tree[idx] += val;
        cout << "tree[" << idx << "]=" << tree[idx] << "\n";
        idx += (idx & -idx);
    }
}

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    int n, m, k;
    cin >> n >> m >> k;

    maxIdx = m;
    multimap<int,int> roads;
    tree.assign(m+1, 0);

    for (int i = 0; i < k; i++) {
        int n1, m1;
        cin >> n1 >> m1;
        roads.insert({n1, m1});
    }


    int crossing_sum = 0;
    for (auto x : roads) {
        cout << "{ " << x.first << " , " << x.second << " }\n";
        crossing_sum += read(x.second);
        cout << "crossing_sum=" << crossing_sum << "\n";
        update(x.second, 1);
        print_vector(tree);
    }

    cout << crossing_sum << "\n";

    return 0;
}
