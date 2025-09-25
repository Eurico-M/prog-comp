// 1 2 3 4    4 3 2 1
// 1 2 3 4 -> 3 2 1 4
// 1 2 3 4    2 1 4 3
// 1 2 3 4    1 4 3 2
//
// A primeira linha inverte totalmente
// A segunda linha inverte de 1 a 3, e de 4 a 4
// A terceira linha inverte de 1 a 2, e de 3 a 4
// A quarta linha inverte de 1 a 1, e de 2 a 4
//
// Assim, o número de operações é sempre 2*n-1
// (podiam ser menos, se retirasse as operações que invertem um único valor)
//
// Para cada caso: O(n)

#include <iostream>

int main() {
    int nr_cases;
    std::cin >> nr_cases;

    for (int i = 0; i < nr_cases; i++) {
        int n;
        std::cin >> n;

        int k = 2*n - 1;
        std::cout << k << std::endl;

        std::cout << "1 1 " << n << std::endl;
        for (int j = 1; j < n; j++) {
            std::cout << j+1 << " 1 " << n-j << std::endl;
            std::cout << j+1 << " " << n+1-j << " " << n << std::endl;
        }
    }

    return 0;
}
