#include <bits/stdc++.h>
#include <cctype>
using namespace std;



int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    bool alphabetical = true;
    bool rev_alphabetical = true;
    string word;
    cin >> word;

    char prev = tolower(word[0]);
    string reversed = "";
    reversed.insert(0, 1, tolower(word[0]));

    for (int i = 1; i < (int)word.length(); i++) {
        char cur = word[i];
        reversed.insert(0, 1, word[i]);
        // cout << "i=" << i << " cur: " << cur << "\n";
        if (cur < prev) {
            alphabetical = false;
        }
        prev = cur;
    }

    // cout << "word: " << word << "\n";
    // cout << "reversed: " << reversed << "\n";

    char rev_prev = tolower(reversed[0]);
    for (int i = 1; i < (int)reversed.length(); i++) {
        char rev_cur = reversed[i];
        if (rev_cur < rev_prev) {
            rev_alphabetical = false;
        }
        rev_prev = rev_cur;
    }

    if (!alphabetical && !rev_alphabetical) {
        cout << "no\n";
    } else {
        cout << "yes\n";
    }

    return 0;
}
