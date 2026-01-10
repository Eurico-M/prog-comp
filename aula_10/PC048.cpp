#include <bits/stdc++.h>
using namespace std;

const int ALPHABET_SIZE = 26;

int calc_score(int n) {
    switch (n) {
        case 3:
            return 1;
        case 4:
            return 1;
        case 5:
            return 2;
        case 6:
            return 3;
        case 7:
            return 5;
        default:
            return 11;
    }
}


// trie node
struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];

    bool isEndOfWord;
    int word_score;
};

// Returns new trie node (initialized to NULLs)
struct TrieNode* getNode(void)
{
    struct TrieNode* pNode = new TrieNode;

    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        pNode->children[i] = NULL;
        pNode->word_score = 0;
    }

    return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(struct TrieNode* root, string key)
{
    struct TrieNode* pCrawl = root;

    for (int i = 0; i < (int)key.length(); i++) {
        int index = key[i] - 'A';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf
    pCrawl->isEndOfWord = true;
    pCrawl->word_score = calc_score(key.length());
}

// Returns true if key present in trie, else false
bool search(struct TrieNode* root, string key)
{
    struct TrieNode* pCrawl = root;

    for (int i = 0; i < (int)key.length(); i++) {
        int index = key[i] - 'A';
        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }

    return (pCrawl != NULL && pCrawl->isEndOfWord);
}

// Returns true if root has no children, else false
bool isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

// Recursive function to delete a key from given Trie
TrieNode* remove(TrieNode* root, string key, int depth = 0)
{
    // If tree is empty
    if (!root)
        return NULL;

    // If last character of key is being processed
    if (depth == (int)key.size()) {

        // This node is no more end of word after
        // removal of given key
        if (root->isEndOfWord)
            root->isEndOfWord = false;

        // If given is not prefix of any other word
        if (isEmpty(root)) {
            delete (root);
            root = NULL;
        }

        return root;
    }

    // If not last character, recur for the child
    // obtained using ASCII value
    int index = key[depth] - 'A';
    root->children[index] = 
          remove(root->children[index], key, depth + 1);

    // If root does not have any child (its only child got 
    // deleted), and it is not end of another word.
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = NULL;
    }

    return root;
}


vector<vector<char>> board (6, vector<char> (6, '.'));
vector<vector<bool>> visited (6, vector<bool> (6, false));
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

void reset_board() {
    for (auto &x : board) {
        for (auto &y : x) {
            y = '.';
        }
    }
}

void reset_visited() {
    for (auto &x : visited) {
        for (auto y : x) {
            y = false;
        }
    }
}

void print_board() {
    cout << "-- Board --\n";
    for (auto x : board) {
        for (auto y : x) {
            cout << y;
        }
        cout << "\n";
    }
}

int dfs(int i, int j, TrieNode* trie_n, string s, TrieNode* root) {
    
    visited[i][j] = true;
    int c = board[i][j] - 'A';
    TrieNode* curr = trie_n;
    
    if (curr->children[c] == NULL) {
        return 0;
    }
    
    curr = curr->children[c];
    s.push_back(c + 'A');
    
    if (curr->isEndOfWord) {
        int score = curr->word_score;
        remove(root, s);
        return score;
    }
    
    for (auto n : neighbours) {
        int x = n.first;
        int y = n.second;
        
        if (board[i+x][j+y] != '.' && !visited[i+x][j+y]) {
            return dfs(i + x, j + y, curr, s, root);
        }
    }

    return 0;
}

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    int n_cases;
    cin >> n_cases;

    for (int i = 0; i < n_cases; i++) {
        reset_board();

        for (int j = 0; j < 4; j++) {
            string line;
            cin >> line;

            for (int k = 0; k < 4; k++) {
                board[j+1][k+1] = line[k];
            }
        }

        // print_board();

        int n_words;
        cin >> n_words;

        TrieNode* root = new TrieNode();

        for (int j = 0; j < n_words; j++) {
            string word;
            insert(root, word);
        }
        
        cout << dfs(1, 1, root, "", root) << "\n";

    }

    return 0;
}