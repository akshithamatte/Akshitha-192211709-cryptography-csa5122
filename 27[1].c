#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_MSG_LEN 1000

// Function prototypes
void rsa_encrypt(char *plaintext, int *ciphertext, int n, int e);
void rsa_decrypt(int *ciphertext, char *plaintext, int n, int d);
void frequency_analysis(int *ciphertext, int num_chars);

int main() {
    char plaintext[MAX_MSG_LEN] = "HELLO"; // Example plaintext
    int ciphertext[MAX_MSG_LEN] = {0}; // Initialize ciphertext array

    int n = 10007; // Large modulus n
    int e = 65537; // Large exponent e (usually chosen as 65537 in practice)
    int d = 1; // For demonstration purposes, d is set to 1 (insecure)

    printf("Plaintext: %s\n", plaintext);

    // Encrypt plaintext
    rsa_encrypt(plaintext, ciphertext, n, e);
    printf("Ciphertext: ");
    int i;
    for (i = 0; i < strlen(plaintext); i++) {
        printf("%d ", ciphertext[i]);
    }
    printf("\n");

    // Perform frequency analysis attack
    frequency_analysis(ciphertext, strlen(plaintext));

    return 0;
}

// Function to encrypt plaintext using insecure RSA method
void rsa_encrypt(char *plaintext, int *ciphertext, int n, int e) {
    int i;
    for (i = 0; i < strlen(plaintext); i++) {
        ciphertext[i] = fmod(pow((int)(plaintext[i] - 'A'), e), n); // Basic RSA encryption
    }
}

// Function to decrypt ciphertext using insecure RSA method
void rsa_decrypt(int *ciphertext, char *plaintext, int n, int d) {
    int i;
    for (i = 0; i < MAX_MSG_LEN; i++) {
        plaintext[i] = (char)(fmod(pow(ciphertext[i], d), n) + 'A'); // Basic RSA decryption
    }
}

// Function to perform frequency analysis attack
void frequency_analysis(int *ciphertext, int num_chars) {
    int frequency[26] = {0}; // Initialize array to store frequency of ciphertext characters

    int i;
    // Count frequency of ciphertext characters
    for (i = 0; i < num_chars; i++) {
        frequency[ciphertext[i]]++;
    }

    // Find the most frequent ciphertext character
    int max_freq = -1;
    int max_index = -1;
    for (i = 0; i < 26; i++) {
        if (frequency[i] > max_freq) {
            max_freq = frequency[i];
            max_index = i;
        }
    }

    // Assuming max_index corresponds to 'E' in English alphabet (most common letter)
    // Decrypt ciphertext using this assumption
    int key = (max_index - ('E' - 'A') + 26) % 26;
    printf("Assuming %c corresponds to 'E', decrypted message: ", (char)(max_index + 'A'));
    for (i = 0; i < num_chars; i++) {
        printf("%c", (char)(((ciphertext[i] - key + 26) % 26) + 'A'));
    }
    printf("\n");
}

