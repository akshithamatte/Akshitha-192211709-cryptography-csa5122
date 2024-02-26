#include <stdio.h>

#define MATRIX_SIZE 2 // Size of the key matrix (for simplicity, assuming a 2x2 matrix)
#define ALPHABET_SIZE 26 // Size of the English alphabet

// Function to calculate the determinant of a 2x2 matrix
int determinant(int key[MATRIX_SIZE][MATRIX_SIZE]) {
    return key[0][0] * key[1][1] - key[0][1] * key[1][0];
}

// Function to calculate the modular inverse of a number 'a' modulo 'm'
// Returns -1 if no modular inverse exists
int modInverse(int a, int m) {
    a = a % m;
    int x;
    for (x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}

// Function to decrypt a ciphertext using the Hill cipher with a given key matrix
void decrypt(int ciphertext[], int key[MATRIX_SIZE][MATRIX_SIZE], int n) {
    int invDet = modInverse(determinant(key), ALPHABET_SIZE);
    if (invDet == -1) {
        printf("The key is not invertible.\n");
        return;
    }

    // Calculate the adjoint matrix
    int adj[MATRIX_SIZE][MATRIX_SIZE] = {
        {key[1][1], -key[0][1]},
        {-key[1][0], key[0][0]}
    };

    // Calculate the inverse of the key matrix
    int i, j;
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            adj[i][j] = (adj[i][j] % ALPHABET_SIZE + ALPHABET_SIZE) % ALPHABET_SIZE;
            key[i][j] = (adj[i][j] * invDet) % ALPHABET_SIZE;
        }
    }

    // Decrypt the ciphertext
    printf("Decrypted plaintext: ");
    for (i = 0; i < n; i += MATRIX_SIZE) {
        int x = key[0][0] * ciphertext[i] + key[0][1] * ciphertext[i + 1];
        int y = key[1][0] * ciphertext[i] + key[1][1] * ciphertext[i + 1];
        printf("%c%c", (x % ALPHABET_SIZE) + 'A', (y % ALPHABET_SIZE) + 'A');
    }
    printf("\n");
}

int main() {
    // Known plaintext-ciphertext pairs
    int plaintext1[] = {0, 1}; // "AB"
    int ciphertext1[] = {9, 22}; // "WV"
    int plaintext2[] = {2, 3}; // "CD"
    int ciphertext2[] = {2, 15}; // "CP"

    // Construct the key matrix using the known plaintext-ciphertext pairs
    int det = (plaintext1[0] * plaintext2[1]) - (plaintext1[1] * plaintext2[0]);
    if (det == 0) {
        printf("Determinant is 0, the key is not invertible.\n");
        return 1;
    }

    int invDet = modInverse(det, ALPHABET_SIZE);
    if (invDet == -1) {
        printf("Modular inverse of the determinant does not exist.\n");
        return 1;
    }

    int key[MATRIX_SIZE][MATRIX_SIZE] = {
        {(plaintext2[1] * invDet) % ALPHABET_SIZE, (-plaintext1[1] * invDet) % ALPHABET_SIZE},
        {(-plaintext2[0] * invDet) % ALPHABET_SIZE, (plaintext1[0] * invDet) % ALPHABET_SIZE}
    };

    // Decrypt a ciphertext using the recovered key
    int ciphertext[] = {0, 3, 4, 18, 24, 4, 13, 3, 0, 16, 20, 17, 4, 18, 8, 18, 4, 17, 4, 18, 24, 3, 19, 0, 4};
    int n = sizeof(ciphertext) / sizeof(ciphertext[0]);
    decrypt(ciphertext, key, n);

    return 0;
}

