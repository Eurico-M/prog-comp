#include <bits/stdc++.h>
using namespace std;

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    string line;
    int dial = 50;
    int password = 0;
    
    // ler input linha a linha
    while (getline(cin, line)) {
        // separar letra e número
        char dir = line[0];
        string nStr = line.substr(1);
        int n = stoi(nStr);
        // número negativo se for para a esquerda
        if (dir == 'L') {
            n = -n;
        }
        // fazer rotação em base 100
        dial = (dial + n) % 100;
        // se parar no zero, contar
        if (dial == 0) {
            password++;
        }

    }

    cout << "password is: " << password << "\n";

    return 0;
}