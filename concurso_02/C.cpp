// Exemplo de pesquisa em largura (BFS) num grafo nao dirigido
// (codigo adaptado do codigo em Java feito na teorica)
// (inclui calculo de distancias)
// (esta versao limpa no final a memoria criada - a cada "new" deve corresponder um "delete")

#include <iostream>
#include <list>
#include <vector>

using namespace std;

vector<int> secret_ppl;
int k;
list<int> q;


// Classe que representa um no
class Node {
public:
    list<int> adj;  // Lista de adjacencias
    bool visited;   // Valor booleano que indica se foi visitado numa pesquisa
    int distance;   // Distancia ao no origem da pesquisa
    int k_visitas;

    Node() {        // Nao e preciso mais nada porque adj ja foi criada
    };              // mas queria mostrar que em C++ tambem existem construtores
};

// Classe que representa um grafo
class Graph {
public:
    int n;          // Numero de nos do grafo
    Node *nodes;    // Array para conter os nos

    Graph(int n) { // Constructor: chamado quando um objeto Graph for criado
        this->n = n;
        nodes = new Node[n+1];  // +1 se os comecam em 1 ao inves de 0
    }

    ~Graph() { // Destructor: chamado quando um objeto Graph for destruido
        delete[] nodes;
    }

    void addLink(int a, int b) {
        nodes[a].adj.push_back(b);
        nodes[b].adj.push_back(a);
    }
    
    void bfs(int k1) {        


        while (q.size() > 0) {
            int u = q.front(); q.pop_front();
            cout << "visitar " << u << "\n";
            // cout << u << " [dist=" << nodes[u].distance << "]" << endl;
            for (auto w : nodes[u].adj) {
                cout << "    vizinho " << w << "\n";
                if (!nodes[w].visited) {
                    q.push_back(w);
                    nodes[w].visited  = true;
                    nodes[w].distance = nodes[u].distance + 1;
                    nodes[w].k_visitas = nodes[u].k_visitas * 2;	  
                }
            }
        }
    }
};

int main() {
    int n, e, a, b;
    
    cin >> n;
    Graph g(n);
    cin >> e;

    int q1;
    cin >> q1;

    int k;
    cin >> k;

    for (int i = 0; i < q1; i++) {
        int sp;
        cin >> sp;
        secret_ppl.push_back(sp);
    }


    for (int i=0; i<e; i++) {
        cin >> a >> b;
        g.addLink(a, b);
    }

    // cout << "secret people: ";
    // for (auto x : secret_ppl) {
    //     cout << x << " ";
    // }
    // cout << "\n";

    for (int i=1; i<=n; i++) {
        g.nodes[i].visited = false;
    }

    for (auto x : secret_ppl) {
        g.nodes[x].visited = true;
        g.nodes[x].distance = 0;
        g.nodes[x].k_visitas = k;
        q.push_back(x);
    }
    // Pesquisa em largura a partir do no 1
    g.bfs(k);

    for (int i = 1; i < n; i++) {
        cout << g.nodes[i].distance << " ";
    }
    cout << g.nodes[n].distance << "\n";

    return 0;
}
