#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canSplitEqualScore(string s) {
        int n = s.size();
        int total = 0;

        // Calculate total score of string
        for (char c : s)
            total += (c - 'a' + 1);

        int leftSum = 0;
        // Check possible splits (must split into two non-empty parts)
        for (int i = 0; i < n - 1; i++) {
            leftSum += (s[i] - 'a' + 1);
            if (leftSum == total - leftSum)
                return true;
        }
        return false;
    }
};

int main() {
    Solution sol;
    cout << boolalpha << sol.canSplitEqualScore("adcb") << endl; // true
    cout << boolalpha << sol.canSplitEqualScore("bace") << endl; // false
    return 0;
}
