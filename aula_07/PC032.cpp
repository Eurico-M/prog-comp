#include <bits/stdc++.h>
using namespace std;


void print_track(const int k, const vector<int> &t) {
    cout << "Track #" << k << "\n";
    for (int i = 0; i < (int)t.size(); i++) {
        cout << i;
        if (i < 10) {
            cout << "  ";
        }
        else {
            cout << " ";
        }
        cout << t[i] << "\n";
    }
    cout << "\n";
}


int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    int n_tests;
    cin >> n_tests;

    for (int i = 0; i < n_tests; i++) {
        int acc, brk;
        cin >> acc >> brk;

        vector<int> track = {0};
        int n, v;
        cin >> n >> v;
        while (n != 0) {
            for (int k = 0; k < n; k++) {
                track.push_back(v);
            }
            cin >> n >> v;
        }
        // print_track(i+1, track);
        vector<vector<int>> dp ((int)track.size(), vector<int> ((int)acc/10 + 1, -1));
    }

    return 0;
}
