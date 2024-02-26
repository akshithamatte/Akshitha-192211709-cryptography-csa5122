#include <stdio.h>

// Function to calculate the greatest common divisor using Euclidean algorithm
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to calculate the modular inverse using the extended Euclidean algorithm
int modInverse(int a, int m) {
    for (int i = 1; i < m; i++) {
        if ((a * i) % m == 1) {
            return i;
        }
    }
    return -1; // Modular inverse doesn't exist
}

int main() {
    int e = 31, n = 3599;
    int p, q;

    // Trial-and-error to find p and q
    for (p = 2; p < n; p++) {
        if (n % p == 0) {
            q = n / p;
            break;
        }
    }

    // Calculate totient (?(n))
    int phi_n = (p - 1) * (q - 1);

    // Calculate private key (d)
    int d = modInverse(e, phi_n);

    // Display results
    printf("p: %d\n", p);
    printf("q: %d\n", q);
    printf("Private Key (d): %d\n", d);

    return 0;
}
