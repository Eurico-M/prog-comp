#include <bits/stdc++.h>
using namespace std;

int n, m, k, x;
map<int, string> replacements;
vector<int> index_illegibles;
set<string> possibilities;

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    cin >> n >> m >> k >> x;
    string word;
    cin >> word;
    possibilities.insert(word);

    for (int i = 0; i < (int)word.length(); i++) {
        if (word[i] == '#') {
            index_illegibles.push_back(i);
        }
    }

    for (int i = 0; i < m; i++) {
        string replacement;
        cin >> replacement;
        replacements[index_illegibles[i]] = replacement;
    }

    // for (auto x : replacements) {
    //     cout << "indice: " << x.first << " hipoteses: " << x.second << "\n";
    // }




    return 0;
}
