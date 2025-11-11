#include <bits/stdc++.h>
using namespace std;

#define INF -1000001

void print_vector(vector<int> v) {
    cout << "[";
    for (auto x : v) {
        cout << " " << x;
    }
    cout << " ]\n";
}

void print_matrix(vector<vector<int>> m) {
    for (auto x: m) {
        print_vector(x);
    }
}

void receive_seq(vector<int> &seq, int sz) {
    for (int i = 0; i < sz; i++) {
        int num;
        cin >> num;
        seq.push_back(num);
    }
}


int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    int n;
    cin >> n;
    vector<int> alice_seq;
    receive_seq(alice_seq, n);

    int m;
    cin >> m;
    vector<int> bob_seq;
    receive_seq(bob_seq, m);

    // cout << "checking vectors:\n";
    // print_vector(alice_seq);
    // print_vector(bob_seq);

    vector<vector<int>> dp (n+1, vector<int>(m+1, INF));

    // print_matrix(dp);

    // longest common subsequence Bottom-Up DP (Tabulation) (geeks for geeks)
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int multiplication = alice_seq[i-1] * bob_seq[j-1];
            if (multiplication > 0 || multiplication > dp[i][j-1]) {
                if (dp[i-1][j-1] < 0) {
                    dp[i][j] = multiplication;
                }
                else {
                    dp[i][j] = dp[i-1][j-1] + multiplication;
                }
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }

    //print_matrix(dp);

    cout << dp[n][m] << "\n";

    return 0;
}
