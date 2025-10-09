// Guardar maps na segtree. Os pares do mapa representam o valor e a frequência desse valor.
// Em cada nó da tree, o map tem no máximo 3 valores: o mais frequente,
// o valor mais à esquerda, e o valor mais à direita (do intervalo correspondente).
//
// Assim, para fazer um merge, é preciso:
// verificar se os dois valores mais "interiores" são iguais. se forem, somar as frequências.
// Calcular o valor mais frequente.
// Colocar no novo map: o mais frequente, e os dois valores dos "extremos".
//
// Isto porque os "extremos" podem somar-se com os extremos de outros ramos da árvore.
//
// Como o elemento neutro é um map vazio, verificar maps vazios antes de aceder aos iteradores.

#include <bits/stdc++.h>

using namespace std;

// -----------------------------------------------------------------
// An example simple segment tree implementation with arrays
// -----------------------------------------------------------------

const int MAX = 200005; // Capacity of Segment Tree
const int MAX_ST = MAX * 4;

const map<int,int> NEUTRAL = {}; // Neutral element

typedef map<int,int> st_value; // type of segment tree value

int n;               // Number of elements in the segtree
st_value v[MAX];     // Array of values
st_value st[MAX_ST]; // Segtree (in this case storing interval sums)

// Merge contents of nodes a and b
st_value merge(st_value a, st_value b) {
    map<int,int> return_map;

    int most_frequent = 0;
    int frequency = 0;

    // calcular se o último elemento do map da direita é
    // igual ao primeiro elemento do map da esquerda
    if (!a.empty() && !b.empty()) {
        auto last_a = a.end();
        last_a--;
        auto first_b = b.begin();

        // se forem iguais, somar as frequencias e assumir como "mais frequente" para já
        if (last_a->first == first_b->first) {
            most_frequent = last_a->first;
            frequency = last_a->second + first_b->second;
        }
    }

    // verificar o valor mais frequente nos dois maps
    for (auto x : a) {
        if (x.second > frequency) {
            frequency = x.second;
            most_frequent = x.first;
        }
    }

    for (auto x : b) {
        if (x.second > frequency) {
            frequency = x.second;
            most_frequent = x.first;
        }
    }

    // preencher novo return_map com: o mais frequente,
    // o mais à esquerda do mapa esquerdo, e o mais à direita do mapa direito
    if (frequency > 0) {
        return_map.insert({most_frequent, frequency});
    }

    if (!a.empty()) {
        auto first_a = a.begin();
        return_map.insert(*first_a);
    }
    if (!b.empty()) {
        auto last_b = b.end();
        last_b--;
        return_map.insert(*last_b);
    }

    return return_map;
}

// Build initial segtree (in position pos, interval [start,end])
void build(int pos, int start, int end) {
  if (start == end) {
    st[pos] = v[start];
  } else {
    int middle = start + (end - start) / 2;
    build(pos * 2, start, middle);
    build(pos * 2 + 1, middle + 1, end);
    st[pos] = merge(st[pos * 2], st[pos * 2 + 1]);
  }
}

// Update node n to value v
void update(int pos, int start, int end, int n, st_value v) {
  if (start > n || end < n)
    return;

  if (start == end) {
    st[pos] = v;

  } else {
    int middle = start + (end - start) / 2;
    update(pos * 2, start, middle, n, v);
    update(pos * 2 + 1, middle + 1, end, n, v);
    st[pos] = merge(st[pos * 2], st[pos * 2 + 1]);
  }
}

// Make a query of interval [a,b]
st_value query(int pos, int start, int end, int a, int b) {
  if (start > b || end < a)
    return NEUTRAL;
  if (start >= a && end <= b)
    return st[pos];

  int middle = start + (end - start) / 2;
  st_value l = query(pos * 2, start, middle, a, b);
  st_value r = query(pos * 2 + 1, middle + 1, end, a, b);
  return merge(l, r);
}

// ---------------------------------------------------------

int main() {
  int q;
  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    int w;
    cin >> w;

    map<int,int> m;
    m.insert({w,1});
    v[i] = m;
  }

  build(1, 1, n);

  for (int i = 1; i <= q; i++) {
    int a, b;
    cin >> a >> b;

    map<int,int> q_answer = query(1, 1, n, a, b);

    int frequency = 0;
    for (auto x : q_answer) {
        if (x.second > frequency) {
            frequency = x.second;
        }
    }

    cout << frequency << "\n";
  }

  return 0;
}
