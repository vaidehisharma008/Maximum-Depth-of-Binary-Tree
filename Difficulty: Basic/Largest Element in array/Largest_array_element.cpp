#include <bits/stdc++.h>
#define ll long long int
using namespace std;

ll largest_element_in_array(vector<ll>& v, ll n) {
    ll maxi = v[0];
    for (ll i = 0; i < n; i++) {
        if (maxi < v[i]) maxi = v[i];
    }
    return maxi;
}

int main() {
    ll n;
    cin>>n;
    vector<ll>v(n);
    for(ll i=0;i<n;i++) cin>>v[i];
    ll ans = largest_element_in_array(v, n);
    cout << ans << endl;
    return 0;

}
