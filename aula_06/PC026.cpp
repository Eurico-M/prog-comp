#include <bits/stdc++.h>
#include <vector>
using namespace std;

#define INF 1000001
#define OFFSET 1000

vector<int> alice_seq;
vector<int> bob_seq;
vector<vector<int>> dp;

void print_vector(vector<int> &v) {
    cout << "[";
    for (auto x : v) {
        cout << " " << x;
    }
    cout << " ]\n";
}

void print_matrix(vector<vector<int>> &m) {
    for (auto x: m) {
        print_vector(x);
    }
}

void receive_seq(vector<int> &seq, int sz) {
    seq.push_back(-INF);
    for (int i = 1; i <= sz; i++) {
        int num;
        cin >> num;
        seq.push_back(num);
    }
}

int lcs_rec(int i, int j) {
    if (i == 0 || j == 0) {
        return -INF;
    }

    if (dp[i][j] != -INF) {
        return dp[i][j];
    }

    int use_both;
    if (lcs_rec(i-1, j-1) == -INF) {
        use_both = alice_seq[i] * bob_seq[j];
    } else {
        use_both = alice_seq[i] * bob_seq[j] + lcs_rec(i-1, j-1);
    }

    return dp[i][j] = max(use_both, max(lcs_rec(i, j-1), lcs_rec(i-1,j)));
}

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    int n;
    cin >> n;
    receive_seq(alice_seq, n);

    int m;
    cin >> m;
    receive_seq(bob_seq, m);

    dp.assign(n+1, vector<int> (m+1, -INF));

    // cout << "checking vectors:\n";
    // print_vector(alice_seq);
    // print_vector(bob_seq);
    // cout << "dp:\n";
    // print_matrix(dp);

    cout << lcs_rec(n, m) << "\n";

    return 0;
}
