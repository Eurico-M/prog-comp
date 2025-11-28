#include <bits/stdc++.h>
#include <set>
using namespace std;

struct Node {
    vector<int> seq;
    list<char> plays;
};

list<char> transformations = {'A', 'B', 'C'};

string list_to_string(list<char> l) {
    string out = "";
    for (auto c : l) {
        out.append(1, c);
    }
    return out;
}

int seq_to_int(vector<int> &seq) {
    int n = 0;
    for (int i = 0; i < (int)seq.size(); i++) {
        n += seq[(int)seq.size()-1 - i] * (int)pow(10, i);
    }
    return n;
}

void trans_A(vector<int> &seq) {
    for (int i = 0; i < 4; i++) {
        int temp = seq[i];
        seq[i] = seq[(int)seq.size()-1 - i];
        seq[(int)seq.size()-1 - i] = temp;
    }
}

void trans_B(vector<int> &seq) {
    int final_top = seq[3];
    int final_bottom = seq[4];
    for (int i = 3; i > 0; i--) {
        seq[i] = seq[i-1];
    }
    for (int i = 4; i < (int)seq.size(); i++) {
        seq[i] = seq[i+1];
    }
    seq[0] = final_top;
    seq[7] = final_bottom;
}

void trans_C(vector<int> &seq) {
    int temp = seq[1];
    seq[1] = seq[6];
    seq[6] = seq[5];
    seq[5] = seq[2];
    seq[2] = temp;
}

vector<int> trans(char t, vector<int> seq) {
    switch (t) {
        case 'A':
            trans_A(seq);
            break;
        case 'B':
            trans_B(seq);
            break;
        case 'C':
            trans_C(seq);
            break;
    }
    return seq;
}

string bfs(Node &initial, vector<int> &target) {
    int target_int = seq_to_int(target);

    queue<Node> q;
    q.push(initial);
    set<int> visited;
    visited.insert(seq_to_int(initial.seq));

    while (!q.empty()) {
        Node v = q.front();
        q.pop();
        // cout << "NODE " << seq_to_int(v.seq) << ":\n";

        for (auto t : transformations) {
            Node w;
            w.seq = trans(t, v.seq);
            w.plays = v.plays;
            w.plays.push_back(t);
            // cout << "   TRANSFORM " << t << ": " << seq_to_int(w.seq) << "\n";
            // cout << "   play: " << list_to_string(w.plays) << "\n";
            if (seq_to_int(w.seq) == target_int) {
                return list_to_string(w.plays);
            }
            if (visited.count(seq_to_int(w.seq)) == 0) {
                q.push(w);
                // cout << "       enqueue\n";
            }
        }
    }
    return "erro no bfs";
}

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    // receber input
    vector<int> target;
    for (int i = 0; i < 8; i++) {
        int n;
        cin >> n;
        target.push_back(n);
    }

    Node initial;
    initial.seq = {1,2,3,4,5,6,7,8};
    initial.plays = {};
    // trans_A(initial.seq);
    // trans_B(initial.seq);
    // trans_C(initial.seq);
    // cout << seq_to_int(initial.seq) << "\n";

    string answer = bfs(initial, target);
    cout << answer.length() << "\n" << answer << "\n";

    return 0;
}
