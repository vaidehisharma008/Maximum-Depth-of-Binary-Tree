#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> triangle; // should be 2D vector

        for (int i = 0; i < numRows; i++) {
            vector<int> row(i + 1, 1); // initialize row with 1s

            for (int j = 1; j < i; j++) {
                row[j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
            }

            triangle.push_back(row); // push the completed row into triangle
        }

        return triangle;
    }
};
