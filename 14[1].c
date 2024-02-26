#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to encrypt a character using Vigenère cipher
char encryptChar(char plaintext, int key) {
    if (isalpha(plaintext)) {
        char base = isupper(plaintext) ? 'A' : 'a';
        return (char)(((plaintext - base + key) % 26) + base);
    }
    return plaintext; // Non-alphabetic characters remain unchanged
}

// Function to encrypt a string using one-time pad Vigenère cipher
void encryptVigenere(char *plaintext, int *key, char *ciphertext) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++) {
        ciphertext[i] = encryptChar(plaintext[i], key[i]);
    }
    ciphertext[len] = '\0'; // Null-terminate the string
}

int main() {
    char plaintext[100];
    int key[100];

    // Example key: 3 19 5 ...
    int keyStream[] = {3, 19, 5};

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character

    // Generate key stream based on the length of the plaintext
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++) {
        key[i] = keyStream[i % sizeof(keyStream)];
    }

    char ciphertext[100];
    encryptVigenere(plaintext, key, ciphertext);

    printf("Plaintext: %s\n", plaintext);
    printf("Key: ");
    for (int i = 0; i < len; i++) {
        printf("%d ", key[i]);
    }
    printf("\n");
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
