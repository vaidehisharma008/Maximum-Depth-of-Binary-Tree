/*
📝 Problem: Maximum Sum Such That No Two Elements Are Adjacent

Given an array of positive integers, find the maximum sum of elements such that no two elements are adjacent.

🎯 Examples:

Input: nums = [3, 2, 7, 10]
Output: 13
Explanation: Pick 3 and 10 => 3 + 10 = 13

Input: nums = [3, 2, 5, 10, 7]
Output: 15
Explanation: Pick 3 + 5 + 7 = 15

Approach:
- Use Dynamic Programming.
- At each index, decide whether to:
  1. Take the current element + result from i-2 (because adjacent is not allowed)
  2. Skip current and take result from i-1
- Base cases:
  - dp[0] = nums[0]
  - dp[1] = max(nums[0], nums[1])
- Final result: dp[n-1]
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maxSumNoAdjacent(const vector<int>& nums) {
    int n = nums.size();

    // Edge cases
    if (n == 0) return 0;
    if (n == 1) return nums[0];

    // dp[i] stores the max sum up to index i
    vector<int> dp(n);

    // Base cases
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);

    // Fill the dp array
    for (int i = 2; i < n; ++i) {
        // Max of: 
        // - current element + dp[i-2]
        // - dp[i-1] (excluding current element)
        dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
    }

    // Final answer
    return dp[n - 1];
}

int main() {
    // Test case 1
    vector<int> nums1 = {3, 2, 7, 10};
    cout << "Maximum sum (no adjacent) = " << maxSumNoAdjacent(nums1) << endl;
    // Output: 13

    // Test case 2
    vector<int> nums2 = {3, 2, 5, 10, 7};
    cout << "Maximum sum (no adjacent) = " << maxSumNoAdjacent(nums2) << endl;
    // Output: 15

    return 0;
}
