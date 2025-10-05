#include <bits/stdc++.h>
using namespace std;

// Check if a queen can be placed at (row, col)
bool isSafe(vector<string>& board, int row, int col, int N) {
    // Check column and diagonals
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 'Q') return false;
        int d = row - i;
        if (col - d >= 0 && board[i][col - d] == 'Q') return false;
        if (col + d < N && board[i][col + d] == 'Q') return false;
    }
    return true;
}

bool solveBF(vector<string>& board, int row, int N) {
    if (row == N) return true;

    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col, N)) {
            board[row][col] = 'Q';
            if (solveBF(board, row + 1, N)) return true;
            board[row][col] = '.'; // backtrack
        }
    }
    return false;
}

void printBoardBF(vector<string>& board) {
    cout << "[\n";
    for (auto& row : board) {
        cout << "[";
        for (int i = 0; i < row.size(); i++) {
            cout << (row[i] == 'Q' ? 1 : 0);
            if (i != row.size()-1) cout << ", ";
        }
        cout << "]";
        if (&row != &board.back()) cout << ",\n";
    }
    cout << "\n]\n";
}

int mainBF() {
    int N;
    cout << "Enter N for Brute Force: ";
    cin >> N;
    vector<string> board(N, string(N, '.'));
    if (solveBF(board, 0, N)) printBoardBF(board);
    else cout << "No solution exists\n";
    return 0;
}
