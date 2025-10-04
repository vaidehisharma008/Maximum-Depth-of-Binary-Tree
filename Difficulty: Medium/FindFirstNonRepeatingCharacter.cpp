#include <iostream>
#include <unordered_map>
using namespace std;

char firstNonRepeatingChar(const string &s) {
    unordered_map<char, int> freq;
    for (char c : s) {
        freq[c]++;
    }
    for (char c : s) {
        if (freq[c] == 1)
            return c;
    }
    return '\0';
}

int main() {
    string str;
    cout << "Enter a string: ";
    cin >> str;
    char result = firstNonRepeatingChar(str);
    if (result != '\0')
        cout << "First non-repeating character: " << result;
    return 0;
}
