class Solution {
  public:
    int findStepKeyIndex(vector<int>& arr, int k, int x) {
        int i = 0;
        while (i < arr.size()) {
            if (arr[i] == x)
                return i;
            int step = max(1, abs(arr[i] - x) / k);
            i += step;
        }
        return -1;
    }
};
