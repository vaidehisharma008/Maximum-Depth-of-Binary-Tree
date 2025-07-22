void square(int s) {
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            // Print '*' on the border
            if (i == 0 || i == s - 1 || j == 0 || j == s - 1) {
                cout << "*";
            } else {
                cout << " ";
            }
            if (j != s - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
}
