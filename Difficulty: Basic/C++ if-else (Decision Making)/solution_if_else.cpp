class Solution {
public:
    void compareWithFive(int n) {
        // Check if the number is greater than 5
        if (n > 5)
            cout << "Greater than 5";
        // Check if the number is less than 5
        else if (n < 5)
            cout << "Less than 5";
        // If the number is equal to 5
        else
            cout << "Equal to 5";
    }
};
