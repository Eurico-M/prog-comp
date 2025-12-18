// Estrutura do Grafo do Professor Pedro Ribeiro das aulas de DAA.
//
// Usar Dijkstra na VCI. Cada nó guarda a melhor velocidade para k+1 hipóteses de renovações.
// No exemplo do enunciado para 2 renovações, o nó 6 guardaria [22, 28, 40], as melhores velocidades
// nesse nó com 0, 1, e 2 renovações.
// Para calcular estes valores (relax_states), se estivermos a visitar um nó v e calcularmos
// o valor de um seu vizinho w, então cada hipótese de renovação em w vai ser o máximo de:
// 1) ou manter as renovações como estavam e usar a nova estrada v-w sem renovação,
// 2) ou gastar uma renovação a menos até v, e aplicar essa renovação na estrada v-w (multiplicar aresta por 2).
// (a excepção é no caso de 0 renovações, não podemos gastar menos de 0)
// 
// Como estamos à procura da velocidade máxima, iniciamos os nós com valor zero, excepto o nó
// inicial, que tem velocidade infinita.

#include <bits/stdc++.h>
#include <climits>

using namespace std;

// Classe que representa um no
class Node {
public:
    list<pair<int, int>> adj;  // Lista de adjacencias
    bool visited;              // No ja foi visitado?
    vector<int> speed;              // velocidade máxima nesse nó, para diferentes renovações
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
        nodes[b].adj.push_back({a,c});
    }

    vector<int> relax_states(vector<int> speed, int s) {
        vector<int> new_state;
        int k = speed.size();

        for (int i = 0; i < k; i++) {
            if (i == 0) {
                new_state.push_back(min(speed[i], s));
            }
            else {
                new_state.push_back(max(min(speed[i], s), min(speed[i-1], s * 2)));
            }
        }

        return new_state;
    }

    // Algoritmo de Dijkstra
    void dijkstra(int s, int k) {
        
        //Inicializar nos como nao visitados e com distancia zero
        for (int i=0; i<n; i++) {
            nodes[i].visited  = false;
            for (int j = 0; j <= k; j++) {
                nodes[i].speed.push_back(0);
            }
        }
        
        // Inicializar "fila" com nó origem.
        for (int j = 0; j <= k; j++) {
                nodes[s].speed[j] = (INT_MAX/2);
            }
        set<pair<int, int>, greater<pair<int,int>>> q; // Fazer sort decrescente 
        q.insert({INT_MAX, s});

        // Ciclo principal do Dijkstra
        while (!q.empty()) {
        
            // Retirar no com maior speed
            int u = q.begin()->second;
            // cout << "visitar " << u << "\n";
            q.erase(q.begin());
            nodes[u].visited = true;
            // cout << u << " [dist=" << nodes[u].speed << "]" << endl;

            // Relaxar arestas do no retirado
            for (auto edge : nodes[u].adj) {
                int v = edge.first;
                // cout << "    nó " << v << "\n";
                int road_speed = edge.second;
                vector<int> v_speed = nodes[v].speed;
                // for (auto w2 : v_speed) {
                //         cout << " " << w2;
                //     }
                // cout << "\n";
                // cout << u << " - " << v << " : " << road_speed << "\n";
                
                if (!nodes[v].visited) {
                    vector<int> v_temp = relax_states(nodes[u].speed, road_speed);
                    // for (auto w3 : v_temp) {
                    //     cout << " " << w3;
                    // }
                    // cout << "\n";
                    for (int l = 0; l <= k; l++) {
                        if (v_temp[l] > v_speed[l]) {
                            v_speed[l] = v_temp[l];
                        }
                    }
                    nodes[v].speed = v_speed;
                    // for (auto w : nodes[v].speed) {
                    //     cout << " " << w;
                    // }
                    // cout << "\n";
                    q.insert({v_temp[k], v});
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


    g.dijkstra(0, k);
    cout << g.nodes[n-1].speed[k]<< "\n";

    return 0;
}