#include <bits/stdc++.h>
using namespace std;

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int a, b, k;
        cin >> a >> b >> k;

        int posicao = 0;
        if (k % 2 == 0) {
            posicao = a*(k/2) - b*(k/2);
        } else {
            posicao = a*(k/2 + 1) - b*(k/2);
        }
        cout << posicao << "\n";
    }

    return 0;
}
