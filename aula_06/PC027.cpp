
// Solução recursiva com memoization.
//
// No geral, um conjunto de misturas [1..n] pode ser dividido em duas partes, [1..k] [k+1..n].
// Podemos fazer isto n-1 vezes.
// Por exemplo, o conjunto de misturas [40 60 20 30] pode ser dividido em:
// [40] [60 20 30]
// [40 60] [20 30]
// [40 60 20] [30]
//
// A motivação para resolver assim é que sabemos o resultado e o custo de misturar duas misturas.
// Por isso, a solução de um conjunto [1..n] é, de entre os conjuntos [1..k] [k+1..n],
// o que apresentar menor custo.
//
// O custo de uma divisão é: a multiplicação dos resultados numéricos anteriores de cada parcela
// somado com os custos anteriores de cada parcela.
//
// Assim, o resultado de uma mistura apresenta dois números: o resultado numérico, e o custo.
//
// O caso base é a mistura única: o resultado é o seu próprio valor, e o custo é nulo.

#include <bits/stdc++.h>
#include <climits>
using namespace std;

// resultado de uma mistura: resultado numérico e custo (são diferentes)
struct Mix {
    int result;
    int cost;
};

// declaração de vector de misturas e matriz de programação dinâmica
vector<int> m;
vector<vector<Mix>> dp;

// vários prints para debug
void print_mix(Mix &m) {
    cout << "(" << m.result << "," << m.cost << ")\n";
}

void print_vector(vector<int> &v) {
    cout << "[";
    for (auto x : v) {
        cout << " " << x;
    }
    cout << " ]\n";
}

void print_mix_vector(vector<Mix> &v) {
    cout << "[";
    for (auto x : v) {
        cout << " (" << x.result << "," << x.cost << ")";
    }
    cout << " ]\n";
}

void print_matrix(vector<vector<Mix>> &m) {
    for (auto x: m) {
        print_mix_vector(x);
    }
}

// limpar o vector anterior e receber novo vector de misturas
void receive_mixtures(int n) {
    m.clear();
    m.push_back(-1);
    for (int i = 1; i <= n; i++) {
        int mix_in;
        cin >> mix_in;
        m.push_back(mix_in);
    }
}

// limpar a matriz dp anterior e inicializar nova matriz com -1
void configure_dp(int n) {
    dp.clear();
    Mix null_mix;
    null_mix.result = -1;
    null_mix.cost = -1;
    dp.assign(n + 1, vector<Mix> (n + 1, null_mix));
}

// função recursiva com memoization
Mix min_smoke(int i, int j) {
    // caso base, mistura única
    if (i == j) {
        Mix mix;
        mix.result = m[i];
        mix.cost = 0;
        return mix;
    }
    // memoization
    if (dp[i][j].cost != -1) {
        return dp[i][j];
    }
    // calcular a mistura mínima: aquela que tiver o custo menor de entre as divisões possíveis
    Mix min_mix;
    min_mix.result = -1;
    min_mix.cost = INT_MAX;
    // gerar as n-1 divisões 'binárias' de um conjunto [1..n]:
    // [1..k][k+1..n] para i <= k < j
    //  left   right
    for (int k = i; k < j; k++) {
        // calcular recursivamente left e right e guardar resultados em dp
        Mix left = min_smoke(i, k);
        dp[i][k] = left;
        Mix right = min_smoke(k + 1, j);
        dp[k + 1][j] = right;
        // o custo é a multiplicação dos resultados somado com os custos anteriores
        int cost = (left.result * right.result) + (left.cost + right.cost);
        // se o custo for o menor, encontramos a mistura mínima
        if (cost < min_mix.cost) {
            min_mix.result = (left.result + right.result) % 100;
            min_mix.cost = cost;
        }
    }
    return min_mix;
}

// funçãozinha para esconder os argumentos 'feios' da recursão, só para experimentar
int minimum_smoke() {
    Mix res = min_smoke(1, (int) m.size() - 1);
    return res.cost;
}

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //
    // receber o número de testes
    int n_tests;
    cin >> n_tests;

    for (int i = 0; i < n_tests; i++) {
        // para cada teste, receber o número de misturas
        int n_mixtures;
        cin >> n_mixtures;
        // preencher vector de misturas e matriz de programação dinâmica
        receive_mixtures(n_mixtures);
        configure_dp(n_mixtures);
        // calcular o mínimo de fumo
        cout << minimum_smoke() << "\n";
    }

    return 0;
}
