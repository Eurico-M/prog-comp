#include <iostream>
#include <set>
using namespace std;

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    int x, n;
    cin >> x >> n;
    cout << "test" << "\n";

    set<int> lights;
    lights.insert(0);
    lights.insert(x);

    for (int i = 0; i < n; i++) {
        int light;
        cin >> light;

        lights.insert(light);

        int longest_passage = 0;
        int prev = *lights.begin();
        cout << "--- i = " << i << "\n";
        cout << "prev = " << prev << "\n";

        for (auto it = ++lights.begin(); it != lights.end(); i++) {
            int cur = *it;
            cout << "cur = " << cur << "\n";
            int passage = cur - prev;
            if (passage > longest_passage) {
                longest_passage = passage;
            }
            prev = cur;
        }

        cout << longest_passage << " ";
    }

    cout << "\n";

    return 0;
}
