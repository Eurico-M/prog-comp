#include <bits/stdc++.h>
using namespace std;

// para debug
void print(vector<vector<char>> &world, int k) {
    cout << "World #" << k << "\n";
    for (auto x : world) {
        for (auto y : x) {
            cout << y;
        }
        cout << "\n";
    }
}

void print_visited(vector<vector<bool>> &v) {
    cout << "visited:\n";
    for (auto x : v) {
        for (auto y : x) {
            cout << y;
        }
        cout << "\n";
    }
}

void bfs(int a, int b, vector<vector<char>> &world, vector<vector<bool>> &visited) {
    queue<pair<int,int>> q;
    q.push({a,b});

    list<pair<int,int>> neighbours = {
        {-1 ,0}, // up
        {1, 0},  // down
        {0, -1}, // left
        {0, 1}   // right
    };

    while (!q.empty()) {
        // remover primeiro elemento da fila
        pair<int,int> p = q.front();
        int i = p.first;
        int j = p.second;
        q.pop();
        // percorrer vizinhos
        for (auto n : neighbours) {
            int x = n.first;
            int y = n.second;
            // se o caracter for igual e não tiver sido visitado,
            // marcar como visitado e colocar na fila
            if (world[i+x][j+y] == world[i][j] && !visited[i+x][j+y]) {
                visited[i+x][j+y] = true;
                q.push({i+x, j+y});
            }
        }
    }
}

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //
    // receber número de testes
    int n;
    cin >> n;
    // para cada teste
    for (int k = 1; k <= n; k++) {
        // receber dimensões
        int h, w;
        cin >> h >> w;
        // criar "mundo" como uma matriz de char com fronteiras
        vector<vector<char>> world (h+2, vector<char>(w+2, '.'));
        // processar input linha a linha
        for (int i = 1; i <= h; i++) {
            string line;
            cin >> line;
            for (int j = 1; j <= w; j++) {
                world[i][j] = line[j-1];
            }
        }
        // print(world, k);
        // criar matriz de visitados e dicionário para guardar conjuntos conexos
        vector<vector<bool>> visited (h+2, vector<bool>(w+2, false));
        map<char,int> states;
        // percorrer mundo e, se encontrarmos um novo país (não visitado), inserir no map
        // e marcar todas as células desse país como visitadas (usando BFS)
        for (int i = 1; i <= h; i++) {
            for (int j = 1; j <= w; j++) {
                if (!visited[i][j]) {
                    states[world[i][j]]++;
                    bfs(i, j, world, visited);
                    // cout << "world " << k << "\n";
                    // cout << "i=" << i << " j=" << j << "\n";
                    // print_visited(visited);
                }
            }
        }
        // inserir valores num multimap, com os números a servirem de chave.
        // assim, o output fica ordenado por ordem decrescente dos números (greater<int>),
        // e ordem crescente de letras (em caso de empate, o multimap mantém ordem de inserção)
        multimap<int,char,greater<int>> output;
        for (auto s : states) {
            output.insert({s.second, s.first});
        }
        // imprimir output
        cout << "World #" << k << "\n";
        for (auto o : output) {
            cout << o.second << ": " << o.first << "\n";
        }
    }

    return 0;
}
