#include <bits/stdc++.h>
using namespace std;

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    string line;
    int dial = 50;
    int password = 0;

    while (getline(cin, line)) {
        char dir = line[0];
        string nStr = line.substr(1);
        int n = stoi(nStr);
        
        if (dir == 'L') {
            n = -n;
        }

        dial = (dial + n) % 100;

        if (dial == 0) {
            password++;
        }

    }

    cout << "password is: " << password << "\n";

    return 0;
}