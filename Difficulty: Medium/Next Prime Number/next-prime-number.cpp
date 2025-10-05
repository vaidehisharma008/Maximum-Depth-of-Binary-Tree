bool isPrime(int num) {
    if (num <= 1) return false;

    for (int i = 2; i*i <= num; i++) {
        if (num % i == 0)
            return false;
    }

    return true;
}

int nextPrime(int n) {
    int candidate = n + 1;

    while (true) {
        if (isPrime(candidate))
            return candidate;
        candidate++;
    }
}
