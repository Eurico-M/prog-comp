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

void init_maze_dist(int a) {
    for (int x = 1; x <= rows; x++) {
        for (int y = 1; y <= cols; y++) {
            cin >> maze[x][y];
        }
    }
}

void init_dist(int a) {
    for (int x = 1; x <= rows; x++) {
        for (int y = 1; y <= cols; y++) {
            dist[x][y] = a;
        }
    }
}

void init_visited() {
    visited.clear();
    visited.assign(rows + 2, vector<bool> (cols + 2, false));
}

void min_sum_dijkstra() {
    // Usar um set. O primeiro valor é a distância (fica ordenado pelo menor) e o segundo valor
    // é o nó (um par de coordenadas da matriz).
    set<pair<int,pair<int,int>>> q;
    dist[rows][1] = maze[rows][1];
    q.insert({dist[rows][1], {rows, 1}});

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

int best_end_square() {
    int best = 0;
    for (int i = 1; i <= rows; i++) {
        if (dist[i][cols] > best) {
            best = dist[i][cols];
        }
    }
    return best;
}

void max_min_dijkstra(int a, int b) {
    // Usar um set. O primeiro valor é a distância (fica ordenado pelo menor) e o segundo valor
    // é o nó (um par de coordenadas da matriz).
    set<pair<int,pair<int,int>>> q;
    dist[a][b] = maze[a][b];
    q.insert({dist[a][b], {a, b}});

    while (!q.empty()) {
        auto v = q.begin()->second;
        int i = v.first;
        int j = v.second;
        q.erase(q.begin());
        visited[i][j] = true;

        for (auto n : neighbours) {
            int x = i + n.first;
            int y = j + n.second;

            if (!visited[x][y] && maze[x][y] != -1 && min(dist[i][j], maze[x][y]) > dist[x][y]) {
                dist[x][y] = min(dist[i][j], maze[x][y]);
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

    int flag;
    cin >> flag;

    cin >> nr_mazes;

    for (int i = 0; i < nr_mazes; i++) {
        cin >> rows;
        cin >> cols;
        maze.clear();
        maze.assign(rows + 2, vector<int> (cols + 2, -1));
        dist.clear();
        dist.assign(rows + 2, vector<int> (cols + 2, -1));
        

        for (int x = 1; x <= rows; x++) {
            for (int y = 1; y <= cols; y++) {
                cin >> maze[x][y];
            }
        }

        // print_matrix(maze);
        // print_matrix(dist);
        if (flag == 1) {
            init_visited();
            init_dist(INF);
            min_sum_dijkstra();
            cout << dist[1][cols] << "\n";
        }
        // print_matrix(maze);
        // print_matrix(dist);

        if (flag == 2) {
            int best = 0;
            for (int i = 1; i <= rows; i++) {
                init_visited();
                init_dist(0);
                max_min_dijkstra(i, 1);
                best = max(best, best_end_square());
            }
            cout << best << "\n";
        }

    }



    return 0;
}
