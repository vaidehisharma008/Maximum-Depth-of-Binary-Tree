#include <bits/stdc++.h>
using namespace std;

int N;
vector<int> pos;   // pos[row] = col
vector<int> cols, diag1, diag2;

void printBoardBest() {
    cout << "[\n";
    for (int r = 0; r < N; ++r) {
        cout << "[";
        for (int c = 0; c < N; ++c) {
            cout << (pos[r] == c ? 1 : 0);
            if (c != N-1) cout << ", ";
        }
        cout << "]";
        if (r != N-1) cout << ",\n";
    }
    cout << "\n]\n";
}

bool solveBest(int row) {
    if (row == N) {
        printBoardBest();
        return true;
    }
    for (int c = 0; c < N; ++c) {
        if (cols[c] || diag1[row + c] || diag2[row - c + N - 1]) continue;
        pos[row] = c;
        cols[c] = diag1[row + c] = diag2[row - c + N - 1] = 1;
        if (solveBest(row + 1)) return true;
        cols[c] = diag1[row + c] = diag2[row - c + N - 1] = 0;
        pos[row] = -1;
    }
    return false;
}

int mainBest() {
    cout << "Enter N for Best Solution: ";
    cin >> N;
    pos.assign(N, -1);
    cols.assign(N, 0);
    diag1.assign(2*N, 0);
    diag2.assign(2*N, 0);

    if (!solveBest(0)) cout << "No solution exists\n";
    return 0;
}
