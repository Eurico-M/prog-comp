#include <bits/stdc++.h>
using namespace std;

void print_matrix(vector<vector<int>> m, int size) {
    for (int i = 1; i <= size; i++) {
        cout << "[";
        for (int j = 1; j <= size; j++) {
            if (m[i][j] < 0) {
                cout << " " << m[i][j];
            } else {
                cout << "  " << m[i][j];
            }
        }
        cout << " ]\n";
    }
}

int kadane(vector<vector<int>> sums, int size, int pos_i, int pos_j) {
    int max = -101;

    for (int i = 1; i <= pos_i; i++) {
        for (int j = 1; j <= pos_j; j++) {
            int sum = sums[pos_i][pos_j] - sums[i-1][pos_j] - sums[pos_i][j-1] + sums[i-1][j-1];
            if (sum > max) {
                max = sum;
            }
        }
    }

    return max;
}


int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    int n;
    cin >> n;

    // construir matriz e matriz de somas acumuladas
    vector<vector<int>> matrix(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> cumSums(n + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int num;
            cin >> num;
            matrix[i][j] = num;
            cumSums[i][j] = num + cumSums[i][j-1];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cumSums[j][i] = cumSums[j][i] + cumSums[j-1][i];
        }
    }

    cout << "Matrix:\n";
    print_matrix(matrix, n);
    cout << "\nCumSums:\n";
    print_matrix(cumSums, n);

    int max_sum = -101;

    // calcular para cada elemento da matriz de somas acumuladas
    // a maior soma
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            int sum_at = kadane(cumSums, n, i, j);
            if (sum_at > max_sum) {
                max_sum = sum_at;
            }
        }
    }

    cout << max_sum << "\n";

    return 0;
}
