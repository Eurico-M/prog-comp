// Usar pesquisa binária no espaço de possibilidades.
//
// Criar um vector com as máquinas e inserir as máquinas, computando a máquina que demora
// mais tempo.
// Declarar o limite inferior (1 segundo) e superior (máquina que demora mais tempo a produzir
// todos os produtos).
// Fazer pesquisa binária nesse espaço de possibilidades: O(log n).
// A verificação da condição is_possible decide se é possível, num determinado tempo, fazer
// o número de produtos pretendido: O(n)
//
// Complexidade total: O(n.log n)

#include <bits/stdc++.h>
#include <vector>
using namespace std;

bool is_possible(vector<unsigned long long> machines, unsigned long long target_products, unsigned long long time) {
    unsigned long long products_made = 0;
    for (unsigned long long m : machines) {
        products_made += time / m;
    }

    return products_made >= target_products;
}

unsigned long long my_binary_search(vector<unsigned long long> machines, unsigned long long lower, unsigned long long upper, unsigned long long target_products) {
    while (lower < upper) {
        unsigned long long middle = lower + (upper - lower) / 2;
        // cout << "middle = " << middle << "\n";
        if (is_possible(machines, target_products, middle)) {
            upper = middle;
        } else {
            lower = middle + 1;
        }
    }

    if (!is_possible(machines, target_products, lower)) {
        return -1;
    }

    return lower;
}

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    unsigned long long n, t;
    cin >> n >> t;

    unsigned long long highest_value = 0;
    vector<unsigned long long> machines;

    for (unsigned long long i = 0; i < n; i++) {

        unsigned long long machine;
        cin >> machine;

        machines.push_back(machine);

        if (machine > highest_value) {
            highest_value = machine;
        }
    }

    unsigned long long lower_bound = 1;
    unsigned long long upper_bound = t * highest_value;

    unsigned long long minimum_time = my_binary_search(machines, lower_bound, upper_bound, t);

    cout << minimum_time << "\n";

    return 0;
}
