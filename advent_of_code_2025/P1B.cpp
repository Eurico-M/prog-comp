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
    // cout << "- Dial starts at " << dial << ".\n";

    while (getline(cin, line)) {
        char dir = line[0];
        string nStr = line.substr(1);
        int n = stoi(nStr);

        // cout << "- Dial is rotated " << dir << n << "\n";
        
        if (dir == 'L') {
            n = -n;
        }

        int new_dial = dial + n;

        while (abs(new_dial) > 100) {

            if (new_dial * dial < 0 || new_dial > 100) {
                password++;
                // cout << "passed 0\n";
            }

            new_dial -= 100;
        }

        dial = new_dial;

        // cout << " goes to " << dial << "\n";

        dial = dial % 100;

        if (dial < 0) {
            dial += 100;
        }

        // cout << " which means " << dial << "\n";

        if (dial == 0) {
            password++;
        }

    }

    cout << "password is: " << password << "\n";

    return 0;
}