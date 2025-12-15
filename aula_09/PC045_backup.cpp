// Exemplo de aplicacao do algoritmo de Dijkstra
// (assumindo um grafo pesado e dirigido, sem pesos negativos)

#include <bits/stdc++.h>

using namespace std;

// Classe que representa um no
class Node {
public:
    list<pair<int, int>> adj;  // Lista de adjacencias
    bool visited;              // No ja foi visitado?
    int speed;              // velocidade máxima nesse nó
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
        
        //Inicializar nos como nao visitados e com distancia zero
        for (int i=0; i<n; i++) {
            nodes[i].speed = 0;
            nodes[i].visited  = false;
        }
        
        // Inicializar "fila" com nó origem.
        nodes[s].speed = INT_MAX;
        set<pair<int, int>, greater<pair<int,int>>> q; // Fazer sort decrescente 
        q.insert({INT_MAX, s});      

        // Ciclo principal do Dijkstra
        while (!q.empty()) {
        
            // Retirar no com maior speed
            int u = q.begin()->second;
            q.erase(q.begin());
            nodes[u].visited = true;
            // cout << u << " [dist=" << nodes[u].speed << "]" << endl;

            // Relaxar arestas do no retirado
            for (auto edge : nodes[u].adj) {
                int v = edge.first;
                int road_speed = edge.second;
                if (!nodes[v].visited && min(nodes[u].speed, road_speed) > nodes[v].speed) {
                    q.erase({nodes[v].speed, v});  // Apagar do set
                    nodes[v].speed = min(nodes[u].speed, road_speed);
                    q.insert({nodes[v].speed, v}); // Inserir com novo max speed
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

    int k;
    cin >> k;


    g.dijkstra(0);
    cout << "max speed = " << g.nodes[n-1].speed << "\n";

    return 0;
}