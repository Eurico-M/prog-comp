#include <bits/stdc++.h>
using namespace std;

int n, m, k;

bool rhyme(string s1, string s2) {
    // cout << "rhyme " << s1 << " - " << s2 << "\n";
    int k1 = s1.length()-k;
    int k2 = s2.length()-k;
    // cout << "k1=" << k1 << " k2=" << k2 << "\n";

    if (k1 < 0 || k2 < 0) {
        return false;
    }

    for (int i = 0; i < k; i++) {
        if (s1[k1+i] == ' ' || s2[k2+i] == ' ' || s1[k1+i] != s2[k2+i]) {
            return false;
        }
    }

    return true;
}

int test_AABB(string s1, string s2, string s3, string s4) {
    if (rhyme(s1, s2) && rhyme(s3, s4)) {
        return 1;
    }
    return 0;
}

int test_ABAB(string s1, string s2, string s3, string s4) {
    if (rhyme(s1, s3) && rhyme(s2, s4)) {
        return 1;
    }
    return 0;
}

int test_ABBA(string s1, string s2, string s3, string s4) {
    if (rhyme(s1, s4) && rhyme(s2, s3)) {
        return 1;
    }
    return 0;
}

int main() {
    // Fast IO
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    //

    cin >> n >> m >> k;
    int n_AABB = 0, n_ABAB = 0, n_ABBA = 0;
    string junk;
    getline(cin, junk);

    for (int i = 0; i < n/4; i++) {
        string s1, s2, s3, s4;
        getline(cin, s1);
        getline(cin, s2);
        getline(cin, s3);
        getline(cin, s4);
        // cout << s1 << "\n";
        // cout << s2 << "\n";
        // cout << s3 << "\n";
        // cout << s4 << "\n";

        n_AABB += test_AABB(s1, s2, s3, s4);
        n_ABAB += test_ABAB(s1, s2, s3, s4);
        n_ABBA += test_ABBA(s1, s2, s3, s4);
    }

    cout << n_AABB << " " << n_ABAB << " " << n_ABBA << "\n";

    return 0;
}
