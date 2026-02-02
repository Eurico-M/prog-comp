// Guardar os números numa estrutura Number que permite manter o valor decimal e a
// representação binária (como número de 1's).
//
// O cálculo do número de 1's é feito com a função calculate_nr_ones quando se recebe o
// input dos números: O(log n).
//
// Receber input, calcular representação binária, preencher vector: O(n.log n)
//
// Guardar estes Number num vector, e ordenar o vector com uma comparação compareNumbers:
// primeiro ordenar o número de 1's por ordem decrescente,
// e se forem iguais ordenar pelo valor do número.
//
// Usar sort() do C++: O(n.log n).
//
// Complexidade total: O(n.log n + n.log n) = O(n.log n);

#include <bits/stdc++.h>
using namespace std;

typedef struct {
    int value;
    int nr_ones;
} Number;

int calculate_nr_ones(int n) {
    int nr_ones = 0;

    while (n > 0) {
        nr_ones += n % 2;
        n = n / 2;
    };

    return nr_ones;
}

void test_print (vector<Number> &v) {
    for (auto x : v) {
        cout << x.value << ": " << x.nr_ones << " 1's\n";
    }
}

bool compareNumbers (Number &num1, Number &num2) {
    if (num1.nr_ones > num2.nr_ones) {
        return true;
    }
    if (num1.nr_ones < num2.nr_ones) {
        return false;
    }
    return (num1.value < num2.value);
}

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    int n;
    cin >> n;

    vector<Number> numbers;

    for (int i = 0; i < n; i++) {
        int input;
        cin >> input;

        Number num;
        num.value = input;
        num.nr_ones = calculate_nr_ones(input);
        numbers.push_back(num);
    }

    // test_print(numbers);

    sort(numbers.begin(), numbers.end(), compareNumbers);

    for (int i = 0; i < int(numbers.size()) - 1; i++) {
        cout << numbers[i].value << " ";
    }

    cout << numbers[numbers.size()-1].value << "\n";

    return 0;
}
