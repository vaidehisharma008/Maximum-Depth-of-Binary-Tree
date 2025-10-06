#include <bits/stdc++.h>
using namespace std;

// Class using the Sliding Window technique
// Time: O(n), Space: O(1)
class Solution_with_sliding_window {
public:
    int lengthOfLongestSubstring(string s) {
        int ans = 0;
        vector<int> count(128, 0); 
        int l = 0;
        for (int r = 0; r < s.length(); ++r) {
            count[s[r]]++;
            while (count[s[r]] > 1) {
                count[s[l]]--;
                l++;
            }
            ans = max(ans, r - l + 1);
        }
        return ans;
    }
};

// Class using the Last Seen Index technique
// Time: O(n), Space: O(1)
class Solution_with_last_seen {
public:
    int lengthOfLongestSubstring(string s) {
        int ans = 0;
        vector<int> lastSeen(128, -1);
        int j = -1; 
        
        for (int i = 0; i < s.length(); ++i) {
            j = max(j, lastSeen[s[i]]);
            ans = max(ans, i - j);
            lastSeen[s[i]] = i;
        }
        return ans;
    }
};

void print_result(const string& s, int expected, int result1, int result2) {
    cout << "Input: " << s << endl;
    cout << "Expected: " << expected << endl;
    cout << "Sliding Window Result: " << result1 << endl;
    cout << "Last Seen Index Result: " << result2 << endl;
    cout << endl;
}

int main() {
    Solution_with_sliding_window solution1;
    Solution_with_last_seen solution2;

    // Example 1: Input: s = "abcabcbb" -> Output: 3
    string s1_input = "abcabcbb";
    int s1_expected = 3;
    int r1_1 = solution1.lengthOfLongestSubstring(s1_input);
    int r2_1 = solution2.lengthOfLongestSubstring(s1_input);
    print_result(s1_input, s1_expected, r1_1, r2_1);

    // Example 2: Input: s = "bbbbb" -> Output: 1
    string s2_input = "bbbbb";
    int s2_expected = 1;
    int r1_2 = solution1.lengthOfLongestSubstring(s2_input);
    int r2_2 = solution2.lengthOfLongestSubstring(s2_input);
    print_result(s2_input, s2_expected, r1_2, r2_2);

    // Example 3: Input: s = "pwwkew" -> Output: 3
    string s3_input = "pwwkew";
    int s3_expected = 3;
    int r1_3 = solution1.lengthOfLongestSubstring(s3_input);
    int r2_3 = solution2.lengthOfLongestSubstring(s3_input);
    print_result(s3_input, s3_expected, r1_3, r2_3);

    return 0;
}