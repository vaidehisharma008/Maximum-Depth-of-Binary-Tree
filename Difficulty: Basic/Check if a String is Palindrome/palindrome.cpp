#include <iostream>
using namespace std;

int main(){

    string s;
    cout << "Enter the string : ";
    cin >> s;

    int left = 0;
    int right = s.length() -1;

    bool palindrome = true;

    while(left<right){
        if(s[left]==s[right]){
            left++;
            right--;
        }

        else{
            palindrome = false;
        break;

        }

    }

    if(palindrome){
        cout << "true" << endl;
    }
    else{   
        cout << "false" << endl;
    }

}
