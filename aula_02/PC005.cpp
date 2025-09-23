#include <iostream>
#include <map>

int main () {
    int n_elementos;
    std::cin >> n_elementos;

    std::map<int,int> dicionario;
    for (int i = 0; i < n_elementos; i++) {
        int numero;
        std::cin >> numero;
        dicionario[numero]++;
    }

    // for (auto x : dicionario) {
    //     std::cout << x.first << " " << x.second << std::endl;
    // }

    return 0;
}
