// Implementação de Trie retirada de https://www.geeksforgeeks.org/dsa/trie-delete/
// (acabei por não usar a função remove(), mas a estrutura veio de lá)
// Modificada para receber letras maiúsculas e guardar pontuação nos nós que são fins de strings.
//
// Receber o tabuleiro 4 x 4, guardar em board[][].
// Receber as palavras a procurar, e guardar numa Trie.
// Fazer um DFS em todas as casas do tabuleiro.
// No DFS, vamos acompanhar a 'descida' no board com uma 'descida' da Trie.
// Se nalgum ponto não conseguirmos acompanhar a Trie, sair do DFS.
// Por exemplo, no tabuleiro:
// FNEI
// OBCN
// EERI
// VSIR
// A palavra BEER começa na posição (1,1), e a Trie é root->B->E->E->R(isEndOfWord)
// O DFS a partir de (1,1) encontra a letra B, que também é encontrada a partir da raíz da Trie.
// Logo, podemos continuar a procurar, e agora tentamos encontrar um E (a próxima da letra da Trie).
// Ao visitar o vizinho da esquerda, verifica-se que O não pertence aos filhos de B na Trie,
// por isso podemos acabar o DFS aí.
// 

#include <bits/stdc++.h>
using namespace std;

const int ALPHABET_SIZE = 26;

int calc_score(int n) {
    switch (n) {
        case 3: return 1;
        case 4: return 1;
        case 5: return 2;
        case 6: return 3;
        case 7: return 5;
        default: return 11;
    }
}

struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
    int word_score;
    
    TrieNode() {
        isEndOfWord = false;
        word_score = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            children[i] = nullptr;
        }
    }
};

TrieNode* getNode() {
    return new TrieNode();
}

void insert(TrieNode* root, const string& key) {
    TrieNode* pCrawl = root;

    for (int i = 0; i < (int)key.length(); i++) {
        int index = key[i] - 'A';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    pCrawl->isEndOfWord = true;
    pCrawl->word_score = calc_score(key.length());
}

bool isEmpty(TrieNode* root) {
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}


vector<vector<char>> board(4, vector<char>(4));
vector<vector<bool>> visited(4, vector<bool>(4, false));
vector<pair<int,int>> neighbours = {
    {-1,-1},    //NW
    {-1, 0},    //N
    {-1, 1},    //NE
    { 0, 1},    //E
    { 1, 1},    //SE
    { 1, 0},    //S
    { 1,-1},    //SW
    { 0,-1}     //W
};

// dfs com backtracking
void dfs(int i, int j, TrieNode* curr, string& s, TrieNode* root, int& total_score) {
    // se estivermos fora dos limites ou já tiver sido visitado, fazer nada
    if (i < 0 || i >= 4 || j < 0 || j >= 4 || visited[i][j]) return;
    
    char c = board[i][j];
    int idx = c - 'A';
    // se a letra não estiver no caminho da trie, a palavra não existe, fazer nada
    if (curr->children[idx] == NULL) return;
    
    visited[i][j] = true;
    curr = curr->children[idx];
    s.push_back(c);
    // se encontramos uma palavra, pontuar e retirar essa palavra da trie (só pode aparecer uma vez)
    if (curr->isEndOfWord) {
        total_score += curr->word_score;
        curr->isEndOfWord = false;
    }
    // continuar o dfs nos vizinhos
    for (auto &n : neighbours) {
        int x = i + n.first;
        int y = j + n.second;
        if (x >= 0 && x < 4 && y >= 0 && y < 4) {
            dfs(x, y, curr, s, root, total_score);
        }
    }
    
    // backtrack
    visited[i][j] = false;
    s.pop_back();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n_cases;
    cin >> n_cases;

    for (int game = 1; game <= n_cases; game++) {

        // preencher board
        for (int i = 0; i < 4; i++) {
            string line;
            cin >> line;
            for (int j = 0; j < 4; j++) {
                board[i][j] = line[j];
            }
        }

        int n_words;
        cin >> n_words;

        // criar uma trie com as palavras
        TrieNode* root = new TrieNode();
        
        for (int i = 0; i < n_words; i++) {
            string word;
            cin >> word;
            insert(root, word);
        }
        
        int total_score = 0;
        string current_word;
        
        // dfs no board inteiro
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                // reset de visited
                for (auto &row : visited) {
                    fill(row.begin(), row.end(), false);
                }
                current_word.clear();
                dfs(i, j, root, current_word, root, total_score);
            }
        }
        
        cout << "Score for Boggle game #" << game << ": " << total_score << "\n";
    }

    return 0;
}