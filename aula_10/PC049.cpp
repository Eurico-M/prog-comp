

// C++ program for building LCP array for given text
#include <bits/stdc++.h>
using namespace std;

// Structure to store information of a suffix
struct suffix
{
    int index;  // To store original index
    int rank[2]; // To store ranks and next rank pair
};

// A comparison function used by sort() to compare two suffixes
// Compares two pairs, returns 1 if first pair is smaller
int cmp(struct suffix a, struct suffix b)
{
    return (a.rank[0] == b.rank[0])? (a.rank[1] < b.rank[1] ?1: 0):
           (a.rank[0] < b.rank[0] ?1: 0);
}

// This is the main function that takes a string 'txt' of size n as an
// argument, builds and return the suffix array for the given string
vector<int> buildSuffixArray(string txt, int n)
{
    // A structure to store suffixes and their indexes
    struct suffix suffixes[n];

    // Store suffixes and their indexes in an array of structures.
    // The structure is needed to sort the suffixes alphabetically
    // and maintain their old indexes while sorting
    for (int i = 0; i < n; i++)
    {
        suffixes[i].index = i;
        suffixes[i].rank[0] = txt[i] - 'a';
        suffixes[i].rank[1] = ((i+1) < n)? (txt[i + 1] - 'a'): -1;
    }

    // Sort the suffixes using the comparison function
    // defined above.
    sort(suffixes, suffixes+n, cmp);

    // At his point, all suffixes are sorted according to first
    // 2 characters.  Let us sort suffixes according to first 4
    // characters, then first 8 and so on
    int ind[n];  // This array is needed to get the index in suffixes[]
    // from original index.  This mapping is needed to get
    // next suffix.
    for (int k = 4; k < 2*n; k = k*2)
    {
        // Assigning rank and index values to first suffix
        int rank = 0;
        int prev_rank = suffixes[0].rank[0];
        suffixes[0].rank[0] = rank;
        ind[suffixes[0].index] = 0;

        // Assigning rank to suffixes
        for (int i = 1; i < n; i++)
        {
            // If first rank and next ranks are same as that of previous
            // suffix in array, assign the same new rank to this suffix
            if (suffixes[i].rank[0] == prev_rank &&
                    suffixes[i].rank[1] == suffixes[i-1].rank[1])
            {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = rank;
            }
            else // Otherwise increment rank and assign
            {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = ++rank;
            }
            ind[suffixes[i].index] = i;
        }

        // Assign next rank to every suffix
        for (int i = 0; i < n; i++)
        {
            int nextindex = suffixes[i].index + k/2;
            suffixes[i].rank[1] = (nextindex < n)?
                                  suffixes[ind[nextindex]].rank[0]: -1;
        }

        // Sort the suffixes according to first k characters
        sort(suffixes, suffixes+n, cmp);
    }

    // Store indexes of all sorted suffixes in the suffix array
    vector<int>suffixArr;
    for (int i = 0; i < n; i++)
        suffixArr.push_back(suffixes[i].index);

    // Return the suffix array
    return  suffixArr;
}

/* To construct and return LCP */
vector<int> kasai(string txt, vector<int> suffixArr)
{
    int n = suffixArr.size();

    // To store LCP array
    vector<int> lcp(n, 0);

    // An auxiliary array to store inverse of suffix array
    // elements. For example if suffixArr[0] is 5, the
    // invSuff[5] would store 0.  This is used to get next
    // suffix string from suffix array.
    vector<int> invSuff(n, 0);

    // Fill values in invSuff[]
    for (int i=0; i < n; i++)
        invSuff[suffixArr[i]] = i;

    // Initialize length of previous LCP
    int k = 0;

    // Process all suffixes one by one starting from
    // first suffix in txt[]
    for (int i=0; i<n; i++)
    {
        /* If the current suffix is at n-1, then we don’t
           have next substring to consider. So lcp is not
           defined for this substring, we put zero. */
        if (invSuff[i] == n-1)
        {
            k = 0;
            continue;
        }

        /* j contains index of the next substring to
           be considered  to compare with the present
           substring, i.e., next string in suffix array */
        int j = suffixArr[invSuff[i]+1];

        // Directly start matching from k'th index as
        // at-least k-1 characters will match
        while (i+k<n && j+k<n && txt[i+k]==txt[j+k])
            k++;

        lcp[invSuff[i]] = k; // lcp for the present suffix.

        // Deleting the starting character from the string.
        if (k>0)
            k--;
    }

    // return the constructed lcp array
    return lcp;
}

// Utility function to print an array
void printArr(vector<int>arr, int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}


