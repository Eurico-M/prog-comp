// Semelhante ao PC005, usar um dicionário do tipo (combinação, frequencia da combinação).
// A combinação é um conjunto (set) para ficar ordenado automaticamente e
// evitar repetições de combinações iguais que tenham configurações diferentes.
// Inserir 5 cursos no set: O(log n)
// Inserir set no dicionario: O(log n)
// Fazer as operações acima para n alunos: O(n.log n)
//
// Para cada dicionário (caso de teste), determinar o valor da frequência máxima (mais popular).
// Somar as frequências máximas para determinar o número de alunos que escolheram combinações
// mais populares.

#include <iostream>
#include <map>
#include <set>

int main () {
    int n_casos;
    std::cin >> n_casos;

    while (n_casos > 0) {
        std::map<std::set<int>,int> dicionario;

        for (int i = 0; i < n_casos; i++) {

            std::set<int> combinacao;
            for (int j = 0; j < 5; j++) {
                int curso;
                std::cin >> curso;
                combinacao.insert(curso);
            }

            dicionario[combinacao]++;
        }

        // Imprimir dicionário
        // for (auto x : dicionario) {
        //     for (auto y : x.first) {
        //         std::cout << y << " ";
        //     }
        //     std::cout << ": " << x.second << std::endl;
        // }

        int mais_popular = 0;

        for (auto x : dicionario) {
            if (x.second >= mais_popular) {
                mais_popular = x.second;
            }
        }

        int soma_freq_mais_popular = 0;

        for (auto x : dicionario) {
            if (x.second == mais_popular) {
                soma_freq_mais_popular += x.second;
            }
        }

        std::cout << soma_freq_mais_popular << std::endl;

        std::cin >> n_casos;
    }


    return 0;
}
