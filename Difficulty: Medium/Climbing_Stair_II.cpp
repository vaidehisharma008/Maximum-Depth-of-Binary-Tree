#include <bits/stdc++.h>
using namespace std;

int minCostToReachEnd(int n, vector<int>& costs) {
    long long dp1 = 0, dp2 = LLONG_MAX, dp3 = LLONG_MAX; // dp[i-1], dp[i-2], dp[i-3]
    long long curr = 0;

    for (int i = 1; i <= n; i++) {
        curr = LLONG_MAX;
        if (i - 1 >= 0) curr = min(curr, dp1 + costs[i - 1] + 1LL * 1 * 1);
        if (i - 2 >= 0) curr = min(curr, dp2 + costs[i - 1] + 1LL * 2 * 2);
        if (i - 3 >= 0) curr = min(curr, dp3 + costs[i - 1] + 1LL * 3 * 3);

        // Shift the window
        dp3 = dp2;
        dp2 = dp1;
        dp1 = curr;
    }

    return (int)dp1;
}

int main() {
    int n;
    cin >> n;
    vector<int> costs(n);
    for (int i = 0; i < n; i++) cin >> costs[i];
    
    cout << minCostToReachEnd(n, costs) << endl;
    return 0;
}
