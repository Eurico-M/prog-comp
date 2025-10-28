#include <bits/stdc++.h>
using namespace std;

bool crossing(pair<int,int> p1, pair<int,int> p2) {
    if ((p1.first-p2.first) * (p1.second-p2.second) < 0) {
        return true;
    }
    return false;
}

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    int n, m, k;
    cin >> n >> m >> k;

    vector<pair<int,int>> roads;

    for (int i = 0; i < k; i++) {
        int n1, m1;
        cin >> n1 >> m1;
        roads.push_back({n1,m1});
    }

    for (int i = 0; i < k; i++) {
        for (int j = i + 1; j < k; j++) {
            pair<int,int> pair_1 = roads[i];
            pair<int,int> pair_2 = roads[j];
            cout << "checking (" << pair_1.first << "," << pair_1.second << ") with";
            cout << " (" << pair_2.first << "," << pair_2.second << "): ";
            bool cross = crossing(pair_1, pair_2);
            if (cross) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }

    return 0;
}
