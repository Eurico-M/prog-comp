#include <bits/stdc++.h>
using namespace std;

#define MAX_SPEED 240

void print_dp(const vector<vector<int>> &dp) {
    cout << "dp:\n";
    for (int i = 0; i < MAX_SPEED/10 + 1; i++) {
        if (i*10 >= 100) {
            cout << " " << i*10;
        }
        else if (i*10 >= 10) {
            cout << "  " << i*10;
        }
        else {
            cout << "     " << i*10;
        }
    }
    cout << "\n";
    int c = 0;
    for (auto x : dp) {
        if (c < 10) {
            cout << "0" << c++;
        }
        else {
            cout << c++;
        }
        for (auto y : x) {
            if (y < 0) {
                cout << "  " << y;
            }
            else {
                cout << "   " << y;
            }
        }
        cout << "\n";
    }
}

void print_list(const list<int> &l) {
    cout << "increment list:";
    for (auto x : l) {
        cout << " " << x;
    }
    cout << "\n";
}

void print_track(const vector<int> &t) {
    for (int i = 0; i < (int)t.size(); i++) {
        cout << i;
        if (i < 10) {
            cout << "  ";
        }
        else {
            cout << " ";
        }
        cout << t[i] << "\n";
    }
    cout << "\n";
}

list<int> create_increment_list(int acc, int brk) {
    list<int> res;
    for (int i = -brk; i <= acc; i += 10) {
        res.push_front(i);
    }
    return res;
}

pair<int,int> new_move(int inc, int pos, int spd) {
    int new_speed = spd + inc;
    int new_pos = new_speed/10 + pos;
    return {new_pos, new_speed};
}

bool valid(const vector<int> &track, int start_pos, int new_pos, int spd) {
    if (new_pos <= 0 || spd <= 0) {
        return false;
    }
    for (int i = start_pos; i <= new_pos; i++) {
        if (spd > track[i]) {
            return false;
        }
    }
    return true;
}

void bfs(vector<vector<int>> &dp, const list<int> incrs, const vector<int> &track, const int finish_line) {
    // iniciar fila de BFS com o nó inicial (0,0)
    queue<pair<int,int>> q;
    q.push({0,0});
    // marcar como visitado
    dp[0][0] = 0;
    // enquanto houver nós não visitados
    while (!q.empty()) {
        // retirar primeiro elemento da queue
        auto v = q.front();
        q.pop();
        int pos = v.first;
        int spd = v.second;
        cout << "pos=" << pos << " spd=" << spd << "\n";
        // os vizinhos são os nós resultantes de fazer os incrementos de velocidade
        for (auto inc : incrs) {
            // calcular a posição e velocidade resultantes de fazer o incremento
            auto w = new_move(inc, pos, spd);
            int new_pos = w.first;
            int new_speed = w.second;
            cout << "inc=" << inc << " new_pos=" << new_pos << " new_speed=" << new_speed << "\n";
            // se a nova posição e velocidade forem válidos e não tiverem sido visitados
            if (valid(track, pos, new_pos, new_speed) && dp[new_pos][new_speed/10] == -1) {
                // inserir nó na queue, se ainda estivermos dentro da pista
                if (new_pos < finish_line) {
                    q.push({new_pos, new_speed});
                }
                // marcar o número de jogadas mínimas para chegar a esse nó (anterior + 1)
                dp[new_pos][new_speed/10] = dp[pos][spd/10] + 1;
                cout << "valid, " << dp[new_pos][new_speed/10] << " moves\n";
            }
        }

    }
}

int min_moves(const vector<vector<int>> &dp, const int finish_line) {
    int min_move = finish_line;
    for (auto x : dp[finish_line]) {
        if (x > -1) {
            min_move = min(min_move, x);
        }
    }
    return min_move;
}

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    int n_tests;
    cin >> n_tests;

    for (int i = 0; i < n_tests; i++) {
        // cout << "TEST #" << i+1 << "\n";
        int acc, brk;
        cin >> acc >> brk;

        list<int> inc = create_increment_list(acc, brk);

        vector<int> track = {MAX_SPEED};
        int n, v;
        cin >> n >> v;
        while (n != 0) {
            for (int k = 0; k < n; k++) {
                track.push_back(v);
            }
            cin >> n >> v;
        }
        int finish_line = (int)track.size();
        for (int k = 0; k <= MAX_SPEED/10; k++) {
            track.push_back(MAX_SPEED);
        }
        print_list(inc);
        print_track(track);
        cout << "finish line: " << finish_line << "\n";
        vector<vector<int>> dp ((int)track.size(), vector<int> (MAX_SPEED/10 + 1, -1));
        // print_dp(dp);
        bfs(dp, inc, track, finish_line);
        print_dp(dp);
        cout << min_moves(dp, finish_line) << "\n";
    }

    return 0;
}
