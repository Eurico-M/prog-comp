// Guardar as arestas num dicionário, assim ficam ordenadas por 'n'.
//
// Uma aresta NiMi vai ter intersecções se as arestas anteriores forem do tipo NkMj, com k < i e j > i.
// k < i é garantindo porque estamos a percorrer as arestas ordenadas por 'n'.
// Só temos de verificar quantos valores j > i apareceram até agora.
//
// Ou seja, quantas arestas que começam em nós anteriores de N acabam em nós posteriores de M.
// Só precisamos de guardar as frequências dos 'm' que apareceram até agora (numa BIT) e,
// para cada aresta NM, perguntar quantos 'm' maiores que M apareceram.
//
// Ou seja, fazer um range query a uma BIT tree do tipo sum[l,r] (que é sum[0,r] - sum[0,l-1])
//
// Para os updates, temos de guardar os valores de 'm' num stack temporário e só fazer updates
// se o 'n' seguinte for diferente. Isto porque, por exemplo, as arestas 3,1 e 3,2 não se intersectam.

#include <bits/stdc++.h>
using namespace std;

#define ll long long int

void print_vector(vector<ll> v) {
    cout << "[";
    for (auto k : v) {
        cout << " " << k;
    }
    cout << " ]\n";
}

// Implementação da BIT

vector<ll> tree;
ll maxIdx;

ll read(ll idx) {
    ll sum = 0;
    while (idx > 0) {
        sum += tree[idx];
        idx -= (idx & -idx);
    }
    return sum;
}

ll sum(ll l, ll r) {
    return read(r) - read(l - 1);
}

void update(ll idx, ll val) {
    while (idx <= maxIdx) {
        tree[idx] += val;
        //cout << "tree[" << idx << "]=" << tree[idx] << "\n";
        idx += (idx & -idx);
    }
}
/////////////////////////



int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    ll n, m, k;
    cin >> n >> m >> k;

    maxIdx = m;
    multimap<ll,ll> roads;
    tree.assign(m+1, 0);

    for (ll i = 0; i < k; i++) {
        ll n1, m1;
        cin >> n1 >> m1;
        roads.insert({n1, m1});
    }

    stack<ll> temp_update;
    ll prev = 0;
    ll crossing_sum = 0;

    for (auto x : roads) {
        // print_vector(tree);
        if (x.first != prev) {
            while (!temp_update.empty()) {
                update(temp_update.top(), 1);
                // cout << "updating " << temp_update.top() << "\n";
                temp_update.pop();
            }
        }
        // print_vector(tree);
        // cout << "{ " << x.first << " , " << x.second << " }\n";
        ll temp_sum = sum(x.second + 1, maxIdx);
        crossing_sum += temp_sum;
        // cout << "temp_sum=" << temp_sum << " crossing_sum=" << crossing_sum << "\n";

        temp_update.push(x.second);
        prev = x.first;

    }

    cout << crossing_sum << "\n";

    return 0;
}
