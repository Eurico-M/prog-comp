#include <bits/stdc++.h>
using namespace std;

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    int n, w;
    cin >> n >> w;

    vector<int> heights;

    for (int i = 0; i < n; i++) {
        int h;
        cin >> h;
        heights.push_back(h);
    }

    sort(heights.begin(), heights.end());

    string possible = "yes\n";
    for (int i = 0; i < n; i++) {
        if ((i+w < n) && (heights[i] >= heights[i+w])) {
            possible = "no\n";
            break;
        }
    }

    cout << possible;

    return 0;
}
