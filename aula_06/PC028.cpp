#include <bits/stdc++.h>
using namespace std;

vector<int> seq;
vector<int> dp;
int n;

void print_vector(vector<int> &v) {
    cout << "[";
    for (auto x : v) {
        cout << " " << x;
    }
    cout << " ]\n";
}

void receive_numbers() {
    seq.clear();
    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        seq.push_back(num);
    }
}

void configure_dp() {
    dp.clear();
    dp.assign(n, -1);
    dp[0] = 1;
}

int lis_rec(int idx) {
    if (idx == 0 || dp[idx] != -1) {
        return dp[idx];
    }

    int max_temp = 0;
    for (int i = 0; i < idx; i++) {
        if (seq[i] < seq[idx]) {
            max_temp = max(max_temp, 1 + lis_rec(i));
        }
    }
    dp[idx] = max_temp;
    return max_temp;
}

int lis() {

    int res = -1;
    for (int i = 0; i < n; i++) {
        res = max(res, lis_rec(i));
    }
    return res;
}

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    int n_tests;
    cin >> n_tests;

    for (int i = 0; i < n_tests; i++) {
        cin >> n;
        receive_numbers();
        configure_dp();

        cout << lis() << "\n";
        print_vector(seq);
        print_vector(dp);
    }

    return 0;
}
