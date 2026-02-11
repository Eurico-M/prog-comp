// a ideia é manter dois maps:
// points representa o gráfico, ordenado por x (por isso é que tem que ser um map).
// heights representa os maiores picos, por ordem descendente.
//
// enquanto pudermos andar no gráfico, da esquerda para a direita:
// (porque os raios de sol vêm da direita)
// 1) Pegar no maior pico (ponto A)
// 2) Pegar no ponto imediatamente a seguir (ponto B)
// AB é uma recta que contém a enconsta que pode apanhar raios solares
// 3) Pegar no segundo maior pico (ponto C)
// 4) Construir uma recta horizontal que passe por C (criar um ponto D
// que tenha coordenadas (-1, yC))
// A intersecção da recta CD com a recta AB é o ponto X, que representa
// o ponto inferior da encosta AB que recebe raios solares.
// 5) A distância AX representa a quantidade da encosta AB que apanha raios solares.
// 6) Repetir o processo, o segundo maior pico (ponto C) é agora o maior (novo ponto A)
//
// quando se itera pelo map heights à procura do segundo maior pico, 
// descartar os pontos que estejam à esquerda do maior pico (valores em heights que sejam
// menores que a coordenada x do maior pico)
//
// este método não precisa de nenhuma condição especial para a última encosta, o último
// ponto da última encosta AB é também o segundo maior pico C, e o algoritmo funciona na mesma.

#include <bits/stdc++.h>

using namespace std;

#define pdd pair<double, double>

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

// distância entre dois pontos
double distance(pdd A, pdd B) {
    return sqrt((A.first-B.first)*(A.first-B.first)+(A.second-B.second)*(A.second-B.second));
}

int main() {
    // Fast IO
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    //

    int cases;
    cin >> cases;

    // para cada caso
    for (int c = 0; c < cases; c++) {

        int n;
        cin >> n;

        // points é ordenado por x
        map<double,double> points;        
        for (int i = 0; i < n; i++) {
            double x, y;
            cin >> x >> y;

            points[x] = y;
        }

        // heights é inversamente ordenado por y.
        // ciclo separado: se houver 2 pontos com a mesma altura,
        // ficam ordenados por x de forma crescente.
        map<double,double,greater<double>> heights;
        for (auto p : points) {
            double x = p.first;
            double y = p.second;

            heights[y] = x;
        }

        // cout << "POINTS:\n";
        // for (auto z : points) {
        //     cout << "(" << z.first << "," << z.second << ")\n"; 
        // }

        // cout << "HEIGHTS:\n";
        // for (auto z : heights) {
        //     cout << z.first << " -> " << z.second << "\n";
        // }

        double sum_sunny_slopes = 0;

        auto k1 = points.begin();
        // retirar o maior pico de heights
        pdd highest_peak = *heights.begin();
        heights.erase(heights.begin());
        // não esquecer que heights é do tipo {y,x}
        swap(highest_peak.first, highest_peak.second);

        // cout << "maior pico: (" << highest_peak.first << "," << highest_peak.second << ")\n";

        // encontrar o maior pico em points
        while (k1->first != highest_peak.first) {
            k1 = next(k1);
        }

        // cout << "confirmar maior pico em points: (";
        // cout << k1->first << "," << k1->second << ")\n";
 
        // percorrer os pontos da esquerda para a direita
        while (next(k1) != points.end()) {            

            // a encosta do maior pico é a recta AB
            pdd A = *k1;
            pdd B = *next(k1);

            // cout << "A (" << A.first << "," << A.second << ")\n";
            // cout << "B (" << B.first << "," << B.second << ")\n";
            // o segundo maior pico bloqueia os raios de sol
            pdd second_highest_peak = *heights.begin();

            // cout << "___________ PROBLEMA AQUI\n";
            // cout << "antes do while. second_highest_peak = ";
            // cout << second_highest_peak.first << ", " << second_highest_peak.second << "\n";
            // fazer pop dos pontos que já ultrapassámos (em x)
            while (second_highest_peak.second < k1->first) {
                // cout << "while passou. ";
                // cout << second_highest_peak.second << " < " << highest_peak.first << "\n";
                heights.erase(heights.begin());
                // cout << "novo heights:\n";
                // for (auto z : heights) {
                //     cout << z.first << " -> " << z.second << "\n";
                // }
                second_highest_peak = *heights.begin();
                // cout << "novo second highest: " << second_highest_peak.first << " , " << second_highest_peak.second << "\n";
            }
            heights.erase(heights.begin());
            swap(second_highest_peak.first, second_highest_peak.second);
            // cout << "FIM DO CICLO WHILE\n";
            // cout << "segundo maior pico: (";
            // cout << second_highest_peak.first << "," << second_highest_peak.second << ")\n";

            // cout << "POINTS:\n";
            // for (auto z : points) {
            //     cout << "(" << z.first << "," << z.second << ")\n"; 
            // }

            // cout << "HEIGHTS:\n";
            // for (auto z : heights) {
            //     cout << z.first << " -> " << z.second << "\n";
            // }
            // simular o raio de sol "limite", i.e., a linha horizontal
            // que passa no segundo maior pico, como uma recta CD
            // onde C é o segundo maior pico
            pdd C = second_highest_peak;
            // e D é um valor com a mesma altura mas x = -1 (por exemplo)
            pdd D = {-1, second_highest_peak.second};

            // a intersecção do "último raio de sol" com a encosta do maior pico
            // dá-nos o ponto da encosta onde o lado da montanha ensolarado acaba
            pdd X = lineLineIntersection(A, B, C, D);

            // a distância "ensolarada" é a distância entre A e X
            double sunny_slope = distance(A, X);
            // fazer update da variável "global"
            sum_sunny_slopes += sunny_slope;

            // cout << "encosta com sol: " << sunny_slope << "\n";
            // cout << "cumulativa: " << sum_sunny_slopes << "\n";

            // fazer andar o ponteiro em points para o segundo maior pico
            // (que agora passa a ser o maior pico)
            while (k1->first != second_highest_peak.first) {
                k1 = next(k1);
            }

            // cout << "---- k1 passa a ser: (" << k1->first << "," << k1->second << ")\n";

        }

        cout.precision(2);
        cout << fixed << sum_sunny_slopes << "\n";

    }

    return 0;
}