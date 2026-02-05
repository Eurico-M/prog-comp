// A resolução deste problema é parecida com a resolução do exercício PC047.
// Ou seja, grafo bipartido.
//
// A construção do grafo, para além dos nós guarda s e t que é preciso adicionar,
// também envolve adicionar arestas em todos os nós de t-shirts que não estão
// restringidas.
//
// A solução envolve, nesta implementação em particular do grafo, usar a matriz
// de capacidades para determinar as arestas usadas pelo fluxo.
// Assim, é possível dizer que t-shirts usar em cada dia.
// Se o fluxo for inferior ao número de dias, então não é possível usar uma
// t-shirt diferente todos os dias.
//
// Edmonds-Karp corre em O(VE^2).
// Adicionar nós guarda e nós de t-shirts não restringidas: O(TD) (T-shirts e Dias)
// Percorrer a matriz capacidades para devolver lista de output: O(TD)
// Como V = T + D, a complexidade é ditada pelo algoritmo de Edmonds-Karp: O(VE^2)

#include <bits/stdc++.h>

using namespace std;

// Classe que representa um grafo
class Graph {
public:
    int n;                    // Numero de nos do grafo
    vector<vector <int>> adj; // Lista de adjacencias
    vector<vector <int>> cap; // Matriz de capacidades

    Graph(int n) {
        this->n = n;
        adj.resize(n); // +1 se os nos comecam em 1 ao inves de 0
        cap.resize(n);
        for (int i=0; i<n; i++) {
            cap[i].resize(n);
        }
    }
    
    void addLink(int a, int b, int c) {
        // adjacencias do grafo nao dirigido, porque podemos ter de andar no sentido
        // contrario ao procurarmos caminhos de aumento
        adj[a].push_back(b);
        adj[b].push_back(a);
        cap[a][b] = c;
    }

    // BFS para encontrar caminho de aumento
    // devolve valor do fluxo nesse caminho
    int bfs(int s, int t, vector<int> &parent) {
        for (int i=0; i<n; i++) parent[i] = -1;

        parent[s] = -2;         
        queue<pair<int, int>> q; // fila do BFS com pares (no, capacidade)
        q.push({s, INT_MAX});    // inicializar com no origem e capacidade infinita

        while (!q.empty()) {
            // returar primeiro no da fila
            int cur = q.front().first;
            int flow = q.front().second;
            q.pop();

            // percorrer nos adjacentes ao no atual (cur)
            for (int next : adj[cur]) {
                // se o vizinho ainda nao foi visitado (parent==-1)
                // e a aresta respetiva ainda tem capacidade para passar fluxo
                if (parent[next] == -1 && cap[cur][next]>0) {
                parent[next] = cur;                        // atualizar pai
                int new_flow = min(flow, cap[cur][next]);  // atualizar fluxo
                if (next == t) return new_flow;            // chegamos ao final?
                q.push({next, new_flow});                  // adicionar a fila
                }
            }
        }

        return 0;
    }
    
    // Algoritmo de Edmonds-Karp para fluxo maximo entre s e t
    // devolve valor do fluxo maximo (cap[][] fica com grafo residual)
    int maxFlow(int s, int t) {
        int flow = 0;             // fluxo a calcular
        vector<int> parent(n+1);  // vetor de pais (permite reconstruir caminho)
        
        while (true) {
            int new_flow = bfs(s, t, parent); // fluxo de um caminho de aumento
            if (new_flow == 0) break;         // se nao existir, terminar

            // imprimir fluxo e caminho de aumento
            // cout << "Caminho de aumento: fluxo " << new_flow << " | " << t;
            
            flow += new_flow;  // aumentar fluxo total com fluxo deste caminho
            int cur = t;
            while (cur != s) { // percorrer caminho de aumento e alterar arestas
                int prev = parent[cur];	
                cap[prev][cur] -= new_flow;
                cap[cur][prev] += new_flow;
                cur = prev;
                // cout << " <- " << cur; // imprimir proximo no do caminho
            }
            // cout << endl;
        }
        
        return flow;
    }
};

int main() {
       
    int t_shirts, dias, restr;
    cin >> t_shirts >> dias >> restr;

    // grafo bipartido com nós guarda
    Graph g(t_shirts + dias + 2);

    vector<bool>t_shirts_restringidas(t_shirts + 1, false);
    // cout << "restrições:\n";
    for (int i = 0; i < restr; i++) {
        int a, b;
        cin >> a >> b;
        // grafo bipartido com capacidades unitárias
        g.addLink(a, b + t_shirts, 1);
        // cout << "addLink(" << a << ", " << b+t_shirts << ")\n";
        t_shirts_restringidas[a] = true;
    }
    // cout << "nós guarda:\n";
    // adicionar arestas dos nós guardas (0 e t_shirts + dias + 1)
    for (int i = 1; i <= t_shirts; i++) {
        g.addLink(0, i, 1);
        // cout << "addLink(" << 0 << ", " << i << ")\n";
        // adicionar arestas das t-shirts não restringidas
        if (!t_shirts_restringidas[i]) {
            // cout << i << " é não restringida:\n";
            for (int j = 1; j <= dias; j++) {
                g.addLink(i, t_shirts + j, 1);
                // cout << "   addLink(" << i << ", " << t_shirts+j << ")\n";
            }
        }
    }
    for (int i = 1; i <= dias; i++) {
        g.addLink(t_shirts + i , t_shirts + dias + 1, 1);
        // cout << "addLink(" << t_shirts + i << ", " << t_shirts + dias + 1 << ")\n";
    }

    // cout << "grafo:\n";
    // for (int i = 0; i < t_shirts + dias + 2; i++) {
    //     cout << i;
    //     for (int j : g.adj[i]) {
    //         cout << " <- " << j;
    //     }
    //     cout << "\n";
    // }

    // resolver fluxo máximo no grafo bipartido
    int flow = g.maxFlow(0, t_shirts + dias + 1);
    // cout << "Fluxo maximo: " << flow << "\n";

    // cout << "cap[][]:\n";
    // for (auto x : g.cap) {
    //     for (auto y : x) {
    //         cout << " " << y;
    //     }
    //     cout << "\n";
    // }

    if (flow < dias) {
        cout << 0 << "\n";
    }
    else {
        for (int i = 1; i <= dias; i++) {
            int no = t_shirts + i;
            for (int j = 1; j <= t_shirts; j++) {
                if (g.cap[no][j] == 1) {
                    // cout << "dia " << no << " -> t-shirt ";
                    cout << j << "\n";
                    break;
                }
            }
        }
    }

    return 0;
}