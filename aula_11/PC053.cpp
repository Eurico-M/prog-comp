#include <bits/stdc++.h>
using namespace std;

// calcular a intersecção numa dimensão de dois segmentos de recta A e B
// o resultado é um par de pontos que representa o segmento de recta nessa dimensão
pair<int,int> intersect_1D(int A1, int A2, int B1, int B2) {
    // se as coordenadas não intersectarem, devolver 0
    if (B1 >= A2 || B2 <= A1) {
        return {0, 0};
    }
    
    pair<int,int> res;
    res.first = max(A1, B1);
    res.second = min(A2, B2);
    return res;    
}

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    int n_cubes;
    cin >> n_cubes;

    while (n_cubes > 0) {

        // receber o primeiro cubo
        int Ax1, Ay1, Az1, Ad;
        cin >> Ax1 >> Ay1 >> Az1 >> Ad;
        // representar o cubo como 3 segmentos de recta
        pair<int,int> Ax = {Ax1, Ax1 + Ad};
        pair<int,int> Ay = {Ay1, Ay1 + Ad};
        pair<int,int> Az = {Az1, Az1 + Ad};

        // para todos os cubos subsequentes
        for (int i = 0; i < n_cubes - 1; i++) {
            // receber o segundo cubo
            int Bx1, By1, Bz1, Bd;
            cin >> Bx1 >> By1 >> Bz1 >> Bd;

            pair<int,int> Bx = {Bx1, Bx1 + Bd};
            pair<int,int> By = {By1, By1 + Bd};
            pair<int,int> Bz = {Bz1, Bz1 + Bd};

            // calcular as intersecções de cada dimensão
            pair<int,int> Cx = intersect_1D(Ax.first, Ax.second, Bx.first, Bx.second);
            pair<int,int> Cy = intersect_1D(Ay.first, Ay.second, By.first, By.second);
            pair<int,int> Cz = intersect_1D(Az.first, Az.second, Bz.first, Bz.second);

            // o resultado da intersecção (cubo C) é agora usado
            // como novo cubo A para intersectar com os seguintes cubos B
            Ax = Cx;
            Ay = Cy;
            Az = Cz;
        }

        // no fim, o cubo A é o resultado de todas as intersecções
        // calcular volume do cubo A
        int volume_A = 0;
        int dAx = Ax.second - Ax.first;
        int dAy = Ay.second - Ay.first;
        int dAz = Az.second - Az.first;

        volume_A = dAx * dAy * dAz;
        
        cout << volume_A << "\n";

        cin >> n_cubes;
    }


    return 0;
}