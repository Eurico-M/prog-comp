#include <bits/stdc++.h>
using namespace std;

vector<int> seq;
vector<int> dp_LR;
vector<int> dp_RL;
int n;

void print_vector(vector<int> &v) {
    cout << "[";
    for (auto x : v) {
        cout << " " << x;
    }
    cout << " ]\n";
}

void receive_numbers() {
    seq.clear();
    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        seq.push_back(num);
    }
}

void configure_dp() {
    dp_LR.clear();
    dp_RL.clear();
    dp_LR.assign(n, -1);
    dp_RL.assign(n, -1);
}

int lis_LR(int idx) {
    if (idx == 0) {
        return dp_LR[idx] = 1;
    }

    if (dp_LR[idx] != -1) {
        return dp_LR[idx];
    }

    int max_temp = 1;
    for (int i = 0; i < idx; i++) {
        if (seq[i] < seq[idx]) {
            max_temp = max(max_temp, 1 + lis_LR(i));
        }
    }
    dp_LR[idx] = max_temp;
    return max_temp;
}

int lis_RL(int idx) {
    if (idx == n-1) {
        return dp_RL[idx] = 1;
    }

    if (dp_RL[idx] != -1) {
        return dp_RL[idx];
    }

    int max_temp = 1;
    for (int i = n-1; i > idx; i--) {
        if (seq[i] < seq[idx]) {
            max_temp = max(max_temp, 1 + lis_RL(i));
        }
    }
    dp_RL[idx] = max_temp;
    return max_temp;
}

int lis() {

    // Percorrer todos os elementos da sequência e tratá-los como se fossem o 'ponto central'
    // da wavio sequence: calcular a maior sequência válida à esquerda e à direita.
    // O mínimo destes valores pode ser usado para construir uma sequência wavio com os valores
    // do outro lado.
    //
    // O ponto central da maior sequência wavio será o que tiver o maior desses valores mínimos.
    int max_min = 0;
    for (int i = 0; i < n; i++) {
        max_min = max(max_min, min(lis_LR(i), lis_RL(i)));
    }
    return max_min * 2 - 1;
}

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    int n_tests;
    cin >> n_tests;

    for (int i = 0; i < n_tests; i++) {
        cin >> n;
        receive_numbers();
        configure_dp();

        // cout << "TEST #" << i + 1 << "\n";
        // print_vector(seq);
        cout << lis() << "\n";
        // print_vector(dp_LR);
        // print_vector(dp_RL);
    }

    return 0;
}
