//
// Fazer um único BFS no mapa todo. Começar com a fila do BFS já preenchida com as núvens,
// marcadas com valor 0.
// De cada vez que encontramos um vizinho não visitado, marcámo-lo com o valor do vértice que
// o visitou incrementado de 1.
// Por exemplo:
// ......      ..11..      .2112.      321123       321123
// ..00..  ->  .1001.  ->  210012  ->  210012  ->   210012
// ...0..      ..101.      .2101.      321012       321012
// ......      ...1..      ..212.      .32123       432123
//
// No fim, visitar os aeroportos (as coordenadas dos aeroportos foram guardadas previamente) e
// calcular o valor mínimo e máximo.


#include <bits/stdc++.h>
using namespace std;

// representar o grafo como uma matriz
vector<vector<int>> grid;
// fila para o BFS
queue<pair<int,int>> q;
// critério para definir vizinhos de uma célula
list<pair<int,int>> neighbours = {
    {-1, 0 },   // up
    { 1, 0 },   // down
    { 0, -1},   // left
    { 0, 1 }    // right
};
// para debug
void print_grid() {
    for (auto x : grid) {
        for (auto y : x) {
            if (y < 0) {
                cout << " " << y;
            }
            else {
                cout << "  " << y;
            }
        }
        cout << "\n";
    }
}

void bfs() {
    // a queue já foi construída no main
    // enquanto houver nós
    while (!q.empty()) {
        // remover o primeiro elemento da queue
        pair<int,int> v = q.front();
        q.pop();
        int i = v.first;
        int j = v.second;
        // para todos os vizinhos desse nó
        for (auto n : neighbours) {
            int i_inc = n.first;
            int j_inc = n.second;
            // se não tiver sido visitado
            if (grid[i+i_inc][j+j_inc] == -1) {
                q.push({i+i_inc, j+j_inc});     // colocar na queue
                grid[i+i_inc][j+j_inc] = grid[i][j] + 1;    // marcar como visitado
                // aqui o "visitado" também serve para guardar o número de dias
                // desde a núvem mais próxima
            }
        }

    }
}

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    int r, c;
    cin >> r >> c;
    // criar mapa com fronteira, preencher com '-2'
    grid.assign(r+2, vector<int>(c+2, -2));
    // criar uma lista para guardar as posições dos aeroportos
    vector<pair<int,int>> airport_locations;

    for (int i = 1; i <= r; i++) {
        // receber mapa linha a linha
        string line;
        cin >> line;

        for (int j = 1; j <= c; j++) {
            // processar os caracteres de cada linha:
            char c = line[j-1];
            switch (c) {
                case '#':
                    // uma nuvem é marcada por 0, para poder incrementar como o "número de dias".
                    // guardar na queue de BFS
                    grid[i][j] = 0;
                    q.push({i,j});
                    break;
                case 'A':
                    // o aeroporto é tratado como uma célula normal ('-1'),
                    // mas guardamos a localização para calcular o output mais tarde
                    grid[i][j] = -1;
                    airport_locations.push_back({i,j});
                    break;
                case '.':
                    grid[i][j] = -1;
                    break;
            }
        }
    }
    // print_grid();
    // fazer um bfs a partir da fila que já tem todas as núvens
    bfs();

    int n_max = 0;              // uma núvem não pode começar em cima de um aeroporto
    int n_min = 250 + 250 + 4;  // distância de manhathan do pior dos casos: cantos opostos

    // verificar os aeroportos, calcular valor mínimo e máximo
    for (auto a : airport_locations) {
        int n = grid[a.first][a.second];
        if (n < n_min) {
            n_min = n;
        }
        if (n > n_max) {
            n_max = n;
        }
    }
    cout << n_min << " " << n_max << "\n";

    return 0;
}
