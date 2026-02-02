// Estrutura do Grafo do Professor Pedro Ribeiro
//
// Bellman-Ford aplicado quase directamente, trocar só a inicialização dos nós para -inf
// porque é um problema de maximização.
//
// Na verificação de ciclos, só retornar -1 se o relaxamento existir (obviamente) mas também só se:
// 1) o nó relaxado consegue chegar ao nó final E
// 2) o nó inicial consegue chegar ao nó relaxado
// estas condições são verificadas com um DFS reaches_n(v, z) que verifica se um nó v consegue
// chegar ao nó z.

#include <bits/stdc++.h>

using namespace std;

#define INF LONG_LONG_MAX
typedef long long ll;

// Classe que representa um no
class Node {
public:
    list<pair<int, int>> adj;  // Lista de adjacencias
    ll distance;              // Distancia ao no origem da pesquisa
    int parent;
    int visited;
};

// Classe que representa um grafo
class Graph {
public:
    int n;          // Numero de nos do grafo
    Node *nodes;    // Array para conter os nos

    Graph(int n) { // Constructor: chamado quando um objeto Graph for criado
        this->n = n;
        nodes = new Node[n+1];  // +1 se os nos comecam em 1 ao inves de 0
    }
    
    ~Graph() { // Destructor: chamado quando um objeto Graph for destruido
        delete[] nodes;
    }
    
    void addLink(int a, int b, int c) {
        nodes[a].adj.push_back({b,c});
    }

    bool dfs(int v, int z) {
        if (v == z) {
            return true;
        }
        nodes[v].visited = true;
        for (auto e : nodes[v].adj) {
            if (!nodes[e.first].visited && dfs(e.first, z)) {
                return true;
            }
        }
        return false;
    }

    bool reaches_n(int v, int z) {
        // cout << "testar se " << v << " chega a " << z << "\n";
        for (int i = 1; i <= n; i++) {
            nodes[i].visited = false;
        }
        bool reaches = dfs(v, z);
        // cout << reaches << "\n";
        return reaches;
    }

    // Bellman-Ford
    ll bellman_ford() {

        // inicializar nós a -inf, estamos à procura da pontuação máxima
        for (int i = 1; i <= n; i++) {
            nodes[i].distance = -INF;
        }
        // pontuação inicial
        nodes[1].distance = 0;
        nodes[1].parent = 0;

        // percorrer todas as arestas V-1 vezes
        for (int i = 1; i < n; i++) {
            // cout << "#### iteração " << i << "\n";
            for (int v = 1; v <= n; v++) {
                // cout << "    nó " << v << "\n";
                for (auto e : nodes[v].adj) {
                    int neighbour = e.first;
                    int score = e.second;
                    // cout << "      aresta " << v << "-" << neighbour << " : score = " << score << "\n";
                    if (nodes[v].distance + score > nodes[neighbour].distance) {
                        // cout << "        relaxar " << nodes[neighbour].distance << " para " << nodes[v].distance + score << "\n";
                        nodes[neighbour].distance = nodes[v].distance + score;
                        nodes[neighbour].parent = v;
                    }
                }
            }
        }

        // detetar ciclos - fazer uma última iteração de todas as arestas
        for (int v = 1; v <= n; v++) {
            for (auto e : nodes[v].adj) {
                int neighbour = e.first;
                int score = e.second;
                // cout << "aresta " << v << "-" << neighbour << "\n"; 
                // retornar -1 só se o nó estiver envolvido no caminho de maior pontuação
                if (reaches_n(neighbour, n) && reaches_n(1, v) && nodes[v].distance + score > nodes[neighbour].distance) {
                    return -1;
                }
            }
        }

        return nodes[n].distance;

    }
};

int main() {
    int n, e, a, b, c;
    
    cin >> n;
    Graph g(n);
    cin >> e;
    for (int i=0; i<e; i++) {
        cin >> a >> b >> c;
        g.addLink(a, b, c);
    }

    cout << g.bellman_ford() << "\n";

    return 0;
}