// Para cada um dos casos:
//
// Guardar os lemmings em dois exércitos, green_army e blue_army, que são multisets,
// para poderem ter lemmings com o mesmo nível, e para estarem ordenados (por ordem crescente,
// por isso retirar sempre do fim, e não do início): O(log n)
//
// Enquanto os dois exércitos tiverem ambos lemmings:
// Criar duas "reservas" para colocar os lemmings que já combateram nessa ronda.
// As reservas não precisam de estar ordenadas, por isso usar uma lista para ser mais eficiente
// adicionar e remover.
//
// Para cada batalha:
// Se os dois exércitos estiverem vazios, acabar as rondas de batalha.
// Se um dos exércitos estiver vazio, o outro ganha automaticamente: colocar o lemming vencedor
// nas reservas e retirá-lo do exército.
// Se não, então há conflito: escolher o lemming mais forte de cada exército (última posição),
// sem esquecer de os retirar do exército.
// Comparar os dois valores: o vencedor fica diminuído do valor do vencido, e vai para as
// reservas. O vencido apenas desaparece.
// Similarmente, se os dois tiverem o mesmo valor, apenas desaparecem.
//
// No fim da ronda de batalhas, reforçar os exércitos com as reservas e repetir o ciclo
// enquanto os dois exércitos tiverem ambos lemmings.
//
// Quando um dos exércitos estiver vazio, verificar qual, e imprimir a mensagem correspondente,
// juntamente com o exército vencedor (se houver).
//
// Em n casos, em b batalhas, fazer inserções e remoções em forward_lists(O(1)) e
// multisets(O(log n)), logo O(n.b.log n)

#include <forward_list>
#include <iostream>
#include <set>
#include <forward_list>

void recruit_lemmings(int nr_lemmings, std::multiset<int> &army) {
    for (int i = 0; i < nr_lemmings; i++) {
        int lemming;
        std::cin >> lemming;
        army.insert(lemming);
        //std::cout << "recruited " << lemming << std::endl;
    }
}

void print_army(std::multiset<int> &army) {
    for (auto it = army.rbegin(); it != army.rend(); it++) {
        std::cout << *it << std::endl;
    }
}

void automatic_win(std::multiset<int> &army, std::forward_list<int> &reserves) {
    auto it = army.end();
    it--;
    reserves.push_front(*it);
    army.erase(it);
}

void win(int winner, int loser, std::forward_list<int> &reserves) {
    winner = winner - loser;
    reserves.push_front(winner);
}

void resupply(std::multiset<int> &army, std::forward_list<int> &reserves) {
    while (!reserves.empty()) {
        int backup = reserves.front();
        army.insert(backup);
        reserves.pop_front();
    }
}

int main() {
    int nr_cases;
    std::cin >> nr_cases;

    for (int i = 0; i < nr_cases; i++) {
        int battlefields, nr_greens, nr_blues;
        std::cin >> battlefields >> nr_greens >> nr_blues;

        std::multiset<int> green_army;
        std::multiset<int> blue_army;

        recruit_lemmings(nr_greens, green_army);
        recruit_lemmings(nr_blues, blue_army);

        // std::cout << "green army:" << std::endl;
        // print_army(green_army);
        // std::cout << "blue army:" << std::endl;
        // print_army(blue_army);

        while (int(green_army.size()) > 0 && int(blue_army.size()) > 0) {
            std::forward_list<int> green_reserves;
            std::forward_list<int> blue_reserves;

            for (int j = 0; j < battlefields; j++) {
                if (green_army.empty() && blue_army.empty()) {
                    break;
                } else if (green_army.empty()) {
                    automatic_win(blue_army, blue_reserves);
                } else if (blue_army.empty()) {
                    automatic_win(green_army, green_reserves);
                } else {
                    auto green_it = green_army.end();
                    green_it--;
                    auto blue_it = blue_army.end();
                    blue_it--;
                    int green_lemming = *green_it;
                    int blue_lemming = *blue_it;
                    green_army.erase(green_it);
                    blue_army.erase(blue_it);

                    if (green_lemming > blue_lemming) {
                        win(green_lemming, blue_lemming, green_reserves);
                    } else if (blue_lemming > green_lemming) {
                        win(blue_lemming, green_lemming, blue_reserves);
                    }
                }
            }

            resupply(green_army, green_reserves);
            resupply(blue_army, blue_reserves);
        }

        if (green_army.empty() && blue_army.empty()) {
            std::cout << "green and blue died" << std::endl;

        } else if (green_army.empty()) {
            std::cout << "blue wins" << std::endl;
            print_army(blue_army);

        } else {
            std::cout << "green wins" << std::endl;
            print_army(green_army);
        }

        if (i < nr_cases - 1) {
            std::cout << std::endl;
        }
    }

    return 0;
}
