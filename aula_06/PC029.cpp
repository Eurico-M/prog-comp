#include <bits/stdc++.h>
using namespace std;

string s1;
string s2;

int rec_ed(int k) {
    if (k == -1) {
        return 0;
    }
    if (s1[k] == s2[k]) {
        return rec_ed(k-1);
    }
    return 1 + rec_ed(k-1);
}

int ed() {
    int l = s1.length();
    return rec_ed(l-1);
}

int main() {
    // receber número de testes
    int t;
    cin >> t;
    // em cada teste
    for (int i = 0; i < t; i++) {
        // receber string
        string s;
        cin >> s;
        // partir a string ao meio, guardar a primeira metade em s1,
        // e a segunda metade em s2, mas invertida.
        // assim, o problema transforma-se no edit distance básico.
        int l = s.length();
        s1.clear();
        s2.clear();
        for (int j = 0; j < l/2; j++) {
            s1.insert(j, 1, s[j]);
            s2.insert(j, 1, s[l-1-j]);
        }

        cout << "s: " << s << "\n";
        cout << "s1: " << s1 << "\n";
        cout << "s2: " << s2 << "\n";

        cout << ed() << "\n";

    }

    return 0;
}
