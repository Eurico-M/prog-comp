#set page(
    paper: "a4",
    flipped: true,
    columns: 2,
    margin: 1.5cm,
    numbering: "1/1"
)

#set text(
    size: 8pt
)

// Acrescentar números de linha nos blocos de código
#import "@preview/zebraw:0.6.1": *
#show: zebraw

== Counting Sort
```
count[max size] ← frequencies array
For i = 0 to n − 1 do
    count[v [i]] + + (one more v[i] element)
i = 0
For j = min size to max size do
    While count[j] > 0 do
        v [i] = j (put element on array)
        count[j]−− (one less element of that size)
        i++ (increments first free position on the array)
```
== A possible RadixSort (starting on the least significant digit)
```
bucket[10] ← array of lists of numbers (one per digit)
For pos = 1 to max number digits do
    For i = 0 to n − 1 do (for each number)
        Put v [i]in bucket[digit position pos(v [i])]
    For i = 0 to 9 do (for each possible digit)
        While size(bucket[i]) > 0 do
            Take first number of bucket[i] and add it to v []
```
== Binary search on a sorted array
```
bsearch(v, low, high, key)
    While (low ≤ high ) do
        middle = low + (high − low )/2
        If (key == v [middle]) return(middle)
        Else If (key < v [middle]) high = middle − 1
        Else low = middle + 1
    return(-1)
```
== Binary search for smallest k such that condition(k) is ”yes”
```
bsearch(low, high, condition)
While (low < high ) do
    middle = low + (high − low )/2
    If (condition(middle) == yes)) high = middle
    Else low = middle + 1
If (condition(low ) == no) return(-1)
return(low)
```
== Ternary search
```
// a: left edge of interval
// b: right edge of interval
// f: function
// epsilon: tolerance
input a, b, f, epsilon
l ← a
r ← b
while (r-l > epsilon)
    m1 ← (2*l + r)/3
    m2 ← (l + 2*r)/3
    if f(m1) < f(m2)
        l ← m1
    else
        r ← m2
print r
```
== Segment tree
```cpp
// Pedro Ribeiro (DCC/FCUP)
#include <bits/stdc++.h>
using namespace std;

// An example simple segment tree implementation with arrays
const int MAX = 200005;   // Capacity of Segment Tree
const int MAX_ST = MAX*4;

const int NEUTRAL = 0;    // Neutral element

typedef int64_t st_value; // type of segment tree value

int n;               // Number of elements in the segtree
st_value v[MAX];     // Array of values
st_value st[MAX_ST]; // Segtree (in this case storing interval sums)

// Merge contents of nodes a and b
st_value merge(st_value a, st_value b) {
    return a+b;
}

// Build initial segtree (in position pos, interval [start,end])
void build(int pos, int start, int end) {
    if (start == end) {
        st[pos] = v[start];
    } else {      
        int middle = start + (end-start)/2;
        build(pos*2, start, middle);
        build(pos*2+1, middle+1, end);
        st[pos] = merge(st[pos*2], st[pos*2+1]);
    }  
}

// Update node n to value v
void update(int pos, int start, int end, int n, st_value v) {
    if (start > n || end < n) return;
    if (start == end) {
        st[pos] = v;
    } else {      
        int middle = start + (end-start)/2;
        update(pos*2, start, middle, n, v);
        update(pos*2+1, middle+1, end, n, v);
        st[pos] = merge(st[pos*2], st[pos*2+1]);
    }  
}

// Make a query of interval [a,b]
st_value query(int pos, int start, int end, int a, int b) {
    if (start>b || end<a) return NEUTRAL;
    if (start>=a && end<=b) return st[pos];
    
    int middle = start + (end-start)/2;
    st_value l = query(pos*2, start, middle, a, b);
    st_value r = query(pos*2+1, middle+1, end, a, b);
    return merge(l, r);
}

// ---------------------------------------------------------

int main() {
    int q;
    cin >> n >> q;
    for (int i=1; i<=n; i++)
        cin >> v[i];
        
    build(1, 1, n);

    for (int i=1; i<=q; i++) {
        int op, a, b;
        cin >> op >> a >> b;
        if (op == 1) update(1, 1, n, a, b);
        else cout << query(1, 1, n, a, b) << endl;
    }
    
    return 0;
}
```
== Binary Indexed Tree
```cpp
vector<int> tree;
int maxIdx;

int read(int idx) {
    int sum = 0;
    while (idx > 0) {
        sum += tree[idx];
        idx -= (idx & -idx);
    }
    return sum;
}

void update(int idx, int val) {
    while (idx <= MaxIdx) {
        tree[idx] += val;
        idx += (idx & -idx);
    }
}

int sum(int l, int r) { // Range Query
  return read(r) - read(l - 1);
}

int readSingle(int idx) { // Read the actual number, not cumulative 
    int sum = tree[idx]; // this sum will be decreased
    if (idx > 0) { // the special case
        int z = idx - (idx & -idx);
        idx--; // idx is not important anymore, so instead y, you can use idx
        while (idx != z) { // at some iteration idx (y) will become z
        sum -= tree[idx];
        // substruct tree frequency which is between y and "the same path"
        idx -= (idx & -idx);
        }
    }
    return sum;
}

void scale(int c) { // Scale entire tree by c
    for (int i = 1; i <= MaxIdx; i++)
        tree[i] = tree[i] / c;
}
```
== Kadane
```py
def max_subarray(numbers):
    """Find the largest sum of any contiguous subarray."""
    best_sum = float('-inf')
    current_sum = 0
    for x in numbers:
        current_sum = max(x, current_sum + x)
        best_sum = max(best_sum, current_sum)
    return best_sum
```
== DFS
```
dfs(node v):
    mark v as visited
    For all neighbors w of v do
        If w has not yet been visited then
        dfs(w)
```
== Finding Connected Components
```
counter ← 0
set all nodes as not visited
For all nodes v of the graph do
    If v has not yet been visited then
        counter++
        dfs(v)
write(counter)
```
== Topological Sorting
```
order ← empty
set all nodes as not visited
For all nodes v of the graph do
    If v has not yet been visited then
        dfs(v)
write(order)

dfs(node v):
    mark v as visited
    For all neighbors w of v do
        If w has not yet been visited then
            dfs(w)
    add v to the begginning of order
```
== Cycle Detection
```
color[v ∈ V] ← white
For all nodes v of the graph do
    If color[v] = white then
    dfs(v)

dfs(node v):
    color[v] ← gray
    For all neighbors w of v do
        If color[w] = gray then
            write(”Cycle found!”)
        Else if color[w] = white then
            dfs(w)
    color[v] ← black
```
== Tarjan Algorithm for Strongly Connected Components
Make a DFS and in each node i:
    Keep pushing the nodes to a stack S.
    Compute and store the values of num(i) and low(i).
    If when finishing the visit of a node i we have that num(i) = low(i),
    then i is the ”root” of a SCC. In that case, remove all the elements in
    the stack until reaching i and report those elements as belonging to a
    SCC!
