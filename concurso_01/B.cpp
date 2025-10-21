#include <bits/stdc++.h>
using namespace std;

bool is_possible(vector<int> nums, int c) {
    int k = 0;
    for (auto x : nums) {
        if (x >= c) {
            k++;
        }
    }
    return (k >= c);
}

int my_binary_search(vector<int> nums, int lower, int upper) {
    while (upper - lower > 1) {
        int middle = lower + (upper - lower) / 2;
        //cout << "lower=" << lower << " upper=" << upper << " middle=" << middle << "\n";
        if (is_possible(nums, middle)) {
            lower = middle;
        } else {
            upper = middle - 1;
        }
    }

    if (is_possible(nums,upper)) {
        return upper;
    } else {
        return lower;
    }
}

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //

    int n;
    cin >> n;

    vector<int> numbers;
    int max = 0;
    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        numbers.push_back(num);
        if (num > max) {
            max = num;
        }
    }

    int out = my_binary_search(numbers, 1, max);
    cout << out << "\n";

    return 0;
}
