#include <iostream>

int main() {
    int size;
    std::cin >> size;

    long int moves = 0;
    int prev;
    std::cin >> prev;

    // um ciclo, O(n)
    for (int i = 0; i < size - 1; i++) {
        int cur;
        std::cin >> cur;

        // comparar os números sem guardar o array
        int diff = prev - cur;
        // se o segundo número for menor, guardar o número de jogadas necessárias
        // para o tornar igual, e fazer update do número
        if (diff > 0) {
            moves += diff;
            cur += diff;
        }

        prev = cur;
    }

    std::cout << moves << std::endl;

    return 0;
}
