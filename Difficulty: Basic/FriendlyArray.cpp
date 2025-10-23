#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    
    for (int i = 0; i < n; i++) cin >> arr[i];
    
    long long friendliness = 0;
    
    for (int i = 0; i < n; i++) {
        int next = (i + 1) % n; 
        friendliness += abs(arr[i] - arr[next]);
    }
    
    cout << friendliness << endl;
    return 0;
}
