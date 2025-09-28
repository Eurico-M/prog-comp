// Primeiro, vi que o número de zeros aumentava de 5 em 5, por isso comecei por fazer n/5.
// Depois vi que em 25 havia um salto, e fiz n/5 + n/25.
// Quando vi o salto em 125, percebi que tinha de fazer:
// n/5 + n/25 + n/125 + n/625 ...
// n/(5^1) + n/(5^2) + n/(5^3) + n/(5^4) ...
// (e também porque o professor na aula tinha falado em potências de 5)
//
// Escrevi uma função para calcular potências porque o C++ não tem potências incluidas
// no standard, e a função pow() do <cmath> retorna um double, que depois me estraga a
// divisão inteira. Se calhar há uma maneira fácil de fazer cast de double para int,
// quando sabemos que o double é sempre um int.

#include <iostream>

int potencia(int n, int k) {
    int base = n;
    for (int i = 1; i < k; i++) {
        n = n * base;
    }
    return n;
}

int main() {
    int n;
    std::cin >> n;

    int trailing_zeroes = 0;
    int k = 1;

    // trailing_zeroes = potencia(5, 4);

    while (potencia(5,k) <= n) {
        trailing_zeroes += n/potencia(5,k);
        k++;
    }

    std::cout << trailing_zeroes << std::endl;

    return 0;
}
