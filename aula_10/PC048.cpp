#include <bits/stdc++.h>
using namespace std;

class TrieNode
{
  public:
    // Array for children nodes of each node
    TrieNode *children[26];

    // for end of word
    bool isLeaf;

    TrieNode()
    {
        isLeaf = false;
        for (int i = 0; i < 26; i++)
        {
            children[i] = nullptr;
        }
    }

};
  // Method to insert a key into the Trie
void insert(TrieNode *root, const string &key)
{

    // Initialize the curr pointer with the root node
    TrieNode *curr = root;

    // Iterate across the length of the string
    for (char c : key)
    {

        // Check if the node exists for the
        // current character in the Trie
        if (curr->children[c - 'A'] == nullptr)
        {

            // If node for current character does
            // not exist then make a new node
            TrieNode *newNode = new TrieNode();

            // Keep the reference for the newly
            // created node
            curr->children[c - 'A'] = newNode;
        }

        // Move the curr pointer to the
        // newly created node
        curr = curr->children[c - 'A'];
    }

    // Mark the end of the word
    curr->isLeaf = true;
}

// Method to search a key in the Trie
bool search(TrieNode *root, const string &key)
{

    if (root == nullptr)
    {
        return false;
    }

    // Initialize the curr pointer with the root node
    TrieNode *curr = root;

    // Iterate across the length of the string
    for (char c : key)
    {

        // Check if the node exists for the
        // current character in the Trie
        if (curr->children[c - 'A'] == nullptr)
            return false;

        // Move the curr pointer to the
        // already existing node for the
        // current character
        curr = curr->children[c - 'A'];
    }

    // Return true if the word exists
    // and is marked as ending
    return curr->isLeaf;
}


vector<vector<char>> board (6, vector<char> (6, '.'));

void reset_board() {
    for (auto &x : board) {
        for (auto &y : x) {
            y = '.';
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
        

    }

    return 0;
}