#include <bits/stdc++.h>
using namespace std;

int N;
int allOnes;

void solveOptimal(int row, int ld, int rd, vector<int>& sol) {
    if (row == allOnes) {
        cout << "[";
        for (int i = 0; i < N; i++) {
            cout << "[";
            for (int j = 0; j < N; j++) {
                cout << ((sol[i] >> j) & 1);
                if (j != N-1) cout << ", ";
            }
            cout << "]";
            if (i != N-1) cout << ", ";
        }
        cout << "]\n";
        return;
    }

    int pos = ~(row | ld | rd) & allOnes;
    while (pos) {
        int p = pos & -pos; // rightmost 1
        pos -= p;
        sol.push_back(p);
        solveOptimal(row | p, (ld | p) << 1, (rd | p) >> 1, sol);
        sol.pop_back();
    }
}

int mainOptimal() {
    cout << "Enter N for Optimal Solution: ";
    cin >> N;
    allOnes = (1 << N) - 1;
    vector<int> sol;
    solveOptimal(0, 0, 0, sol);
    return 0;
}
