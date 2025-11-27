#include <bits/stdc++.h>
using namespace std;

// grafo dirigido para guardar precedências
struct Graph {
    map<char,set<char>> edges;
    map<char,bool> visited;
};

// aproveitar e ir inicializando o map de visitados
void update(Graph &g, char a, char b) {
    g.edges[a].insert(b);
    g.visited[a] = false;
    g.visited[b] = false;
}

void print(Graph &g) {
    for (auto e : g.edges) {
        cout << e.first << " -> ";
        for (auto v : e.second) {
            cout << v << " ";
        }
        cout << "\n";
    }
}

void dfs(Graph &g, char v, deque<char> &order) {
    g.visited[v] = true;
    for (auto w : g.edges[v]) {
        if (!g.visited[w]) {
            dfs(g, w, order);
        }
    }
    order.push_front(v);
}
// ordem topológica em dfs (slide 39)
deque<char> topological_dfs(Graph &g) {
    deque<char> order;

    for (auto v : g.visited) {
        if (!g.visited[v.first]) {
            dfs(g, v.first, order);
        }
    }

    return order;
}


int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    int n;
    cin >> n;
    // vamos usar um grafo
    Graph g;

    string prev;
    cin >> prev;
    // comparar as palavras à medida que são recebidas
    for (int i = 0; i < n-1; i++) {
        string curr;
        cin >> curr;
        // encontrar a primeira letra diferente
        for (int k = 0; k < min((int)prev.length(), (int)curr.length()); k++) {
            if (prev[k] != curr[k]) {
                // adicionar ao grafo a informação de precedência
                update(g, prev[k], curr[k]);
                break;
            }
        }
        prev = curr;
    }
    // print(g);
    // a ordem que queremos é a ordem topológica do grafo
    deque<char> order = topological_dfs(g);
    for (auto x : order) {
        cout << x;
    }
    cout << "\n";

    return 0;
}
