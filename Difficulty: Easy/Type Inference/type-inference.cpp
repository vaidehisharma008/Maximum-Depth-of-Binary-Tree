#include <iostream>
#include <typeinfo>
using namespace std;

int main() {
    int a = 3;
    float b = 5.57;
    string id1 = typeid(a).name();
    string id2 = typeid(b).name();
    cout << id1 << " " << id2 << endl;
}