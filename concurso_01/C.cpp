#include <bits/stdc++.h>
using namespace std;

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    int n;
    cin >> n;
    list<string> names;
    for (int i = 0; i < n; i++) {
        string name;
        cin >> name;
        names.push_front(name);
    }

    set<string> skip;

    for (auto x : names) {
        if (skip.count(x) == 0) {
            cout << x << "\n";
            skip.insert(x);
        }
    }

    return 0;
}
