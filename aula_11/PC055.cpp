// https://www.geeksforgeeks.org/cpp/point-in-polygon-in-cpp/
// https://www.geeksforgeeks.org/dsa/area-of-a-polygon-with-given-n-ordered-vertices/
//
// Para cada reino (polígono), calcular a sua área usando a fórmula do enunciado.
// Para cada ponto onde o míssil aterra, usar ray-casting para verificar se está dentro de um polígono.
// Temos de verificar todos os polígonos.

#include <bits/stdc++.h>
using namespace std;

struct Point {
    // Coordinates of the point
    double x, y;
};

// Function to check if a point is inside a polygon using
// the ray-casting algorithm
bool isPointInPolygon(const vector<Point>& polygon,
                      const Point& point)
{
    // Number of vertices in the polygon
    int n = polygon.size();
    // Count of intersections
    int count = 0;

    // Iterate through each edge of the polygon
    for (int i = 0; i < n; i++) {
        Point p1 = polygon[i];
        // Ensure the last point connects to the first point
        Point p2 = polygon[(i + 1) % n];

        // Check if the point's y-coordinate is within the
        // edge's y-range and if the point is to the left of
        // the edge
        if ((point.y > min(p1.y, p2.y))
            && (point.y <= max(p1.y, p2.y))
            && (point.x <= max(p1.x, p2.x))) {
            // Calculate the x-coordinate of the
            // intersection of the edge with a horizontal
            // line through the point
            double xIntersect = (point.y - p1.y)
                                    * (p2.x - p1.x)
                                    / (p2.y - p1.y)
                                + p1.x;
            // If the edge is vertical or the point's
            // x-coordinate is less than or equal to the
            // intersection x-coordinate, increment count
            if (p1.x == p2.x || point.x <= xIntersect) {
                count++;
            }
        }
    }
    // If the number of intersections is odd, the point is
    // inside the polygon
    return count % 2 == 1;
}

// calcular área de um polígono
double polygonArea(const vector<Point>& polygon) {
    double area = 0;

    int n = (int)polygon.size();
    int j = n - 1;

    for (int i = 0; i < n; i++) {
        area += (polygon[j].x + polygon[i].x) * (polygon[j].y - polygon[i].y);
        j = i;
    }

    return abs(area/2.0);
}


int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    int n_vertices;
    cin >> n_vertices;

    vector<pair<vector<Point>,double>> polygons_and_areas;

    // lêr os polígonos
    while (n_vertices > 0) {

        vector<Point> points;
        // receber os pontos
        for (int i = 0; i < n_vertices; i++) {
            double x, y;
            cin >> x >> y;

            Point p = {x, y};
            points.push_back(p);            
        }
        // calcular a área
        double p_area = polygonArea(points);
        // inserir pontos e área na lista
        polygons_and_areas.push_back({points, p_area});

        cin >> n_vertices;
    }

    // receber mísseis e calcular área acumulada para cada míssil
    double area = 0;
    int px, py;
    while (cin >> px >> py) {
        Point missile = {(double)px, (double)py};
        // verificar que polígono o míssil atingiu
        for (auto p : polygons_and_areas) {
            if (isPointInPolygon(p.first, missile)) {
                // se o míssil estiver dentro do polígono, somar área e sair do ciclo
                // (porque um míssil só pode cair dentro de um polígono)
                area += p.second;
                break;
            }
        }
    }

    cout.precision(2);
    cout << fixed << area << "\n";

    return 0;
}
