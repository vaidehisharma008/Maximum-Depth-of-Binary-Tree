class Solution {
  public:
    int binaryToDecimal(string &b) {
        int decimal = 0;
        int n = b.length();
        for (int i = 0; i < n; i++) {
            decimal = decimal * 2 + (b[i] - '0');
        }
        return decimal;
    }
};