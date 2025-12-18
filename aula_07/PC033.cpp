// Num qualquer estado solve(nA, nB, sK, sC):
// nA: número de jogadores escolhidos pela Alice até agora,
// nB: número de jogadores escolhidos pelo Bob até agora,
// sK: run de escolhas consecutivas por parte de um jogador,
// sC: jogador a que a run de sK diz respeito. (para efeitos da matriz de memoization, tive de
// representar 'A' como 0 e 'B' como 1)
//
// Assim, num qualquer estado, podemos adicionar um A ou um B, com as restrições:
// Se a run já tiver ultrapassado o limite k, não podemos adicionar nada.
// Se o número de B's não for menor que o número de A's, não podemos adicionar um B.
//
// Ao adicionar um A ou B, verificar se a run atual é desse tipo.
// Se for, incrementar a run. Se não, fazer reset do sK para 1.
// Em qualquer dos casos, sC é marcado como a escolha que foi feita.
//
// Parar a recursão quando:
// Tivermos chegado a uma configuração válida (nA == nB == n/2), retornar 1.
// Se nA ou nB exceder n/2, configuração inválida, retornar 0.


#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n, k;
vector<vector<vector<vector<ll>>>> dp;

// void print_dp() {
//     for (auto a : dp) {
//         for (auto b : a) {
//             for (auto c : b) {
//                 for (auto d : c) {
//                     cout << " " << d;
//                 }
//                 cout << "\n";
//             }
//             cout << "\n";
//         }
//         cout << "\n";
//     }
// }

ll solve(int nA, int nB, int sK, int sC) {
    // cout << "nA=" << nA << " nB=" << nB << " sK=" << sK << " sC=" << sC << "\n";
    
    if (nA > n/2 || nB > n/2) {
        // return dp[nA][nB][sK][sC] = 0;
        return 0;
    }
    if (nA == n/2 && nB == n/2) {
        // cout << "found one!\n";
        return dp[nA][nB][sK][sC] = 1;
        // return 1;
    }

    if (dp[nA][nB][sK][sC] != -1) {
        return dp[nA][nB][sK][sC];
    }

    ll num = 0;

    // adicionar um A
    if (nA < n/2) {
        // se o último não foi um A
        if (sC != 0) { 
            num += solve(nA + 1, nB, 1, 0);
        }
        // se o último foi um A mas ainda é possível continuar a run
        else if (sK < k) { 
            num += solve(nA + 1, nB, sK + 1, 0);
        }
    }
    // adicionar um B se permitido
    if (nB < nA && nB < n/2) {
        // se o último não foi um B
        if (sC != 1) {
            num += solve(nA, nB + 1, 1, 1);
        }
        // se o último foi um B mas é possível continuar a run
        else if (sK < k) {
            num += solve(nA, nB + 1, sK + 1, 1);
        }
    }
    // return num;
    return dp[nA][nB][sK][sC] = num;
}

int main() {
    // Fast IO
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    //

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        cin >> n >> k;
        dp.clear();
        dp.assign(n/2 + 1,
            vector<vector<vector<ll>>> (n/2 + 1, 
            vector<vector<ll>> (k + 2,
            vector<ll> (2, -1))));
        // print_dp();
        cout << solve(1, 0, 1, 0) << "\n";
    }

    return 0;
}
