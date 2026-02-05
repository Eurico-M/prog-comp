// Para gerar grafos grandes, pensei em simplesmente usar números aleatórios.
// Encontrei esta página no Geeks for Geeks:
// https://www.geeksforgeeks.org/cpp/how-to-generate-random-number-in-range-in-cpp/
//
// Este programa recebe 3 números como argumentos, e faz output de um 
// conjunto de números conforme indicado na secção "Input" do enunciado.
//
// Os números podem ser repetidos, mas isso faz parte do problema.

#include <bits/stdc++.h>
#include <random>

using namespace std;

int main(int argc, char *argv[]) {

    if (argc != 4) {
        cout << "Indicar como argumentos: número de t-shirts, dias, e restrições.\n";
    }
    int tshirts = atoi(argv[1]);
    int dias = atoi(argv[2]);
    int restr = atoi(argv[3]);

    // Initialize a random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib_a(1, tshirts);
    uniform_int_distribution<> distrib_b(1, dias);

    // Generate random number in the range [min, max]
    // int randomValueA = distrib_a(gen);
    // cout << "Random number between " << 1 << " and "
    //     << tshirts << " is " << randomValueA << endl;
    // int randomValueB = distrib_b(gen);
    // cout << "Random number between " << 1 << " and "
    //     << dias << " is " << randomValueB << endl;

    cout << tshirts << " " << dias << " " << restr << "\n";
    for (int i = 0; i < restr; i++) {
        cout << distrib_a(gen) << " " << distrib_b(gen) << "\n";
    }


    return 0;
}