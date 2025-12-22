// Usei a implementação de Edmonds-Karp do Professor Pedro Ribeiro de DAA.
//
// Só modifiquei a inserção de dados no grafo, para transformar os inputs desta maneira:
// O número de nós do grafo é 2n+2. 2n porque é um grafo bipartido. 
// Por exemplo, para o caso de teste:
// 5
// 5
// 0 1
// 1 2
// 2 3
// 3 4
// 4 2
//
// 5 nós e 5 arestas tranformam-se em 10 nós e 5 arestas:
//
//            1     6
//            2     7  
//            3     8
//            4     9  
//            5     10
//
// com arestas 1-7, 2-8, 3-9, 4-10, 5-8
// 
// Para transformar este grafo num problema de fluxo máximo (com capacidades unitárias)
// temos de adicionar dois nós guarda:
//
//            1     6
//            2     7 
//      0     3     8     11
//            4     9
//            5     10
//
// e arestas do nó 0 para os nós 1..5 e dos nós 6..10 para o nó 11.
//
// Depois é só resolver um problema de fluxo máximo, onde as capacidades das arestas são 1,
// e se o fluxo final for igual a 'n' então conseguimos distribuir todos os livros por todas
// as pessoas.


// Exemplo de implementacao de algoritmo de Edmonds-Karp para grafos pesados e dirigidos
// usando lista de adjacencias + matriz de capacidades (implementacao com vector)

#include <iostream>
#include <climits>
#include <vector>
#include <queue>

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
    int tests;
    cin >> tests;

    for (int t = 0; t < tests; t++) {
        
        int n, e, a, b;
        cin >> n;
        // grafo bipartido com nós guarda
        Graph g(2*n+2);
        cin >> e;
        for (int i=0; i<e; i++) {
            cin >> a >> b;
            // grafo bipartido com capacidades unitárias
            g.addLink(a+1, b+1+n, 1);
        }
        // adicionar arestas dos nós guardas (0 e 2n+1)
        for (int i = 1; i <= n; i++) {
            g.addLink(0, i, 1);
            g.addLink(i+n, 2*n+1, 1);
        }

        // resolver fluxo máximo no grafo bipartido
        int flow = g.maxFlow(0, 2*n+1);
        // cout << "Fluxo maximo: " << flow << endl;
        // se o fluxo for igual a 'n', conseguimos distribuir todos os livros
        if (flow != n) {
            cout << "NO\n";
        }
        else {
            cout << "YES\n";
        }
    }
    

    return 0;
}