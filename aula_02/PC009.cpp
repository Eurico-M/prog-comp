// Usar dois sets: o set positions guarda os números que já foram usados para colocar semáforos,
// incluindo os extremos 0 e X. O multiset gaps guarda os intervalos entre os pontos em positions.
//
// Quando se recebe um novo semáforo (light), primeiro inserimo-lo em positions.
// Usamos um iterador para descobrir o local onde o semáforo foi inserido, e encontramos
// os valores imediatamente antes e imediatamente a seguir. Estes formam o segmento de estrada
// modificado.
// Calculamos o intervalo entre eles e removemos este intervalo do multiset gaps.
// Calculamos dois novos intervalos, entre o novo semáforo inserido e cada um dos pontos vizinhos,
// e colocamos estes novos intervalos no multiset gaps.
//
// O maior segmento sem semáforos é o maior valor do multiset gaps,
// que se pode obter directamente.
//
// Todas as operações com sets têm complexidade O(log n), logo o programa tem complexidade total
// O(n.log n)

#include <bits/stdc++.h>
using namespace std;

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    int x, n;
    cin >> x >> n;

    set<int> positions;
    multiset<int> gaps;

    positions.insert(0);
    positions.insert(x);
    gaps.insert(x);

    for (int i = 0; i < n; i++) {
        int light;
        cin >> light;

        positions.insert(light);

        auto it = positions.find(light);
        auto prv = prev(it);
        auto nxt = next(it);

        int gap_to_remove = *nxt - *prv;
        auto remove_it = gaps.find(gap_to_remove);
        gaps.erase(remove_it);

        int new_gap_before = light - *prv;
        int new_gap_after = *nxt - light;

        gaps.insert(new_gap_before);
        gaps.insert(new_gap_after);

        int largest_gap = *gaps.rbegin();
        cout << largest_gap << " ";
    }

    cout << "\n";

    return 0;
}
