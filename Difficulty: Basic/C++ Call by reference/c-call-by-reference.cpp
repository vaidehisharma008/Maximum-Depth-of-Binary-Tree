void reverse_dig(int &a, int &b) {
    int r1 = 0, r2 = 0;
    while (a != 0) {
        r1 = r1 * 10 + a % 10;
        a /= 10;
    }
    while (b != 0) {
        r2 = r2 * 10 + b % 10;
        b /= 10;
    }
    a = r1;
    b = r2;
}
void swap(int &a, int &b) {
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}
