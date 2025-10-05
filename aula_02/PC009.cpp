// Manter uma lista de dicionários.
// Cada dicionário corresponde a uma configuração da rua com semáforos:
// Antes de incluir semáforos, a rua é do tipo ({0,n},{n,0}), ou seja, no ponto 0 temos um
// segmento livre de tamanho n, e no ponto n temos um segmento livre de tamanho 0.
//
// Quando inserimos um semáforo na rua no ponto 2, o dicionário passa a ser:
// ({0,2},{2,3},{5,0}), ou seja, no ponto 0 começa um segmento livre de tamanho 2, no ponto
// 2 começa um segmento livre de tamanho 3, e no ponto 5 começa um segmento livre de tamanho 0.
//
// Assim, para um qualquer ponto inserido no dicionário, só temos de mudar os dois pontos
// adjacentes A e B (que é o equivalente a cortar esse segmento entre os pontos A e B, o resto
// da rua mantém-se inalterada).
//
// Assim, podemos ter uma criação dos dicionários linearitmica, e noutro ciclo procurar em cada
// dicionário qual o valor máximo dos intervalos, que também é uma operação linearítmica, e o
// programa fica todo com complexidade O(n.log n).

#include <bits/stdc++.h>
using namespace std;

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    int x, n;
    cin >> x >> n;

    list<map<int,int>> street_over_time;

    map<int,int> initial_lights;
    initial_lights.insert({0,x});
    initial_lights.insert({x,0});

    street_over_time.push_back(initial_lights);

    for (int i = 0; i < n; i++) {
        int light;
        cin >> light;

        map<int,int> lights_at_certain_time;
        lights_at_certain_time = street_over_time.back();
        lights_at_certain_time.insert({light,0});

        auto it = lights_at_certain_time.find(light);
        auto prv = prev(it);
        auto nxt = next(it);

        prv->second = light - prv->first;
        it->second = nxt->first - light;

        street_over_time.push_back(lights_at_certain_time);
    }

    auto cur = street_over_time.begin();
    cur++;

    while (cur != street_over_time.end()) {
        set<int> distances;
        for (auto x : *cur) {
            distances.insert(x.second);
        }
        auto max = distances.end();
        max--;
        cout << *max << " ";
        cur++;
    }

    cout << "\n";

    return 0;
}
