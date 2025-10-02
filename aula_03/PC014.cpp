// Pesquisa ternária no espaço de possibilidades k (altura final dos edifícios).
//
// Função cost(k) calcula o custo de ter todos os edifícios à altura k: O(n).
// Fazer uma pesquisa ternária para o k mínimo: O(log3 n).
//
// Complexidade total: O(t.n.log n)

#include <bits/stdc++.h>
#include <vector>
using namespace std;

typedef struct {
    int height;
    int cost;
} Building;

void test_print(vector<Building> v) {
    cout << "Buildings:\n";
    for (auto x : v) {
        cout << x.height << ": " << x.cost << "\n";
    }
}

int cost(vector<Building> buildings, int k) {
    int cost = 0;
    for (auto x : buildings) {
        cost += abs(x.height - k) * x.cost;
    }
    return cost;
}

int my_ternary_search(vector<Building> buildings, int lower, int upper) {
    while (lower < upper) {
        int m1 = lower + (upper - lower) / 3;
        int m2 = lower + (upper - lower) * 2 / 3;

        int cost1 = cost(buildings, m1);
        int cost2 = cost(buildings, m2);

        // cout << "m1 = " << m1 << " cost = " << cost1 << "\n";
        // cout << "m2 = " << m2 << " cost = " << cost2 << "\n";

        if (cost1 < cost2) {
            upper = m2;
        } else if (cost1 > cost2) {
            lower = m1 + 1;
        } else {
            lower = m1;
            upper = m2;
        }
    }

    return lower;
}


int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    int nr_tests;
    cin >> nr_tests;

    for (int i = 0; i < nr_tests; i++) {
        int nr_buildings;
        cin >> nr_buildings;

        vector<Building> buildings;
        int highest_building = 0;

        for (int j = 0; j < nr_buildings; j++) {
            int height_in;
            cin >> height_in;

            Building b;
            b.height = height_in;
            b.cost = 0;
            buildings.push_back(b);

            if (height_in > highest_building) {
                highest_building = height_in;
            }
        }

        for (int j = 0; j < nr_buildings; j++) {
            int cost_in;
            cin >> cost_in;
            buildings[j].cost = cost_in;
        }

        // test_print(buildings);
        int lower = 1;
        int upper = highest_building + 1;
        // cout << "lower = " << lower << "   upper = " << upper << "\n";

        int k = my_ternary_search(buildings, lower, upper);
        cout << cost(buildings, k) << "\n";
    }

    return 0;
}
