#include <bits/stdc++.h>
using namespace std;

int* greaterElement(int arr[], int n) {
    set<int> s(arr, arr + n); // store all elements in sorted order
    int* res = new int[n];

    for (int i = 0; i < n; i++) {
        auto it = s.upper_bound(arr[i]); // first element strictly greater than arr[i]
        if (it == s.end()) {
            res[i] = -10000000;
        } else {
            res[i] = *it;
        }
    }

    return res;
}
