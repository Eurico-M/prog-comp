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
        for (int i=0; i<n; i++) cap[i].resize(n);
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

    for (int i = 0; i < restr; i++) {
        int a, b;
        cin >> a >> b;
        // grafo bipartido com capacidades unitárias
        g.addLink(a, b + t_shirts, 1);
    }
    // adicionar arestas dos nós guardas (0 e t_shirts + dias + 2)
    for (int i = 1; i <= t_shirts; i++) {
        g.addLink(0, i, 1);
    }
    for (int i = 1; i <= dias; i++) {
        g.addLink(t_shirts + i , t_shirts + dias + 2, 1);
    }

    // resolver fluxo máximo no grafo bipartido
    int flow = g.maxFlow(0, t_shirts + dias + 2);
    cout << "Fluxo maximo: " << flow << "\n";

    return 0;
}