// Driver program to test above functions
int main()
{

    // casos de teste diferentes
    int n_lifeforms;
    cin >> n_lifeforms;

    int newline_counter = 0;

    while (n_lifeforms > 0) {
        // cout << "--- CASE ---\n";
        if (newline_counter > 0) {
            cout << "\n";
        }
        newline_counter++;
        
        string concat = "";
        vector<int> stringID;

        // receber as strings e ir concatenando numa única string
        for (int i = 0; i < n_lifeforms; i++) {
            string lifeform;
            cin >> lifeform;
            // preencher stringID para saber a que posições da string concat correspondem cada palavra
            for (int j = 0; j < (int)lifeform.length(); j++) {
                stringID.push_back(i);
            }
            // acrescentar separador único de strings
            char separator = 128 + i;
            lifeform.push_back(separator);
            // marcar separador como -1 porque não faz parte das palavras
            stringID.push_back(-1);

            concat.append(lifeform);
        }

        int n = concat.length();
        vector<int> suffixArr = buildSuffixArray(concat, n);

        cout << "Following is suffix array for: " << concat << "\n";
        printArr(suffixArr, n);

        vector<int>lcp = kasai(concat, suffixArr);

        cout << "LCP Array:\n";
        printArr(lcp, n);

        cout << "String ID:\n";
        printArr(stringID, (int)stringID.size());
        
        int more_than_half = n_lifeforms/2 + 1;
        cout << "more than half = " << more_than_half << "\n";


        map<string,set<int>> all_prefix_strings;
        // string prev = "";

        // for (int k = 0; k < n; k++) {
        //     if (lcp[k] > 0) {
        //         string p = concat.substr(suffixArr[k], lcp[k]);
        //         cout << "encontrei sufixo: " << p << "\n";
        //         int id1 = stringID[suffixArr[k]];
        //         int id2 = stringID[suffixArr[k+1]];

        //         if (p != prev) {
        //             all_prefix_strings.insert({p,{id1, id2}});
        //         }
        //         else {
        //             set<int> temp_set = all_prefix_strings[p];
        //             temp_set.insert(id1);
        //             temp_set.insert(id2);
        //             all_prefix_strings[p] = temp_set;
        //         }

        //         prev = p;
        //     }
        // }

        int k = 0;

        while (k < n) {

            if (lcp[k] == 0) {
                k++;
                continue;
            }
            
            // Start of a group with common prefix
            int group_start = k;
            int min_lcp_in_group = lcp[k];
            
            // First, collect all string IDs in this group
            set<int> strings_in_group;
            
            // Add the first string (at position group_start)
            if (stringID[suffixArr[k]] != -1) {
                strings_in_group.insert(stringID[suffixArr[k]]);
            }
            
            // Expand the group while LCP > 0
            while (k < n && lcp[k] > 0) {
                // Update minimum LCP in this group
                if (lcp[k] < min_lcp_in_group) {
                    min_lcp_in_group = lcp[k];
                }
                
                // Add the current string (at position k+1)
                if (stringID[suffixArr[k+1]] != -1) {
                    strings_in_group.insert(stringID[suffixArr[k+1]]);
                }
                
                k++;
            }
            
            // Now we have a complete group from group_start to k
            // Add all prefixes of lengths from min_lcp_in_group down to 1
            
            if (min_lcp_in_group > 0 && !strings_in_group.empty()) {
                // Get the starting position of the first suffix in the group
                int start_pos = suffixArr[group_start];
                
                // Extract the common prefix
                string common_prefix = concat.substr(start_pos, min_lcp_in_group);
                
                // // Remove any separators from the prefix
                // common_prefix.erase(remove_if(common_prefix.begin(), common_prefix.end(), 
                //     [](char c) { return c >= 128; }), common_prefix.end());
                
                if (!common_prefix.empty()) {
                    // Check if this prefix already exists in our map
                    if (all_prefix_strings.find(common_prefix) == all_prefix_strings.end()) {
                        all_prefix_strings[common_prefix] = strings_in_group;
                    } else {
                        // Merge the string sets
                        for (int id : strings_in_group) {
                            all_prefix_strings[common_prefix].insert(id);
                        }
                    }
                }
            }
        }

        multimap<int,string,greater<int>> mth_prefix_strings;
        for (auto x : all_prefix_strings) {
            string prefix = x.first;
            int prefix_size = prefix.length();
            set<int> diff_strings = x.second;
            int set_size = diff_strings.size();

            cout << "- prefixo '" << prefix << "' ocorre em " << set_size << " strings\n";

            if (set_size >= more_than_half) {
                mth_prefix_strings.insert({prefix_size, prefix});
            } 
        }

        if (mth_prefix_strings.empty()) {
            cout << "?\n";
        }
        else {
            auto it = mth_prefix_strings.begin();
            int max_length = it->first;
            while (it != mth_prefix_strings.end() && it->first == max_length) {
                cout << it->second << "\n";
                it = next(it);
            }
        }

        cin >> n_lifeforms;
    }

    return 0;
}