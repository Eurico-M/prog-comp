// Construir a matriz de somas cumulativas.
// Fixar duas linhas da matriz, e usar Kadane como se as colunas delimitadas por essas
// linhas fossem elementos únicos (a soma da coluna).

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

// soma de uma coluna j, desde i_start até i_end
int column(vector<vector<int>> & sums, int i_start, int i_end, int j) {
    return sums[i_end][j] - sums[i_start-1][j] - sums[i_end][j-1] + sums[i_start-1][j-1];
}

// kadane numa dimensão 'n', delimitada por duas linhas 'a' e 'b'
int kadane(vector<vector<int>> & sums, int size, int a, int b) {
    int current_sum = column(sums, a, b, 1);
    int best_sum = current_sum;

    for (int n = 2; n <= size; n++) {
        current_sum = max(column(sums, a, b, n), current_sum + column(sums, a, b, n));
        best_sum = max(best_sum, current_sum);
    }

    return best_sum;
}


int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    int n;
    cin >> n;

    // construir matriz e matriz de somas acumuladas
    //vector<vector<int>> matrix(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> cumSums(n + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int num;
            cin >> num;
            //matrix[i][j] = num;
            cumSums[i][j] = num + cumSums[i][j-1];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cumSums[j][i] = cumSums[j][i] + cumSums[j-1][i];
        }
    }

    // cout << "Matrix:\n";
    // print_matrix(matrix, n);
    // cout << "\nCumSums:\n";
    // print_matrix(cumSums, n);

    int max_sum = -101;

    // fixar linhas (a e b) e usar Kadane nessa dimensão
    for (int a = 1; a <= n; a++) {
        for (int b = a; b <= n; b++) {
            int sum_at = kadane(cumSums, n, a, b);
            if (sum_at > max_sum) {
                max_sum = sum_at;
            }
        }
    }

    cout << max_sum << "\n";

    return 0;
}
