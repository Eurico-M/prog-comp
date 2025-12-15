// Exemplo de aplicacao do algoritmo de Dijkstra
// (assumindo um grafo pesado e dirigido, sem pesos negativos)

#include <bits/stdc++.h>

using namespace std;

// Classe que representa um no
class Node {
public:
    list<pair<int, int>> adj;  // Lista de adjacencias
    bool visited;              // No ja foi visitado?
    int distance;              // Distancia ao no origem da pesquisa
};

// Classe que representa um grafo
class Graph {
public:
    int n;          // Numero de nos do grafo
    Node *nodes;    // Array para conter os nos

    Graph(int n) { // Constructor: chamado quando um objeto Graph for criado
        this->n = n;
        nodes = new Node[n];  // +1 se os nos comecam em 1 ao inves de 0
    }
    
    ~Graph() { // Destructor: chamado quando um objeto Graph for destruido
        delete[] nodes;
    }
    
    void addLink(int a, int b, int c) {
        nodes[a].adj.push_back({b,c});
    }

    // Algoritmo de Dijkstra
    void dijkstra(int s) {
        
        //Inicializar nos como nao visitados e com distancia infinita
        for (int i=0; i<n; i++) {
            nodes[i].distance = INT_MAX;
            nodes[i].visited  = false;
        }
        
        // Inicializar "fila" com no origem
        nodes[s].distance = 0;
        set<pair<int, int>> q; // By "default" um par e comparado pelo primeiro elemento 
        q.insert({0, s});      // Criar um par (dist=0, no=s)

        // Ciclo principal do Dijkstra
        while (!q.empty()) {
        
            // Retirar no com menor distancia (o "primeiro" do set, que e uma BST)
            int u = q.begin()->second;
            q.erase(q.begin());
            nodes[u].visited = true;
            cout << u << " [dist=" << nodes[u].distance << "]" << endl;

            // Relaxar arestas do no retirado
            for (auto edge : nodes[u].adj) {
                int v = edge.first;
                int cost = edge.second;
                if (!nodes[v].visited && nodes[u].distance + cost < nodes[v].distance) {
                    q.erase({nodes[v].distance, v});  // Apagar do set
                    nodes[v].distance = nodes[u].distance + cost;
                    q.insert({nodes[v].distance, v}); // Inserir com nova (e menor) distancia
                }
            }
        }
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


    // Execucao exemplo a partir do no 1
    g.dijkstra(1);

    return 0;
}