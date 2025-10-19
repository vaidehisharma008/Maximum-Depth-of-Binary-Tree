#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

const int MAXB = 64;  // 64 bits for 64-bit numbers
ull C[MAXB + 1][MAXB + 1]; // nCr lookup table

// Build Pascal's triangle for combinations
void buildComb() {
    for (int n = 0; n <= MAXB; ++n) {
        for (int r = 0; r <= n; ++r) {
            if (r == 0 || r == n)
                C[n][r] = 1;
            else
                C[n][r] = min<ull>(C[n - 1][r - 1] + C[n - 1][r], ULLONG_MAX / 2);
        }
    }
}

// Count how many numbers <= x have exactly k set bits
ull countSet(ull x, int k) {
    if (k == 0)
        return 1;
    if (x == 0)
        return 0;

    int h = 63 - __builtin_clzll(x); // highest set bit position (log2)
    if (h < k - 1)
        return 0;

    ull withoutHighest = C[h][k];
    ull withHighest = countSet(x ^ (1ULL << h), k - 1);
    return withoutHighest + withHighest;
}

// Count numbers <= x with at most k set bits
ull total(ull x, int k) {
    ull ans = 0;
    for (int i = 0; i <= k; ++i)
        ans += countSet(x, i);
    return ans;
}

class Solution {
public:
    ull findNthNumber(ull n, int k) {
        ull low = 0, high = (ull)1e15;
        while (low < high) {
            ull mid = low + (high - low) / 2;
            if (total(mid, k) >= n)
                high = mid;
            else
                low = mid + 1;
        }
        return low;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    buildComb();

    int t;
    cin >> t;
    while (t--) {
        ull n;
        int k;
        cin >> n >> k;
        Solution sol;
        cout << sol.findNthNumber(n, k) << "\n";
    }

    return 0;
}
