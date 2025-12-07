#include <bits/stdc++.h>
using namespace std;

#define MAX_SPEED 240

list<int> increments;
vector<int> track;
vector<vector<int>> dp;
int finish_line;

void print_dp() {
    cout << "DP:\n";
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
    cout << "\n";
}

void print_increments() {
    cout << "Increments:";
    for (auto x : increments) {
        cout << " " << x;
    }
    cout << "\n\n";
}

void print_track() {
    cout << "Track:\n";
    for (int i = 0; i < (int)track.size(); i++) {
        cout << i;
        if (i < 10) {
            cout << "  ";
        }
        else {
            cout << " ";
        }
        cout << track[i] << "\n";
    }
    cout << "\n";
}

void init_increments(int acc, int brk) {
    increments.clear();
    for (int i = -brk; i <= acc; i += 10) {
        increments.push_back(i);
    }
}

void init_track() {
    track.clear();
    track.push_back({MAX_SPEED});
}

void buffer_track() {
    for (int i = 0; i <= MAX_SPEED/10; i++) {
        track.push_back(MAX_SPEED);
    }
}

void init_dp() {
    dp.clear();
    dp.assign((int)track.size(), vector<int>(MAX_SPEED/10 + 1, -1));
}

pair<int,int> new_move(int inc, int pos, int spd) {
    int new_speed = spd + inc;
    int new_pos = new_speed/10 + pos;
    return {new_pos, new_speed};
}

bool valid(int start_pos, int new_pos, int spd) {
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

int solve(int pos, int spd) {
    cout << "pos=" << pos << " spd=" << spd << "\n";
    if (pos >= finish_line) {
        return dp[pos][spd/10] = 0;
    }

    if (dp[pos][spd/10] != -1) {
        return dp[pos][spd/10];
    }

    int min_moves = finish_line;

    for (int i : increments) {
        pair<int,int> move = new_move(i, pos, spd);
        int new_pos = move.first;
        int new_speed = move.second;
        cout << "inc=" << i << " new pos=" << new_pos << " new spd=" << new_speed << "\n";
        if (valid(pos, new_pos, new_speed)) {
            cout << "valid\n";
            min_moves = min(min_moves, solve(new_pos, new_speed));
        }
    }

    return dp[pos][spd/10] = 1 + min_moves;
}


int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    int n_tests;
    cin >> n_tests;

    for (int i = 0; i < n_tests; i++) {
        int acc, brk;
        cin >> acc >> brk;

        init_increments(acc, brk);
        init_track();

        int n, v;
        cin >> n >> v;
        while (n != 0) {
            for (int k = 0; k < n; k++) {
                track.push_back(v);
            }
            cin >> n >> v;
        }
        finish_line = track.size();
        buffer_track();

        init_dp();

        cout << solve(0,0) << "\n";

        print_track();
        cout << "finish line: " << finish_line << "\n";
        print_increments();
        print_dp();

    }

    return 0;
}
