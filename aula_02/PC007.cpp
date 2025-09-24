// Usar um conjunto (song_set) para guardar as canções.
// Antes de inserir, verificar se a canção já está no conjunto.
// Se estiver, limpar o conjunto e só depois inserir.
// Depois de inserir cada canção, guardar o maior tamanho do conjunto,
// que é a maior sequência de canções únicas.
//
// Inserir uma canção no conjunto: O(log n)
// Determinar o tamanho: O(1)
// Computar n canções: O(n.log n)

#include <iostream>
#include <set>

int main() {
    int nr_songs;
    std::cin >> nr_songs;

    int longest_sequence = 1;
    std::set<int> song_set;

    for (int i = 0; i < nr_songs; i++) {
        int song;
        std::cin >> song;

        if (song_set.count(song) > 0) {
            song_set.clear();
            song_set.insert(song);
        } else {
            song_set.insert(song);
        }

        if (int(song_set.size()) > longest_sequence) {
            longest_sequence = song_set.size();
        }
    }

    std::cout << longest_sequence << std::endl;

    return 0;
}
