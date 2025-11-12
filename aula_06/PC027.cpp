
#include <bits/stdc++.h>
using namespace std;


int smokeless(vector<int> &m, int i, int j) {
    if (i == j) {
        return 0;
    }

    int res = INT_MAX;
    for (int k = i; k < j; k++) {

        min_cost = min(min_cost, smokeless(m, i, k))
    }
}

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    int n_tests;
    cin >> n_tests;

    for (int i = 0; i < n_tests; i++) {
        int n_mixtures;
        cin >> n_mixtures;

        vector<int> mixtures (n_mixtures + 1);

        for (int j = 1; j <= n_mixtures; j++) {
            int m;
            cin >> m;
            mixtures.push_back(m);
        }

        cout << smokeless(mixtures, 1, n_mixtures) << "\n";
    }

    return 0;
}
