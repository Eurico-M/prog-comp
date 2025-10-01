// Muito semelhante ao PC012, usar pesquisa binária no espaço de possibilidades.
//
// Duas diferenças: valores contínuos e o problema agora é de maximização (em vez de minimização).
// Para os valores contínuos, modificar o critério de paragem para ser um intervalo maior
// ou igual que a precisão pretendida.
// Para a maximização, o espaço de possibilidades é do tipo:
// [yes, yes,..., yes, no, no, ..., no]
// por isso, quando o middle verifica a condição, fazemos low = middle, e quando não verifica
// fazemos high = middle (o oposto da minimização do problema PC012).
//
// Para a condição booleana is_possible, usar novamente um algoritmo greedy que tenta
// dividir o volume de uma tarte pelo volume hipotético para obter o número de pessoas que
// pode alimentar.

#include <bits/stdc++.h>
#include <vector>
using namespace std;


bool is_possible(vector<int> pies, int people, double volume) {
    int max_people = 0;
    for (auto p : pies) {
        max_people += int(floor((M_PI * p * p)/volume));
        // cout << "pie " << p << " feeds " << int(floor((M_PI * p * p)/volume)) << " people\n";
    }

    return max_people >= people;
}


double my_binary_search(vector<int> pies, double low, double high, int people) {
    while (high-low >= 0.0001) {
        double middle = low + (high - low) / 2;
        // cout << "middle = " << middle << "\n";
        if (is_possible(pies, people, middle)) {
            low = middle;
        } else {
            high = middle;
        }
    }
    return low;
}

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    int test_cases;
    cin >> test_cases;

    for (int i = 0; i < test_cases; i++) {
        int nr_pies, friends;
        cin >> nr_pies >> friends;

        int people = friends + 1;

        vector<int> pies;
        int biggest_pie = 0;
        for (int j = 0; j < nr_pies; j++) {
            int p;
            cin >> p;
            pies.push_back(p);
            if (p > biggest_pie) {
                biggest_pie = p;
            }
        }

        double upper_bound = M_PI * biggest_pie * biggest_pie;
        double lower_bound = 0;

        // cout << "--- CASO " << i+1 << " ---\n";
        // cout << "pies = " << nr_pies << ", people = " << friends << " + 1 = " << people << "\n";
        // cout << "Pies: ";
        // for (auto x : pies) {
        //     cout << x << " ";
        // }
        // cout << "\n";

        double volume = my_binary_search(pies, lower_bound, upper_bound, people);

        cout << fixed;
        cout << setprecision(4);
        cout << volume << "\n";
    }

    return 0;
}