```
index ← 0 ; S ← ∅
For all nodes v of the graph do
    If num[v] is still undefined then
        dfs_scc(v)

dfs scc(node v):
    num[v] ← low [v] ← index ; index ← index + 1 ; S.push(v)
    /* Traverse edges of v */
    For all neighbors w of v do
        If num[w] is still undefined then /* Tree Edge */
            dfs scc(w) ; low [v ] ← min(low [v], low [w])
        Else if w is in S then /* Back Edge */
            low [v] ← min(low [v], num[w])
    /* We know that we are at the root of an SCC */
    If num[v] = low [v] then
        Start new SCC C
        Repeat
            w ← S.pop() ; Add w to C
        Until w = v
        Write C
```
== Articulation Points
Apply DFS to the graph and obtain the DFS tree.
If a node v has a child w without any path to an ancestor of v,
then v is an articulation point! (since removing it would disconnect
w from the rest of the graph). The only exception is the root of the DFS tree. 
If it has more than one child in the tree it is also an articulation point!
```
dfs art(node v):
    num[v] ← low[v] ← index ; index ← index + 1 ; S.push(v)
    For all neighbors w of v do
        If num[w] is not yet defined then /* Tree Edge */
            dfs art(w) ; low [v] ← min(low [v], low [w])
            If low [w] ≥ num[v] then
                write(v + ”is an articulation point”)
        Else if w is in S then /* Back Edge */
        low [v] ← min(low [v], num[w])
    S.pop()
```
== BFS - Computing Distances
```
bfs(node v):
    q ← ∅ /* Queue of non visited nodes */
    q.enqueue(v)
    v .distance ← 0 /* distance from v to itself it’s zero */
    mark v as visited
    While q != ∅ /* while there are still unprocessed nodes */
        u ← q.dequeue() /* remove first element of q */
        For all neighbors w of u do
            If w has not yet been visited then /* new node */
                q.enqueue(w)
                mark w as visited
                w .distance ← u.distance + 1
```
== Edmonds-Karp (Fluxo máximo)
```cpp
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
        adj.resize(n+1); // +1 se os nos comecam em 1 ao inves de 0
        cap.resize(n+1);
        for (int i=1; i<=n; i++) cap[i].resize(n+1);
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
        for (int i=1; i<=n; i++) parent[i] = -1;

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
        cout << "Caminho de aumento: fluxo " << new_flow << " | " << t;
        
        flow += new_flow;  // aumentar fluxo total com fluxo deste caminho
        int cur = t;
        while (cur != s) { // percorrer caminho de aumento e alterar arestas
            int prev = parent[cur];	
            cap[prev][cur] -= new_flow;
            cap[cur][prev] += new_flow;
            cur = prev;
            cout << " <- " << cur; // imprimir proximo no do caminho
        }
        cout << endl;
        }
        
        return flow;
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

    // Execucao exemplo usando 1 como no origem a 4 como o destino
    int flow = g.maxFlow(1, 4);
    cout << "Fluxo maximo: " << flow << endl;

    return 0;
}
```
== Dijkstra
```cpp
// Exemplo de aplicacao do algoritmo de Dijkstra
// (assumindo um grafo pesado e dirigido, sem pesos negativos)

#include <iostream>
#include <climits>
#include <list>
#include <set>

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
        nodes = new Node[n+1];  // +1 se os nos comecam em 1 ao inves de 0
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
        for (int i=1; i<=n; i++) {
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
```
== Minimum Spanning Trees
=== Prim
The minimum spanning tree is built gradually by adding edges one at a time. At first the spanning tree consists only of a single vertex (chosen arbitrarily). Then the minimum weight edge outgoing from this vertex is selected and added to the spanning tree. After that the spanning tree already consists of two vertices. Now select and add the edge with the minimum weight that has one end in an already selected vertex (i.e. a vertex that is already part of the spanning tree), and the other end in an unselected vertex. And so on, i.e. every time we select and add the edge with minimal weight that connects one selected vertex with one unselected vertex. The process is repeated until the spanning tree contains all vertices (or equivalently until we have $n - 1$ edges).
In the end the constructed spanning tree will be minimal. If the graph was originally not connected, then there doesn't exist a spanning tree, so the number of selected edges will be less than $n - 1$.
==== Dense Graphs
```cpp
// We approach this problem from a different angle: for every not yet selected vertex we will store the minimum edge to an already selected vertex.
// Then during a step we only have to look at these minimum weight edges, which will have a complexity of O(n).
// After adding an edge some minimum edge pointers have to be recalculated. Note that the weights only can decrease, i.e. the minimal weight edge of every not yet selected vertex might stay the same, or it will be updated by an edge to the newly selected vertex. Therefore this phase can also be done in O(n).

int n;
vector<vector<int>> adj; // adjacency matrix of graph
const int INF = 1000000000; // weight INF means there is no edge

struct Edge {
    int w = INF, to = -1;
};

void prim() {
    int total_weight = 0;
    vector<bool> selected(n, false);
    vector<Edge> min_e(n);
    min_e[0].w = 0;

    for (int i=0; i<n; ++i) {
        int v = -1;
        for (int j = 0; j < n; ++j) {
            if (!selected[j] && (v == -1 || min_e[j].w < min_e[v].w))
                v = j;
        }

        if (min_e[v].w == INF) {
            cout << "No MST!" << endl;
            exit(0);
        }

        selected[v] = true;
        total_weight += min_e[v].w;
        if (min_e[v].to != -1)
            cout << v << " " << min_e[v].to << endl;

        for (int to = 0; to < n; ++to) {
            if (adj[v][to] < min_e[to].w)
                min_e[to] = {adj[v][to], v};
        }
    }

    cout << total_weight << endl;
}
```
==== Sparse Graphs
```cpp
// We can find the minimum edge in O(log n)$ time. 
// On the other hand recomputing the pointers will now take O(n log n) time, which is worse than in the previous algorithm.
// But when we consider that we only need to update O(m) times in total, and perform O(n) searches for the minimal edge, then the total complexity will be O(m log n). For sparse graphs this is better than the above algorithm, but for dense graphs this will be slower.

const int INF = 1000000000;

struct Edge {
    int w = INF, to = -1;
    bool operator<(Edge const& other) const {
        return make_pair(w, to) < make_pair(other.w, other.to);
    }
};

int n;
vector<vector<Edge>> adj;

void prim() {
    int total_weight = 0;
    vector<Edge> min_e(n);
    min_e[0].w = 0;
    set<Edge> q;
    q.insert({0, 0});
    vector<bool> selected(n, false);
    for (int i = 0; i < n; ++i) {
        if (q.empty()) {
            cout << "No MST!" << endl;
            exit(0);
        }

        int v = q.begin()->to;
        selected[v] = true;
        total_weight += q.begin()->w;
        q.erase(q.begin());

        if (min_e[v].to != -1)
            cout << v << " " << min_e[v].to << endl;

        for (Edge e : adj[v]) {
            if (!selected[e.to] && e.w < min_e[e.to].w) {
                q.erase({min_e[e.to].w, e.to});
                min_e[e.to] = {e.w, v};
                q.insert({e.w, e.to});
            }
        }
    }

    cout << total_weight << endl;
}
```
=== Kruskal
Kruskal's algorithm initially places all the nodes of the original graph isolated from each other, to form a forest of single node trees, and then gradually merges these trees, combining at each iteration any two of all the trees with some edge of the original graph. Before the execution of the algorithm, all edges are sorted by weight (in non-decreasing order). Then begins the process of unification: pick all edges from the first to the last (in sorted order), and if the ends of the currently picked edge belong to different subtrees, these subtrees are combined, and the edge is added to the answer. After iterating through all the edges, all the vertices will belong to the same sub-tree, and we will get the answer.
```cpp
struct Edge {
    int u, v, weight;
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

int n;
vector<Edge> edges;

int cost = 0;
vector<int> tree_id(n);
vector<Edge> result;
for (int i = 0; i < n; i++)
    tree_id[i] = i;

sort(edges.begin(), edges.end());

for (Edge e : edges) {
    if (tree_id[e.u] != tree_id[e.v]) {
        cost += e.weight;
        result.push_back(e);

        int old_id = tree_id[e.u], new_id = tree_id[e.v];
        for (int i = 0; i < n; i++) {
            if (tree_id[i] == old_id)
                tree_id[i] = new_id;
        }
    }
}
```
=== Kruskal with Disjoint Set Union
Just as in the simple version of the Kruskal algorithm, we sort all the edges of the graph in non-decreasing order of weights. Then put each vertex in its own tree (i.e. its set) via calls to the make_set function - it will take a total of $O(N)$. We iterate through all the edges (in sorted order) and for each edge determine whether the ends belong to different trees (with two find_set calls in $O(1)$ each). Finally, we need to perform the union of the two trees (sets), for which the DSU union_sets function will be called - also in $O(1)$. So we get the total time complexity of $O(M log N + N + M)$ = $O(M log N)$.
```cpp
vector<int> parent, rank;

void make_set(int v) {
    parent[v] = v;
    rank[v] = 0;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (rank[a] < rank[b])
            swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            rank[a]++;
    }
}

struct Edge {
    int u, v, weight;
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

int n;
vector<Edge> edges;

int cost = 0;
vector<Edge> result;
parent.resize(n);
rank.resize(n);
for (int i = 0; i < n; i++)
    make_set(i);

sort(edges.begin(), edges.end());

for (Edge e : edges) {
    if (find_set(e.u) != find_set(e.v)) {
        cost += e.weight;
        result.push_back(e);
        union_sets(e.u, e.v);
    }
}
```
== Bellman-Ford
Let us assume that the graph contains no negative weight cycle. The case of presence of a negative weight cycle will be discussed below in a separate section.

