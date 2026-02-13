// Para cada flight path, calcular a intersecção da recta AB (flight path) com as rectas CD
// (os lados do polígono que estão no caminho do flight path)
// Estar no caminho do flight path é ter as coordenadas dos vértices em lados diferentes da
// recta AB (ou seja, se Cx < Ax && Dx > Ax || Cx > Ax && Dx < Ax).
// Os pontos de intersecção X são guardados num vector (só as coordenadas y interessam).
// Fazer sort deste vector, e calcular a distância acumulada entre pares de pontos.

#include <bits/stdc++.h>
using namespace std;

#define pdd pair<double,double>

// calcular intersecção de duas rectas
// https://www.geeksforgeeks.org/dsa/program-for-point-of-intersection-of-two-lines/
pdd lineLineIntersection(pdd A, pdd B, pdd C, pdd D)
{
    // Line AB represented as a1x + b1y = c1
    double a1 = B.second - A.second;
    double b1 = A.first - B.first;
    double c1 = a1*(A.first) + b1*(A.second);

    // Line CD represented as a2x + b2y = c2
    double a2 = D.second - C.second;
    double b2 = C.first - D.first;
    double c2 = a2*(C.first)+ b2*(C.second);

    double determinant = a1*b2 - a2*b1;

    if (determinant == 0)
    {
        // The lines are parallel. This is simplified
        // by returning a pair of FLT_MAX
        return make_pair(FLT_MAX, FLT_MAX);
    }
    else
    {
        double x = (b2*c1 - b1*c2)/determinant;
        double y = (a1*c2 - a2*c1)/determinant;
        return make_pair(x, y);
    }
}


int main() {
    // Fast IO
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    //

    int n_cases;
    cin >> n_cases;

    for (int n1 = 0; n1 < n_cases; n1++) {

        int n_vertices;
        cin >> n_vertices;

        vector<pdd> polygon;

        // receber vertices e manter a ordem
        for (int j = 0; j < n_vertices; j++) {
            double x, y;
            cin >> x >> y;

            polygon.push_back({x, y});
        }

        double threshold;
        cin >> threshold;

        int x_line;
        cin >> x_line;

        // cout << "x_line = " << x_line << "\n";

        // criar recta de flight path AB
        pdd A = {x_line, -1};
        pdd B = {x_line, FLT_MAX};

        // calcular a intersecção de AB com os lados do polígono atravessados por AB
        vector<double> y_flight;

        for (int k = 0; k < n_vertices; k++) {
            // para "dar a volta" ao vector: quando k = 6 então l = 0
            int l = (k+1)%n_vertices;
            // cout << "K=" << k << " L=" << l << "\n";
            // construir a recta CD que representa o lado do polígono,
            // se estiver no caminho do flight path
            // cout << "polygon[k] = " << polygon[k].first << "," << polygon[k].second << "\n";
            // cout << "polygon[l] = " << polygon[l].first << "," << polygon[l].second << "\n";
            if (polygon[k].first < (double)x_line && polygon[l].first > (double)x_line
                || polygon[k].first > (double)x_line && polygon[l].first < (double)x_line) {
                pdd C = polygon[k];
                pdd D = polygon[l];

                // ponto X é a intersecção do flight path AB com o lado do polígono CD
                pdd X = lineLineIntersection(A, B, C, D);

                // cout << "X = " << X.first << "," << X.second << "\n";

                // colocar a coordenada y do ponto X num vector (coordenada x é irrelevante)
                y_flight.push_back(X.second);
            }
        }

        // ordenar y_flight
        sort(y_flight.begin(), y_flight.end());

        // como o pássaro começa fora do polígono, vai atravessar um número par de lados
        // se os elementos de y_flight são yi, podemos calcular a distância que o pássaro sobrevoa
        // o polígono fazendo yi+1 - yi, para i % 2 == 0
        double distance = 0;
        // cout << "y_flight size = " << y_flight.size() << "\n";
        for (int i = 0; i < (int)y_flight.size(); i++) {
            if (i % 2 == 0) {
                distance += y_flight[i+1] - y_flight[i];
            }
        }

        // formatar output
        if (distance > threshold) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }

    }


    return 0;
}