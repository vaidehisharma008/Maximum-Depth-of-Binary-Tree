#include <iostream>
#include <vector>
using namespace std;

int findLargest(const vector<int>& arr) {
    if (arr.empty()) {
        throw invalid_argument("Array is empty");
    }
    int largest = arr[0];
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i] > largest) {
            largest = arr[i];
        }
    }
    return largest;
}

int main() {
    vector<int> arr = {10, 45, 2, 99, 23, 56};
    try {
        cout << "Largest element: " << findLargest(arr) << endl;
    } catch (const exception& e) {
        cout << e.what() << endl;
    }
    return 0;
}