We will create an array of distances $d[0 \ldots n-1]$, which after execution of the algorithm will contain the answer to the problem. In the beginning we fill it as follows: $d[v] = 0$, and all other elements $d[ ]$ equal to $infinity$.

The algorithm consists of several phases. Each phase scans through all edges of the graph, and the algorithm tries to produce relaxation along each edge $(a,b)$ having weight $c$. Relaxation along the edges is an attempt to improve the value $d[b]$ using value $d[a] + c$. In fact, it means that we are trying to improve the answer for this vertex using edge $(a,b)$ and current answer for vertex $a$.
It is claimed that $n-1$ phases of the algorithm are sufficient to correctly calculate the lengths of all shortest paths in the graph (again, we believe that the cycles of negative weight do not exist). For unreachable vertices the distance $d[ ]$ will remain equal to $infinity$.

```cpp
struct Edge {
    int a, b, cost;
};

int n, m, v;
vector<Edge> edges;
const int INF = 1000000000;

void solve()
{
    vector<int> d(n, INF);
    d[v] = 0;
    for (;;) {
        bool any = false;

        for (Edge e : edges)
            if (d[e.a] < INF)
                if (d[e.b] > d[e.a] + e.cost) {
                    d[e.b] = d[e.a] + e.cost;
                    any = true;
                }

        if (!any)
            break;
    }
    // display d, for example, on the screen
}
```
=== Retrieving Path
```cpp
void solve()
{
    vector<int> d(n, INF);
    d[v] = 0;
    vector<int> p(n, -1);

    for (;;) {
        bool any = false;
        for (Edge e : edges)
            if (d[e.a] < INF)
                if (d[e.b] > d[e.a] + e.cost) {
                    d[e.b] = d[e.a] + e.cost;
                    p[e.b] = e.a;
                    any = true;
                }
        if (!any)
            break;
    }

    if (d[t] == INF)
        cout << "No path from " << v << " to " << t << ".";
    else {
        vector<int> path;
        for (int cur = t; cur != -1; cur = p[cur])
            path.push_back(cur);
        reverse(path.begin(), path.end());

        cout << "Path from " << v << " to " << t << ": ";
        for (int u : path)
            cout << u << ' ';
    }
}
```
=== Negative Cycle
```cpp
void solve()
{
    vector<int> d(n, INF);
    d[v] = 0;
    vector<int> p(n, -1);
    int x;
    for (int i = 0; i < n; ++i) {
        x = -1;
        for (Edge e : edges)
            if (d[e.a] < INF)
                if (d[e.b] > d[e.a] + e.cost) {
                    d[e.b] = max(-INF, d[e.a] + e.cost);
                    p[e.b] = e.a;
                    x = e.b;
                }
    }

    if (x == -1)
        cout << "No negative cycle from " << v;
    else {
        int y = x;
        for (int i = 0; i < n; ++i)
            y = p[y];

        vector<int> path;
        for (int cur = y;; cur = p[cur]) {
            path.push_back(cur);
            if (cur == y && path.size() > 1)
                break;
        }
        reverse(path.begin(), path.end());

        cout << "Negative cycle: ";
        for (int u : path)
            cout << u << ' ';
    }
}
```
== Floyd-Warshall
Let $d[][]$ is a 2D array of size $n times n$, which is filled according to the $0$-th phase as explained earlier. Also we will set $d[i][i] = 0$ for any $i$ at the $0$-th phase.

