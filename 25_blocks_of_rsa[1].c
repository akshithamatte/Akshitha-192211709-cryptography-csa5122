#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to calculate the greatest common divisor
long long gcd(long long a, long long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to factorize n and compute private key d
long long factorize_and_compute_d(long long n, long long e) {
    long long p, q;
    
    // Find a candidate factor x
    long long x = gcd(n, e);
    
    // Factorize n
    p = x;
    q = n / x;
    
    // Compute private key d
    long long phi = (p - 1) * (q - 1);
    long long d;
    
    for (d = 2; d < phi; d++) {
        if ((e * d) % phi == 1) {
            break;
        }
    }

    return d;
}

// Function to decrypt the ciphertext using private key d
long long decrypt(long long ciphertext, long long d, long long n) {
    long long decrypted = 1;
    for (long long i = 0; i < d; i++) {
        decrypted = (decrypted * ciphertext) % n;
    }
    return decrypted;
}

int main() {
    // Public key components
    long long n = 143;  // Replace with your actual n
    long long e = 7;    // Replace with your actual e
    
    // Ciphertext block
    long long ciphertext = 49;  // Replace with your actual ciphertext block
    
    // Factorize n and compute private key d
    long long d = factorize_and_compute_d(n, e);

    // Decrypt the ciphertext
    long long decrypted = decrypt(ciphertext, d, n);

    // Print the result
    printf("Decrypted plaintext block: %lld\n", decrypted);

    return 0;
}
