//
// Usar um grafo. Os nós são os estados do jogo (sequência de números).
// Gerar os nós à medida que se faz um BFS a partir do nó raíz (estado inicial do jogo).
// Os vizinhos de cada nó são as 3 transformações que se podem fazer (o grafo é uma árvore ternária).
// Ao marcar os nós visitados, estamos a optimizar o tempo com um bocadinho de
// programação dinâmica inerente ao BFS: se uma configuração do jogo já foi visitada, quer dizer
// que é possível chegar a essa configuração num número menor de jogadas/transformações.
//
// Para fazer o output, ir guardando nos nós as jogadas feitas para chegar a esse nó.

#include <bits/stdc++.h>
#include <set>
using namespace std;

// nó do grafo: sequência de números e jogadas necessárias para chegar a essa sequência
struct Node {
    vector<int> seq;
    list<char> plays;
};
// as 3 jogadas possíveis
list<char> transformations = {'A', 'B', 'C'};
// fazer print de uma lista (indirectamente)
string list_to_string(list<char> l) {
    string out = "";
    for (auto c : l) {
        out.append(1, c);
    }
    return out;
}
// tranformar um vector de números num único número (int)
// fica mais fácil manipular
int seq_to_int(vector<int> &seq) {
    int n = 0;
    for (int i = 0; i < (int)seq.size(); i++) {
        n += seq[(int)seq.size()-1 - i] * (int)pow(10, i);
    }
    return n;
}
// as 3 transformações possíveis:
// A: trocar fila de cima com a fila de baixo
void trans_A(vector<int> &seq) {
    for (int i = 0; i < 4; i++) {
        int temp = seq[i];
        seq[i] = seq[(int)seq.size()-1 - i];
        seq[(int)seq.size()-1 - i] = temp;
    }
}
// B: deslizar colunas para a direita, a última dá a volta
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
// C: rodar o quadrado central na direção horária
void trans_C(vector<int> &seq) {
    int temp = seq[1];
    seq[1] = seq[6];
    seq[6] = seq[5];
    seq[5] = seq[2];
    seq[2] = temp;
}
// selecionar qual das transformações apllicar com base na letra
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
    // converter a configuração alvo num int para comparação
    int target_int = seq_to_int(target);
    // inicializar queue BFS e conjunto de visitados (com ints -> mais simples)
    queue<Node> q;
    q.push(initial);
    set<int> visited;
    visited.insert(seq_to_int(initial.seq));

    while (!q.empty()) {
        // para cada nó da queue
        Node v = q.front();
        q.pop();
        // cout << "NODE " << seq_to_int(v.seq) << ":\n";
        //
        // visitar vizinhos (transformar com A, B, C)
        for (auto t : transformations) {
            Node w;
            w.seq = trans(t, v.seq);
            // as jogadas em cada nó são as jogadas do nó pai acrescidas da jogada que acabou de ser feita
            w.plays = v.plays;
            w.plays.push_back(t);
            // cout << "   TRANSFORM " << t << ": " << seq_to_int(w.seq) << "\n";
            // cout << "   play: " << list_to_string(w.plays) << "\n";
            //
            // quando chegámos à configuração alvo, sair do BFS e retornar a lista de jogadas
            if (seq_to_int(w.seq) == target_int) {
                return list_to_string(w.plays);
            }
            // se ainda não tivermos visto esta configuração, colocá-la na queue e marcar como visitada.
            if (visited.count(seq_to_int(w.seq)) == 0) {
                q.push(w);
                visited.insert(seq_to_int(w.seq));
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
    // criar nó raíz do grafo
    Node initial;
    initial.seq = {1,2,3,4,5,6,7,8};
    initial.plays = {};
    // trans_A(initial.seq);
    // trans_B(initial.seq);
    // trans_C(initial.seq);
    // cout << seq_to_int(initial.seq) << "\n";

    // BFS a partir da posição inicial, com o objectivo de chegar a uma configuração alvo
    string answer = bfs(initial, target);
    cout << answer.length() << "\n" << answer << "\n";

    return 0;
}
