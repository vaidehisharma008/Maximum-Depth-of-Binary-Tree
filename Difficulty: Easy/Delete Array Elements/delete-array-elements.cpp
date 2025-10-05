// Function to delete elements from the array based on some conditions.
class Solution {
  public:

    vector<int> deleteElement(vector<int>& arr, int k) {
        int n = arr.size();
        stack<int> s;
        s.push(arr[0]);
        int countt = 0;

        // iterating over the elements of the array
        for (int i = 1; i < n; i++) {
            // removing elements from the stack if they are smaller than the current
            // element and the count is less than k
            while (!s.empty() && s.top() < arr[i] && countt < k) {
                s.pop();
                countt++;
            }
            // pushing the current element into the stack
            s.push(arr[i]);
        }
        int m = s.size();
        vector<int> v(m);

        // populating the vector with elements from the stack
        while (!s.empty()) {
            v[--m] = s.top();
            s.pop();
        }

        // returning the vector
        return v;
    }
};