#include <bits/stdc++.h>
using namespace std;

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    map<int,int> events_pos;
    vector<int> b;

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        int event;
        cin >> event;

        if (events_pos.count(event) > 0) {
            b.push_back(events_pos[event]);
        } else {
            b.push_back(-1);
        }

        events_pos[event] = i;
    }

    cout << b[0];
    for (int i = 1; i < n; i++) {
        cout << " " << b[i];
    }
    cout << "\n";

    return 0;
}
