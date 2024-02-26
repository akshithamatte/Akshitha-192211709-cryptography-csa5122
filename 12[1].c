#include <stdio.h>
#include <string.h>

#define SIZE 100

// Function to encrypt a message using Hill cipher
void hillCipherEncrypt(char message[], int key[2][2]) {
    int len = strlen(message);
    int encrypted[len];

    for (int i = 0; i < len; i += 2) {
        // Convert pairs of characters to corresponding numeric values
        int p1 = message[i] - 'a';
        int p2 = message[i + 1] - 'a';

        // Apply the Hill cipher encryption formula
        encrypted[i] = (key[0][0] * p1 + key[0][1] * p2) % 26;
        encrypted[i + 1] = (key[1][0] * p1 + key[1][1] * p2) % 26;

        // Convert back to characters
        encrypted[i] += 'a';
        encrypted[i + 1] += 'a';
    }

    // Display the encrypted message
    printf("Encrypted message: %s\n", encrypted);
}

int main() {
    char message[] = "meetmeattheusualplaceattenratherthaneightoclock";
    int key[2][2] = {{9, 4}, {5, 7}};

    // Display the original message
    printf("Original message: %s\n", message);

    // Encrypt the message using the Hill cipher
    hillCipherEncrypt(message, key);

    return 0;
}
