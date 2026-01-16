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

    while (getline(cin, line)) {
        char dir = line[0];
        string nStr = line.substr(1);
        int n = stoi(nStr);
        // cout << "- Dial is rotated " << dir << nStr << "\n";

        // Pode haver rotações de mais de uma volta.
        // Contar rotações e remover voltas do N.
        if (n > 100) {
            password += n / 100;
            // cout << "   passes 0 " << n/100 << " times\n";
            n = n - (n/100) * 100;            
            // cout << "   corrected N is " << n << "\n";
        }

        if (dir == 'L') {
            n = - n;
        }

        // Verificar se passamos pelo 0. Se já começamos no 0, não conta.
        int new_dial = dial + n;
        // cout << "   new (raw) dial is " << new_dial << "\n";
        if (dial != 0 && (new_dial > 100 || new_dial < 0)) {
            password++;
            // cout << "   passed 0\n";
        }

        // Normalizar o resultado para o valor 'real'.
        dial = new_dial % 100;
        // Em C++, -18 % 100 = -18, em vez de 82. Corrigir isso aqui.
        if (dial < 0) {
            dial += 100;
        }
        // cout << "   new (correct) dial is " << dial << "\n";
        if (n != 0 && dial == 0) {
            password++;
            // cout << "   is at 0\n";
        }
    }

    cout << "password is: " << password << "\n";

    return 0;
}