For $k = 0$, we can fill matrix with $d[i][j] = w_{i j}$ if there exists an edge between $i$ and $j$ with weight $w_{i j}$ and $d[i][j] = infinity$ if there doesn't exist an edge. In practice $infinity$ will be some high value.

```cpp
for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (d[i][k] < INF && d[k][j] < INF)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]); 
        }
    }
}
```
== KMP
=== Pseudocódigo dos slides:
```
KMP-Matcher(T, P)
n = T.length
m = P.length
pi = Compute-Prefix-Function(P)
q = 0
for i = 1 to n
    while q > 0 and P[q+1] != T[i]
        q = pi[q]
    if P[q+1] == T[i]
        q = q+1
    if q == m
        print "Pattern occurs with shift" i-m
        q = pi[q]

Compute-Prefix-Function(P)
m = P.length
let pi[1..m] be a new array
pi[1] = 0
k = 0
for q = 2 to m
    while k > 0 and P[k+1] != P[q]
        k = pi[k]
    if P[k+1] == P[q]
        k = k+1
    pi[q] = k
return pi
```
=== Prefix function definition
You are given a string $s$ of length $n$. The prefix function for this string is defined as an array $\pi$ of length $n$, where $\pi[i]$ is the length of the longest proper prefix of the substring $s[0...i]$ which is also a suffix of this substring. A proper prefix of a string is a prefix that is not equal to the string itself. By definition, $\pi[0] = 0$.

