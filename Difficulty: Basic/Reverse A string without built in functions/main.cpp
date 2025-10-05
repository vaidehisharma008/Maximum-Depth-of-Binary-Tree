#include <iostream>
#include <string>
using namespace std;

string reverseString(string s) {
    int left = 0, right = s.length() - 1;
    
    while (left < right) {
        // swap characters
        char temp = s[left];
        s[left] = s[right];
        s[right] = temp;
        
        left++;
        right--;
    }
    return s;
}

int main() {
    string input = "hello";
    cout << "Input: " << input << endl;
    cout << "Output: " << reverseString(input) << endl;
    return 0;
}
