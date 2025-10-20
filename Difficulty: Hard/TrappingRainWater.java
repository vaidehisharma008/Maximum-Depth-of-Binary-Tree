class Solution {
    public int maxWater(int arr[]) {
        int n = arr.length;
        if (n == 0) return 0;

        int left = 0, right = n - 1;
        int leftMax = 0, rightMax = 0;
        int water = 0;

        while (left < right) {
            if (arr[left] <= arr[right]) {
                if (arr[left] >= leftMax) {
                    leftMax = arr[left];
                } else {
                    water += leftMax - arr[left];
                }
                left++;
            } else {
                if (arr[right] >= rightMax) {
                    rightMax = arr[right];
                } else {
                    water += rightMax - arr[right];
                }
                right--;
            }
        }

        return water;
    }

    // Optional: for testing
    public static void main(String[] args) {
        Solution sol = new Solution();
        int arr[] = {3, 0, 1, 0, 4, 0, 2};
        System.out.println(sol.maxWater(arr)); // Output: 10
    }
}
