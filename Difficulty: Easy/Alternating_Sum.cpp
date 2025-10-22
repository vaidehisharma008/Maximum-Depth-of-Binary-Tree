#include <bits/stdc++.h>
using namespace std;

int alternatingSum(vector<int>& nums) {
    int sum = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (i % 2 == 0) sum += nums[i];
        else sum -= nums[i];
    }
    return sum;
}

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];
    cout << alternatingSum(nums) << endl;
    return 0;
}
