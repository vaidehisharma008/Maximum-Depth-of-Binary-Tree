// To find the shortest possible route in which all the cities are visited exactly once and return back to the starting city
// This code uses DP with time complexity of O(2^n.n²) and space O(n.2^n)

class Solution {
public:
    int total_cost(int cost[][13], int n) {
        // dp[mask][i] stores the minimum cost to visit all cities in 'mask' ending at city 'i'
        vector<vector<int>> dp(1 << n, vector<int>(n, -1));
        return tsp(cost, n, 1, 0, dp);  // Start from city 0 with mask = 1 (only 0 visited)
    }

private:
    int tsp(int cost[][13], int n, int mask, int pos, vector<vector<int>>& dp) {
        // Base case: all cities visited, return cost to go back to start (city 0)
        if (mask == (1 << n) - 1)
            return cost[pos][0];

        // Return memoized result
        if (dp[mask][pos] != -1)
            return dp[mask][pos];

        int ans = INT_MAX;

        // Try to go to every unvisited city
        for (int city = 0; city < n; city++) {
            if ((mask & (1 << city)) == 0) {  // If city not visited
                int newCost = cost[pos][city] + tsp(cost, n, mask | (1 << city), city, dp);
                ans = min(ans, newCost);
            }
        }

        return dp[mask][pos] = ans;  // Store and return minimum cost
    }
};
