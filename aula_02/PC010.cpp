#include <bits/stdc++.h>
using namespace std;

int set_cost(multiset<int> set, int median) {
    int cost = 0;

    for (auto x : set) {
        cost += abs(median - x);
    }

    return cost;
}

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    int n, k;
    cin >> n >> k;

    vector<int> window;
    int number_to_remove = 0;

    // criar vector da janela inicial
    for (int i = 0; i < k; i++) {
        int number;
        cin >> number;

        window.push_back(number);
        if (i == 0) {
            number_to_remove = number;
        }
    }

    // fazer sort e criar sets iniciais
    sort(window.begin(), window.end());

    multiset<int> left, right;
    int middle = window.size()/2;
    int median = window[middle];

    for (int i = 0; i < middle; i++) {
        left.insert(window[i]);
    }

    for (int i = middle + 1; i < (int)window.size(); i++) {
        right.insert(window[i]);
    }

    // calcular primeiro custo
    int cost = set_cost(left, median) + set_cost(right, median);
    cout << cost << " ";

    // cout << "Left set: ";
    // for (auto x : left) {
    //     cout << x << " ";
    // }
    // cout << "\nMedian: " << median << "\n";
    // cout << "Right set:";
    // for (auto x : right) {
    //     cout << x << " ";
    // }
    // cout << "\n";

    for (int i = 1; i + k - 1 < n; i++) {
        int number;
        cin >> number;

        // inserir novo número nos sets
        if (number >= median) {
            right.insert(number);
        } else {
            left.insert(number);
        }

        // remover número que já saiu da janela
        if (left.count(number_to_remove) > 0) {
            auto it = left.find(number_to_remove);
            left.erase(it);
            cost -= abs(number_to_remove - median);

        } else if (right.count(number_to_remove)) {
            auto it = right.find(number_to_remove);
            right.erase(it);
            cost -= abs(number_to_remove - median);

        } else {
            auto it = left.end();
            it--;
            median = *it;
            left.erase(it);
        }

        number_to_remove = number;

        // manter a mediana correcta
        if (left.size() - right.size() > 1) {
            right.insert(median);
            auto it = left.end();
            it--;
            median = *it;
            left.erase(it);

        } else if (right.size() - left.size() > 1) {
            left.insert(median);
            auto it = right.begin();
            median = *it;
            right.erase(it);
        }


    }

    return 0;
}
