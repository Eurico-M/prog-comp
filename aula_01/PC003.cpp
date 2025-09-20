#include <iostream>
#include <string>

int main() {
    short int cases;
    std::cin >> cases;

    // O(número de casos)
    for (int i = 0; i < cases; i++) {
        std::string a, b;
        std::cin >> a >> b;

        // usar um cursor k para percorrer a string A
        int k = 0;
        bool found = false;
        // percorrer a string B, O(tamanho de B)
        for (int j = 0; j < int(b.length()); j++) {
            // comparar cada caracter, avançando k se a string for igual
            if (b[j] == a[k]) {
                k++;
            }
            // se k chegar ao fim de A, encontramos toda a substring
            if (k == int(a.length())) {
                found = true;
                break;
            }
        }

        if (found) {
            std::cout << "yes" << std::endl;
        } else {
            std::cout << "no" << std::endl;
        }
    }

    return 0;
}
