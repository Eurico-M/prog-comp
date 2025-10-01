#include <bits/stdc++.h>
using namespace std;

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    int x, n;
    cin >> x >> n;

    set<int> lights;
    lights.insert(0);
    lights.insert(x);

    for (int i = 0; i < n; i++) {
        int light;
        cin >> light;

        lights.insert(light);

        int longest_passage = 0;

        auto it = lights.begin();
        for (int i = 0; i < int(lights.size()) - 1; i++) {
            int a = *it;
            ++it;
            int b = *it;

            if (b - a > longest_passage) {
                longest_passage = b - a;
            }
        }

        cout << longest_passage << " ";
    }

    cout << "\n";

    return 0;
}
