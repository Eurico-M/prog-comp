#include <bits/stdc++.h>
using namespace std;

#define INF INT_MAX/2

int nr_mazes;
int rows, cols;
vector<vector<int>> maze;
vector<vector<int>> dist;
vector<vector<bool>> visited;


void print_matrix(vector<vector<int>> &m) {
    for (auto x : m) {
        for (auto y : x) {
            cout << " " << y;
        }
        cout << "\n";
    }
    cout << "\n";
}

void print_bool_matrix(vector<vector<bool>> &m) {
    for (auto x : m) {
        for (auto y : x) {
            cout << " " << y;
        }
        cout << "\n";
    }
    cout << "\n";
}

list<pair<int,int>> neighbours = {
    {-1 ,0}, // up
    {1, 0},  // down
    {0, -1}, // left
    {0, 1}   // right
};

void dijkstra() {
    // Usar um set. O primeiro valor é a distância (fica ordenado pelo menor) e o segundo valor
    // é o nó (um par de coordenadas da matriz).
    set<pair<int,pair<int,int>>> q;
    dist[1][1] = maze[1][1];
    q.insert({dist[1][1], {1, 1}});

    while (!q.empty()) {
        auto v = q.begin()->second;
        int i = v.first;
        int j = v.second;
        q.erase(q.begin());
        visited[i][j] = true;

        for (auto n : neighbours) {
            int x = i + n.first;
            int y = j + n.second;

            if (!visited[x][y] && maze[x][y] != -1 && dist[i][j] + maze[x][y] < dist[x][y]) {
                dist[x][y] = dist[i][j] + maze[x][y];
                q.insert({dist[x][y], {x, y}});
            }
        }
    }
}

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    cin >> nr_mazes;

    for (int i = 0; i < nr_mazes; i++) {
        cin >> rows;
        cin >> cols;
        maze.clear();
        maze.assign(rows + 2, vector<int> (cols + 2, -1));
        dist.clear();
        dist.assign(rows + 2, vector<int> (cols + 2, -1));
        visited.clear();
        visited.assign(rows + 2, vector<bool> (cols + 2, false));

        for (int x = 1; x <= rows; x++) {
            for (int y = 1; y <= cols; y++) {
                cin >> maze[x][y];
                dist[x][y] = INF;
            }
        }
        // print_matrix(maze);
        // print_matrix(dist);
        dijkstra();
        // print_matrix(maze);
        // print_matrix(dist);
        cout << dist[rows][cols] << "\n";
    }



    return 0;
}