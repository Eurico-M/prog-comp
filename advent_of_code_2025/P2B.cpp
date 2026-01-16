#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Verificar se um ID é inválido.
// Converter o ID numa string, separar a string ao meio (se o tamanho for ímpar automaticamente
// não é inválido) e comparar as duas metades.
bool invalidID(ll n) {
    string str_n = to_string(n);
    int str_length = str_n.length();

    if (str_length % 2 != 0) {
        return false;
    }

    ll half = str_length/2;
    string frst = str_n.substr(0, half);
    string scnd = str_n.substr(half);

    for (ll k = 0; k < half; k++) {
        if (frst[k] != scnd[k]) {
            return false;
        }
    }

    return true;
}

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    string range;
    ll answer = 0;

    // Ler os ranges separados por ',' (11-22)
    while (getline(cin, range, ',')) {
        // cout << "range: " << range << "\n";
        // Encontrar o sinal '-'
        ll sep = 0;
        while (range[sep] != '-') {
            sep++;
        }
        // Separar as substrings de cada número e converter para ll
        ll left = stoll(range.substr(0, sep));
        ll right = stoll(range.substr(sep+1));
        // cout << "   left: " << left << " right: " << right << "\n";

        // Percorrer o range e ir somando os IDs inválidos
        for (ll n = left; n <= right; n++) {
            if (invalidID(n)) {
                answer += n;
                // cout << "       inválido: " << n << "\n";
            }
        }
    }

    cout << "resposta: " << answer << "\n";

    return 0;
}