#include <iostream>
using namespace std;

int main() {
    int n1, n2, m1, m2;
    cin >> n1 >> n2;
    int A[n1][n2];
    for (int i = 0; i < n1; i++)
        for (int j = 0; j < n2; j++)
            cin >> A[i][j];

            cin >> m1 >> m2;
    int B[m1][m2];

    for (int i = 0; i < m1; i++)
        for (int j = 0; j < m2; j++)
            cin >> B[i][j];

    if (n2 != m1) {
        cout << "Matrix multiplication not possible" << endl;
        return 0;
    }

    int C[n1][m2];

    for (int i = 0; i < n1; i++)
        for (int j = 0; j < m2; j++)
            C[i][j] = 0;

    for (int i = 0; i < n1; i++)
        for (int j = 0; j < m2; j++)
            for (int k = 0; k < n2; k++)
                C[i][j] += A[i][k] * B[k][j];

    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m2; j++)
            cout << C[i][j] << " ";
        cout << endl;
    }
    return 0;
}
