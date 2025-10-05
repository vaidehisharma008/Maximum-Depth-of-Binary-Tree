string reverseString(string &s) {
    int l = s.length();
    string rev = "";
    for (int i = l - 1; i >= 0; i--) {
        rev += s[i];
    }
    return rev;
}
