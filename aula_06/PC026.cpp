// Dinamic Programming com memoization

#include <bits/stdc++.h>
using namespace std;

#define INF 1e6 + 4

vector<int> alice_seq;
vector<int> bob_seq;
vector<vector<int>> dp;

void print_vector(vector<int> &v) {
    cout << "[";
    for (auto x : v) {
        cout << " " << x;
    }
    cout << " ]\n";
}

void print_matrix(vector<vector<int>> &m) {
    for (auto x: m) {
        print_vector(x);
    }
}

void receive_seq(vector<int> &seq, int sz) {
    seq.push_back(-INF);
    for (int i = 1; i <= sz; i++) {
        int num;
        cin >> num;
        seq.push_back(num);
    }
}

// longest common subsequence, recursivo com memoization
// i: índice na sequência da alice
// j: índice na sequência do bob
int lcs_rec(int i, int j) {
    // caso base
    // se uma ou ambas as sequências estiverem vazias.
    // não pode ser zero porque podemos ter respostas negativas.
    if (i == 0 || j == 0) {
        return -INF;
    }
    // memoization
    // verificar na tabela dp se a resposta já foi calculada
    if (dp[i][j] != -INF) {
        return dp[i][j];
    }
    // 3 hipóteses:
    // 1) usar os números dos índices indicados: o nosso valor total vai incrementar da multiplicação
    // (ou vai ser melhor que um valor muito negativo), continuar a procurar em i-1, j-1
    // 2) descartar o número 'j' do bob, continuar a procurar em i, j-1
    // 3) descartar o número 'i' da alice, continuar a procurar em i-1, j
    int use_both = max(alice_seq[i] * bob_seq[j] + lcs_rec(i-1, j-1), alice_seq[i] * bob_seq[j]);
    int use_alice = lcs_rec(i, j-1);
    int use_bob = lcs_rec(i-1, j);
    // retornar e guardar o valor em dp ao mesmo tempo
    return dp[i][j] = max(use_both, max(use_alice, use_bob));
}

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    int n;
    cin >> n;
    receive_seq(alice_seq, n);

    int m;
    cin >> m;
    receive_seq(bob_seq, m);
    // tabela de memoization, usar 'inf' por causa dos valores negativos
    dp.assign(n+1, vector<int> (m+1, -INF));

    // cout << "checking vectors:\n";
    // print_vector(alice_seq);
    // print_vector(bob_seq);
    // cout << "dp:\n";
    // print_matrix(dp);

    cout << lcs_rec(n, m) << "\n";

    return 0;
}
