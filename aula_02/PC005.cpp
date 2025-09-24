// Usar um dicionário (map) do tipo (número, frequência desse número na sequência).
// Inserir um valor no dicionário: O(log n)
// Inserir n valores: O(n.log n)
//
// Para cada entrada no dicionário,
// se o valor ocorrer mais vezes que o número, remover a diferença
// se o valor ocorrer menos vezes que o número, remover todas as ocorrências
// Aceder a n valores do dicionário: O(n.log n) ???

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

    int to_remove = 0;
    for (auto x : dicionario) {
        if (x.second > x.first) {
            to_remove += x.second - x.first;
        }
        if (x.second < x.first) {
            to_remove += x.second;
        }
    }

    std::cout << to_remove << std::endl;

    return 0;
}
