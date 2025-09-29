// Tive ajuda do André Mendes, e gerei casos de teste com o DeepSeek (tinha erros em casos
// privados).
//
// Manter um dicionário com as últimas posições de cada canção.
// Quando se lê uma canção, verificar se já está no dicionário.
// Se estiver, apagar do dicionário todas as canções com uma posição menor que essa canção
// (incluindo a própria canção).
//
// Atualizar o dicionário.
//
// Verificar se o tamanho do dicionário é maior que a maior sequência, atualizando se necessário.

#include <iostream>
#include <map>

int main() {
    int nr_songs;
    std::cin >> nr_songs;

    std::map<int,int> last_position;
    int longest_sequence = 1;

    for (int i = 0; i < nr_songs; i++) {
        int song;
        std::cin >> song;

        if (last_position.count(song) > 0) {
            int cutoff = last_position[song];
            for (auto it = last_position.begin(); it != last_position.end();) {
                if (it->second <= cutoff) {
                    it = last_position.erase(it);
                } else {
                    ++it;
                }
            }
        }

        last_position[song] = i;

        if (int(last_position.size()) > longest_sequence) {
            longest_sequence = int(last_position.size());
        }

    }

    std::cout << longest_sequence << std::endl;

    return 0;
}
