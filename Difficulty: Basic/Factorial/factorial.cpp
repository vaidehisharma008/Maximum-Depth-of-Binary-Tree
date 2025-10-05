// User function Template for C++

int nFactorial(int n) {
    int ans = 1;
    while (n!=0) {
        ans=ans*n;
        n--;
    }
    return ans;
}