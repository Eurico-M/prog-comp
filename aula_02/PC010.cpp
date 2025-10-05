#include <bits/stdc++.h>
using namespace std;

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    int n, k;
    cin >> n >> k;

    vector<int> numbers;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        numbers.push_back(x);
    }

    for (int i = 0; i < n - k + 1; i++) {
        set<int> window;

        for (int j = 0; j < k; j++) {
            int x = numbers[i+j];
            window.insert(x);
        }

        auto it_smallest = window.begin();
        auto it_largest = window.end();
        it_largest--;

        int smallest = *it_smallest;
        int largest = *it_largest;

        cout << largest - smallest << " ";
    }

    cout << "\n";

    return 0;
}
