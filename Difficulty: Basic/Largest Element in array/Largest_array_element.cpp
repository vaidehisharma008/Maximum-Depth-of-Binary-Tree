#include <bits/stdc++.h>
#define ll long long int
using namespace std;

int largest_element_in_array(vector<int>& v, int n) {
    int maxi = v[0];
    for (int i = 0; i < n; i++) {
        if (maxi < v[i]) maxi = v[i];
    }
    return maxi;
}

int main() {
    vector<ll> v = {1, 4, 3, 5};
    int n = v.size();
    int ans = largest_element_in_array(v, n);
    cout << ans << endl;
    return 0;
}