//https://www.geeksforgeeks.org/dsa/program-for-point-of-intersection-of-two-lines/

#include <bits/stdc++.h>

using namespace std;

#define pdd pair<double, double>

// calcular intersecção de duas rectas
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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    int cases;
    cin >> cases;

    // para cada caso
    for (int c = 0; c < cases; c++) {

        int n;
        cin >> n;

        // points é ordenado por x
        map<double,double> points;
        // heights é inversamente ordenado por y
        map<double,double,greater<double>> heights;
        for (int i = 0; i < n; i++) {
            double x, y;
            cin >> x >> y;

            points[x] = y;
            heights[y] = x;
        }

        auto highest_peak = heights.begin();

        while (next(highest_peak) != points.end()) {

        }

        double sum_sunny_slopes;


    }

    return 0;
}