For example, prefix function of string "abcabcd" is $[0, 0, 0, 1, 2, 3, 0]$, and prefix function of string "aabaaab" is $[0, 1, 0, 1, 2, 2, 3]$.
```cpp
vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}
```
== Trie
```cpp
// C++ implementation of delete operations on Trie
#include <bits/stdc++.h>
using namespace std;

const int ALPHABET_SIZE = 26;

// trie node
struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];

    // isEndOfWord is true if the node represents end of a word
    bool isEndOfWord;
};

// Returns new trie node (initialized to NULLs)
struct TrieNode* getNode(void)
{
    struct TrieNode* pNode = new TrieNode;

    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(struct TrieNode* root, string key)
{
    struct TrieNode* pCrawl = root;

    for (int i = 0; i < key.length(); i++) {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf
    pCrawl->isEndOfWord = true;
}

// Returns true if key presents in trie, else false
bool search(struct TrieNode* root, string key)
{
    struct TrieNode* pCrawl = root;

    for (int i = 0; i < key.length(); i++) {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }

    return (pCrawl != NULL && pCrawl->isEndOfWord);
}

// Returns true if root has no children, else false
bool isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

// Recursive function to delete a key from given Trie
TrieNode* remove(TrieNode* root, string key, int depth = 0)
{
    // If tree is empty
    if (!root)
        return NULL;

    // If last character of key is being processed
    if (depth == key.size()) {

        // This node is no more end of word after removal of given key
        if (root->isEndOfWord)
            root->isEndOfWord = false;

        // If given is not prefix of any other word
        if (isEmpty(root)) {
            delete (root);
            root = NULL;
        }

        return root;
    }

    // If not last character, recur for the child obtained using ASCII value
    int index = key[depth] - 'a';
    root->children[index] = 
          remove(root->children[index], key, depth + 1);

    // If root does not have any child (its only child got 
    // deleted), and it is not end of another word.
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = NULL;
    }

    return root;
}

// Driver
int main()
{
    // Input keys (use only 'a' through 'z' and lower case)
    string keys[] = { "the", "a", "there",
                      "answer", "any", "by",
                      "bye", "their", "hero", "heroplane" };
    int n = sizeof(keys) / sizeof(keys[0]);

    struct TrieNode* root = getNode();

    // Construct trie
    for (int i = 0; i < n; i++)
        insert(root, keys[i]);

    // Search for different keys
    search(root, "the") ? cout << "Yes\n" : cout << "No\n";
    search(root, "these") ? cout << "Yes\n" : cout << "No\n";

    remove(root, "heroplane");
    search(root, "hero") ? cout << "Yes\n" : cout << "No\n";
    return 0;
}
```
== Aho-Corasick
Aho-Corasick Algorithm finds all words in O(n + m + z) time where z is total number of occurrences of words in text. The Aho-Corasick string matching algorithm formed the basis of the original Unix command fgrep. 

