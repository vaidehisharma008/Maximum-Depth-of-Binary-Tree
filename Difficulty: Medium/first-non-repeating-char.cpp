#include <bits/stdc++.h>
using namespace std;

char firstNonRepeatingCharacter(const string &s) {
    unordered_map<char, int> freq;

    // Count frequency of each character
    for (char ch : s) {
        freq[ch]++;
    }

    // Find the first character with frequency 1
    for (char ch : s) {
        if (freq[ch] == 1) {
            return ch;
        }
    }

    // Return a placeholder if no non-repeating character exists
    return '\0';
}

int main() {
    string str;
    cout << "Enter a string: ";
    cin >> str;

    char result = firstNonRepeatingCharacter(str);

    if (result != '\0') {
        cout << "First non-repeating character: " << result << "\n";
    } else {
        cout << "No non-repeating character found\n";
    }

    return 0;
}
