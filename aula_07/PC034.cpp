// Seguir a receita da hint do professor:
// 
// Distinguir a margem Norte da margem Sul através de um BFS (check_margins)
// Calcular, para cada coluna, o custo de construir uma ponte nesse lugar (calc_bridge_length)
// Fazer uma recursão com DP: num estado solve(j, b), j é o índice da coluna, b é o número de pontes que
// faltam construir.
// A matriz DP guarda o tamanho mínimo da configuração de pontes nesse instante.
// Para um estado qualquer, podemos tomar duas opções: 
// 1) Colocar uma ponte e prosseguir a partir do intervalo mínimo, 
// com menos uma ponte por construir (j+s, b-1). Acrescentar o custo da ponte.
// 2) Ou não construir a ponte, e prosseguir para a coluna seguinte (j+1, b).
// Os critérios de paragem são:
// ou já não temos pontes para construir (b = 0), neste caso devolver 0 porque queremos esta solução.
// ou ainda temos pontes por construir mas já chegámos ao fim do mapa (j >= cols), neste caso
// devolver INF porque não queremos esta solução.

#include <bits/stdc++.h>
using namespace std;

#define INF INT_MAX/2

int rows, cols;
int bgs, sps;
vector<vector<char>> mapa;
vector<int> bridge_length;
vector<vector<int>> dp;

list<pair<int,int>> nbrs = {
    {-1, 0},    // up
    {1, 0},     // down
    {0, -1},    // left
    {0, 1}      // right
};

void print_mapa() {
    for (auto x : mapa) {
        for (auto y : x) {
            cout << y;
        }
        cout << "\n";
    }
    cout << "\n";
}

void print_bridge_length () {
    for (auto x : bridge_length) {
        cout << " " << x;
    }
    cout << "\n";
}

void check_margins(char c, int a, int b) {
    queue<pair<int,int>> q;
    q.push({a, b});

    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        int x = v.first;
        int y = v.second;

        mapa[x][y] = c;

        for (auto w : nbrs) {
            int i = w.first;
            int j = w.second;

            if (mapa[x+i][y+j] == '#') {
                q.push({x+i, y+j});
            }
        }
    }
}

void calc_bridge_length() {
    for (int j = 1; j <= cols; j++) {
        int n = 1;
        int s = rows;

        for (int i = 1; i <= rows; i++) {
            if (mapa[i][j] == 'N') {
                n = i;
            }
        }
        for (int i = rows; i >= 1; i--) {
            if (mapa[i][j] == 'S') {
                s = i;
            }
        }

        bridge_length.push_back(s - n - 1);
    }
}

int solve(int j, int b) {

    // cout << "j=" << j << " b=" << b << "\n";
    if (b == 0) {
        return dp[j][b] = 0;
        //return 0;
    }

    if (j >= cols) {
        return dp[j][b] = INF;
        // return INF;
    }

    if (dp[j][b] != -1) {
        return dp[j][b];
    }

    return dp[j][b] = min((solve(j+1+sps, b-1) + bridge_length[j]), solve(j+1, b));
    // return min((solve(j+1+sps, b-1) + bridge_length[j]), solve(j+1, b));
}



int main() {
    // Fast IO
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    //

    cin >> rows >> cols;
    mapa.assign(rows + 2, vector<char> (cols + 2, 'x'));
    //print_mapa();
    cin >> bgs >> sps;
    dp.assign(cols + sps + 2, vector<int> (bgs + 1, -1));
    
    for (int i = 1; i <= rows; i++) {
        string line;
        cin >> line;
        for (int j = 1; j <= cols; j++) {
            mapa[i][j] = line[j-1];
        }
    }

    // print_mapa();

    // bfs na margem norte
    check_margins('N', 1, 1);
    // bfs na margem sul
    check_margins('S', rows, 1);

    //print_mapa();

    calc_bridge_length();

    //print_bridge_length();

    cout << solve(0, bgs) << "\n";

    return 0;
}
