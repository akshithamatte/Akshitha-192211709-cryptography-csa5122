#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Function to calculate the greatest common divisor (GCD) of two numbers
uint64_t gcd(uint64_t a, uint64_t b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

// Function to calculate the modular exponentiation (x^y mod N)
uint64_t mod_exp(uint64_t x, uint64_t y, uint64_t N) {
    uint64_t result = 1;
    x = x % N;
    while (y > 0) {
        if (y % 2 == 1) {
            result = (result * x) % N;
        }
        y = y / 2;
        x = (x * x) % N;
    }
    return result;
}

// Function to generate a new public and private key pair
void generate_new_key_pair(uint64_t p, uint64_t q, uint64_t *e, uint64_t *d, uint64_t *N) {
    uint64_t phi = (p - 1) * (q - 1);
    *N = p * q;

    // Choose a new public key 'e' (typically a small prime number)
    *e = 65537;  // Commonly used value for 'e'

    // Calculate the new private key 'd' using the modular multiplicative inverse
    *d = 1;
    while ((*d * *e) % phi != 1) {
        (*d)++;
    }
}

int main() {
    // Original public and private keys
    uint64_t p = 61;  // A prime number
    uint64_t q = 53;  // Another prime number
    uint64_t e_bob = 17;  // Bob's original public key
    uint64_t d_bob = 2753;  // Bob's leaked private key
    uint64_t N_bob;  // Bob's original modulus

    // Generate new public and private keys after Bob's private key has been leaked
    uint64_t e_new, d_new, N_new;
    generate_new_key_pair(p, q, &e_new, &d_new, &N_new);

    // Output
    printf("Bob's original public key (e): %lu\n", e_bob);
    printf("Bob's leaked private key (d): %lu\n", d_bob);
    printf("Bob's original modulus (N): %lu\n", N_bob);

    printf("\nNew public key (e): %lu\n", e_new);
    printf("New private key (d): %lu\n", d_new);
    printf("New modulus (N): %lu\n", N_new);

    return 0;
}

