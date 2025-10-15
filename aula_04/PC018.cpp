// Receber a sequência de números e guardar para usar mais tarde:
// sequence = [0,5,1,2,3,4,5]
//
// Receber primeiro as queries, para poder criar uma única segtree que responde a todos os queries:
// queries = [(2,4,1),(4,4,4),(1,6,2)]
//
// Põr todos os K das queries num set, para remover repetidos e ordenar:
// query_set = [1,2,4]
//
// Criar um dicionário auxiliar para ser mais fácil aceder a indexes:
// query_dictionary = [{1:0},{2:1},{4:2}]
//
// Criar o array auxiliar v[] para usar o build() da segtree. Cada elemento da segtree é um
// vector que nos diz, a cada posição, se os elementos desse range são maiores do que um K, para
// K valores do vector.
// Por exemplo, o primeiro elemento da sequência (5) é maior que 1, 2, e 4, logo:
// v[1] = [1,1,1]
// O quarto elemento da sequência (3) é só maior que 1 e 2, logo:
// v[4] = [1,1,0]
//
// O merge() da segtree é simplesmente somar os vectores elemento a elemento, tendo em atenção
// vectores vazios (NEUTRAL são vectores vazios).
//
// A resposta a um query da árvore é, portanto, um vector, que representa o número de vezes que,
// nesse range, os elementos da sequẽncia são maiores que os K todos.
// Depois é só usar o query_dictionary para descobrir o índice desse vector que corresponde ao
// query k que queremos responder.

#include <bits/stdc++.h>

using namespace std;

// -----------------------------------------------------------------
// An example simple segment tree implementation with arrays
// -----------------------------------------------------------------

const int MAX = 200005;   // Capacity of Segment Tree
const int MAX_ST = MAX*4;

const vector<int> NEUTRAL = {};    // Neutral element

typedef vector<int> st_value; // type of segment tree value

int n;               // Number of elements in the segtree
st_value v[MAX];     // Array of values
st_value st[MAX_ST]; // Segtree (in this case storing interval sums)

// Merge contents of nodes a and b
st_value merge(st_value a, st_value b) {
    // verificar vectores vazios, usar tamanho maior
    int size_a = a.size();
    int size_b = b.size();
    int size = max(size_a, size_b);

    vector<int> merge_result;

    for (int i = 0; i < size; i++) {
        if (a.empty()){
            merge_result.push_back(b[i]);
        } else if (b.empty()) {
            merge_result.push_back(a[i]);
        } else {
            merge_result.push_back(a[i]+b[i]);
        }
    }

    return merge_result;
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
    vector<int> sequence;
    sequence.push_back(0); // sentinela para sequence[0]

    // construir sequencia de números
    for (int i = 0; i < n; i++) {
        int number;
        cin >> number;
        sequence.push_back(number);
    }

    vector<tuple<int,int,int>> queries;
    set<int> query_set;

    // construir vector de queries (para responder depois)
    // construir query_set (para saber que números tenho de responder na segtree)
    for (int i = 0; i < q; i++) {
        tuple<int,int,int> query;
        int a, b, k;
        cin >> a >> b >> k;

        get<0>(query) = a;
        get<1>(query) = b;
        get<2>(query) = k;

        queries.push_back(query);
        query_set.insert(k);
    }

    // construir um dicionário para ser mais fácil saber o índice dos queries
    map<int,int> query_dictionary;
    int counter = 0;
    for (auto x : query_set) {
        query_dictionary.insert({x, counter});
        counter++;
    }

    // construir o array v[] para o build() da segtree
    for (int i = 1; i <= n; i++) {
        vector<int> v_k;
        for (auto x : query_set) {
            if (sequence[i] > x) {
                v_k.push_back(1);
            } else {
                v_k.push_back(0);
            }
        }
        v[i] = v_k;
    }

    build(1, 1, n);

    for (auto x : queries) {
        int a, b, k;
        tie(a, b, k) = x;

        vector<int> query_result = query(1, 1, n, a, b);
        int index = query_dictionary[k];
        int result = query_result[index];

        cout << result << "\n";
    }


    return 0;
}
