#include <iostream>
#include <string>
using namespace std;

int main() {
    string num;
    getline(cin, num);
    int n = stoi(num);    // Convert string to integer
    cout << n * 2 << endl;
    return 0;
}