#underline[Preprocessing]: Build an automaton of all words in arr[] The automaton has mainly three functions:

- Go To: This function simply follows edges of Trie of all words in arr[]. It is represented as 2D array g[][] where we store next state for current state and character.
We build Trie. And for all characters which don't have an edge at root, we add an edge back to root.

- Failure: This function stores all edges that are followed when current character doesn't have edge in Trie.  It is represented as 1D array f[] where we store next state for current state.
For a state s, we find the longest proper suffix which is a proper prefix of some pattern. This is done using Breadth First Traversal of Trie.

- Output:  Stores indexes of all words that end at current state. It is represented as 1D array o[] where we store indexes of all matching words as a bitmap for current state.
For a state s, indexes of all words ending at s are stored. These indexes are stored as bitwise map (by doing bitwise OR of values). This is also computing using Breadth First Traversal with Failure.

#underline[Matching]: Traverse the given text over built automaton to find all matching words.
```cpp
// C++ program for implementation of Aho Corasick algorithm
// for string matching
using namespace std;
#include <bits/stdc++.h>

// Max number of states in the matching machine.
// Should be equal to the sum of the length of all keywords.
const int MAXS = 500;

// Maximum number of characters in input alphabet
const int MAXC = 26;

// OUTPUT FUNCTION IS IMPLEMENTED USING out[]
// Bit i in this mask is one if the word with index i
// appears when the machine enters this state.
int out[MAXS];

// FAILURE FUNCTION IS IMPLEMENTED USING f[]
int f[MAXS];

// GOTO FUNCTION (OR TRIE) IS IMPLEMENTED USING g[][]
int g[MAXS][MAXC];

// Builds the string matching machine.
// arr -   array of words. The index of each keyword is important:
//         "out[state] & (1 << i)" is > 0 if we just found word[i]
//         in the text.
// Returns the number of states that the built machine has.
// States are numbered 0 up to the return value - 1, inclusive.
int buildMatchingMachine(string arr[], int k)
{
    // Initialize all values in output function as 0.
    memset(out, 0, sizeof out);

    // Initialize all values in goto function as -1.
    memset(g, -1, sizeof g);

    // Initially, we just have the 0 state
    int states = 1;

    // Construct values for goto function, i.e., fill g[][]
    // This is same as building a Trie for arr[]
    for (int i = 0; i < k; ++i)
    {
        const string &word = arr[i];
        int currentState = 0;

        // Insert all characters of current word in arr[]
        for (int j = 0; j < word.size(); ++j)
        {
            int ch = word[j] - 'a';

            // Allocate a new node (create a new state) if a
            // node for ch doesn't exist.
            if (g[currentState][ch] == -1)
                g[currentState][ch] = states++;

            currentState = g[currentState][ch];
        }

        // Add current word in output function
        out[currentState] |= (1 << i);
    }

    // For all characters which don't have an edge from
    // root (or state 0) in Trie, add a goto edge to state
    // 0 itself
    for (int ch = 0; ch < MAXC; ++ch)
        if (g[0][ch] == -1)
            g[0][ch] = 0;

    // Now, let's build the failure function

    // Initialize values in fail function
    memset(f, -1, sizeof f);

    // Failure function is computed in breadth first order
    // using a queue
    queue<int> q;

     // Iterate over every possible input
    for (int ch = 0; ch < MAXC; ++ch)
    {
        // All nodes of depth 1 have failure function value
        // as 0. For example, in above diagram we move to 0
        // from states 1 and 3.
        if (g[0][ch] != 0)
        {
            f[g[0][ch]] = 0;
            q.push(g[0][ch]);
        }
    }

    // Now queue has states 1 and 3
    while (q.size())
    {
        // Remove the front state from queue
        int state = q.front();
        q.pop();

        // For the removed state, find failure function for
        // all those characters for which goto function is
        // not defined.
        for (int ch = 0; ch <= MAXC; ++ch)
        {
            // If goto function is defined for character 'ch'
            // and 'state'
            if (g[state][ch] != -1)
            {
                // Find failure state of removed state
                int failure = f[state];

                // Find the deepest node labeled by proper
                // suffix of string from root to current
                // state.
                while (g[failure][ch] == -1)
                      failure = f[failure];

                failure = g[failure][ch];
                f[g[state][ch]] = failure;

                // Merge output values
                out[g[state][ch]] |= out[failure];

                // Insert the next level node (of Trie) in Queue
                q.push(g[state][ch]);
            }
        }
    }

    return states;
}

// Returns the next state the machine will transition to using goto
// and failure functions.
// currentState - The current state of the machine. Must be between
//                0 and the number of states - 1, inclusive.
// nextInput - The next character that enters into the machine.
int findNextState(int currentState, char nextInput)
{
    int answer = currentState;
    int ch = nextInput - 'a';

    // If goto is not defined, use failure function
    while (g[answer][ch] == -1)
        answer = f[answer];

    return g[answer][ch];
}

// This function finds all occurrences of all array words
// in text.
void searchWords(string arr[], int k, string text)
{
    // Preprocess patterns.
    // Build machine with goto, failure and output functions
    buildMatchingMachine(arr, k);

    // Initialize current state
    int currentState = 0;

    // Traverse the text through the built machine to find
    // all occurrences of words in arr[]
    for (int i = 0; i < text.size(); ++i)
    {
        currentState = findNextState(currentState, text[i]);

        // If match not found, move to next state
        if (out[currentState] == 0)
             continue;

        // Match found, print all matching words of arr[]
        // using output function.
        for (int j = 0; j < k; ++j)
        {
            if (out[currentState] & (1 << j))
            {
                cout << "Word " << arr[j] << " appears from "
                     << i - arr[j].size() + 1 << " to " << i << endl;
            }
        }
    }
}

// Driver program to test above
int main()
{
    string arr[] = {"he", "she", "hers", "his"};
    string text = "ahishers";
    int k = sizeof(arr)/sizeof(arr[0]);

    searchWords(arr, k, text);

    return 0;
}
```
