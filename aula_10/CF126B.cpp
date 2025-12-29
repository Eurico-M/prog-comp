// Aplicar KMP
//
// Depois de receber a string original, calcular a sua função Pi.
// Sabendo o valor do prefixo/sufixo maior (é o valor na última posição de Pi),
// criar uma string possível de ser a nossa resposta.
// Já sabemos que obedece às condições de sufixo e prefixo (é isso que a função Pi faz).
// Para descobrir se é infixo, correr KMP da string possível na string original.
//
// KMP foi aplicado quase directamente dos slides, com as modificações:
// 1) Usar indexação 0,
// 2) Em vez de imprimir que "foi encontrado padrão com shift etc.", queremos apenas
// retornar verdadeiro se o padrão acontecer (obviamente) mas também se acontecer para além
// de acontecer no início e no fim da string original.
// 
// Se não ocorrer, temos de verificar se a string possível contém ela própria sufixos/prefixos.
// Por exemplo, a string qwertyqwertyqwerty tem como possível resposta qwertyqwerty. Mas qwertyqwerty não
// cumpre as nossas 3 condições (prefixo, sufixo, infixo).
// Mas qwerty cumpre. Por isso temos um ciclo que transforma a nossa string possível em strings cada vez
// mais pequenas que têm prefixos que são sufixos.


#include <bits/stdc++.h>
using namespace std;

void print_pi(string p, vector<int> pi) {
    for (auto c : p) {
        cout << " " << c;
    }
    cout << "\n";
    for (auto i : pi) {
        cout << " " << i;
    }
    cout << "\n";
}

vector<int> compute_prefix(string p) {
    int m = p.length();
    vector<int> pi(m,0);
    int k = 0;

    for (int q = 1; q < m; q++) {
        while (k > 0 && p[k] != p[q]) {
            k = pi[k-1];
        }
        if (p[k] == p[q]) {
            k++;
        }
        pi[q] = k;
    }

    return pi;
}

// procurar padrão p na string t
bool kmp(string t, string p) {
    int n = t.length();
    int m = p.length();
    // se o sufixo for vazio, não ocorre
    if (m == 0) return false;
    vector<int> pi = compute_prefix(p);
    int q = 0;

    for (int i = 0; i < n; i++) {
        while (q > 0 && p[q] != t[i]) {
            q = pi[q-1];
        }
        if (p[q] == t[i]) {
            q = q + 1;
        }
        if (q == m) {
            int start_pos = i - m + 1;
            // cout << "found " << p << " in " << t << " with shift " << start_pos << "\n";
            //se o padrão for todo igual e não estiver no início nem no fim
            if (start_pos > 0 && start_pos < n - m) return true;
            q = pi[q-1];
        }
    }
    return false;
}

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    string original;
    cin >> original;

    string possible = original;

    // calcular respostas possíveis, começando pela maior e ir diminuindo
    do {
        vector<int> pi = compute_prefix(possible);
        int l = possible.length();
        possible = possible.substr(l-pi[l-1], pi[l-1]);
        
        if (kmp(original, possible)) {
            cout << possible << "\n";
            return 0;
        }
    } while (possible.length() > 0);

    cout << "Just a legend\n";
    return 0;
}