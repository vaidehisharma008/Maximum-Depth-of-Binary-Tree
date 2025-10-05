int findPattern(string &s, string &p) {
    int n = s.size(), m = p.size();
    if (m > n) return -1;
    for (int i = 0; i <= n - m; ++i) {
        int j = 0;
        while (j < m && s[i + j] == p[j]) {
            ++j;
        }
        if (j == m) return i;
    }
    return -1;
}
