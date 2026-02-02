// Pesquisa ternária no espaço de possibilidades k (altura final dos edifícios).
//
// Função cost(k) calcula o custo de ter todos os edifícios à altura k: O(n).
// Fazer uma pesquisa ternária para o k mínimo: O(log3 n).
// A pesquisa ternária tem de ter um critério de paragem ligeiramente diferente porque,
// como o espaço de pesquisa é discreto, a divisão ternária não pode ser aplicada a espaços
// menores que 3.
// Assim, quando reduzimos o espaço de possibilidades a 3 inteiros, fazemos uma pesquisa
// linear nesses 3 inteiros.
//
// Complexidade total: O(t.n.log n)

#include <bits/stdc++.h>
using namespace std;

typedef struct {
    long height;
    long cost;
} Building;

void test_print(vector<Building> v) {
    cout << "Buildings:\n";
    for (auto x : v) {
        cout << x.height << ": " << x.cost << "\n";
    }
}

long cost(vector<Building> buildings, long k) {
    long cost = 0;
    for (auto x : buildings) {
        cost += abs(x.height - k) * x.cost;
    }
    return cost;
}

long my_ternary_search(vector<Building> buildings, long lower, long upper) {
    while (upper - lower > 3) {
        // long m1 = (2 * lower + upper) / 3;
        // long m2 = (lower + 2 * upper) / 3;

        long m1 = lower + (upper - lower) / 3;
        long m2 = upper - (upper - lower) / 3;

        long cost1 = cost(buildings, m1);
        long cost2 = cost(buildings, m2);

        // cout << "m1 = " << m1 << " cost = " << cost1 << "\n";
        // cout << "m2 = " << m2 << " cost = " << cost2 << "\n";

        if (cost1 < cost2) {
            upper = m2;
        } else if (cost1 > cost2) {
            lower = m1;
        } else {
            lower = m1;
            upper = m2;
        }
    }

    long min_cost = cost(buildings, lower);
    long k = lower;

    for (long i = lower; i <= upper; i++) {
        long c = cost(buildings, i);
        if (c < min_cost) {
            min_cost = c;
            k = i;
        }
    }

    return k;
}


int main() {
    // Fast IO
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    //

    long nr_tests;
    cin >> nr_tests;

    for (long i = 0; i < nr_tests; i++) {
        long nr_buildings;
        cin >> nr_buildings;

        vector<Building> buildings;
        long highest_building = 0;

        for (long j = 0; j < nr_buildings; j++) {
            long height_in;
            cin >> height_in;

            Building b;
            b.height = height_in;
            b.cost = 0;
            buildings.push_back(b);

            if (height_in > highest_building) {
                highest_building = height_in;
            }
        }

        for (long j = 0; j < nr_buildings; j++) {
            long cost_in;
            cin >> cost_in;
            buildings[j].cost = cost_in;
        }

        // test_print(buildings);
        long lower = 1;
        long upper = highest_building;
        // cout << "lower = " << lower << "   upper = " << upper << "\n";

        long k = my_ternary_search(buildings, lower, upper);
        cout << cost(buildings, k) << "\n";
    }

    return 0;
}
