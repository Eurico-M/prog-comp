#include <bits/stdc++.h>
using namespace std;

int main() {

    int n;
    cin >> n;

    string prev;
    cin >> prev;

    for (int i = 0; i < n-1; i++) {
        string curr;
        cin >> curr;

        for (int j = 0; j < min(prev.length(), curr.length()); j++) {
            if (prev[j] != curr[j]) {
                update(graph, prev[j], curr[j]);
            }
        }
    }
    return 0;
}