#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26
#define MAX_PLAINTEXTS 10

// Function to shift a character by a given key (mod 26)
char shiftCharacter(char c, int key) {
    if (c >= 'A' && c <= 'Z') {
        return ((c - 'A' + key) % ALPHABET_SIZE) + 'A';
    } else if (c >= 'a' && c <= 'z') {
        return ((c - 'a' + key) % ALPHABET_SIZE) + 'a';
    } else {
        return c; // Preserve non-alphabetic characters
    }
}

// Function to decrypt the ciphertext using a given key (additive cipher)
void decrypt(char ciphertext[], int key) {
    int length = strlen(ciphertext);
    int i;
    printf("Key: %d\n", key);
    printf("Decrypted plaintext: ");
    for ( i = 0; i < length; i++) {
        printf("%c", shiftCharacter(ciphertext[i], -key));
    }
    printf("\n\n");
}

// Function to count the frequency of each letter in the ciphertext
void countFrequency(char ciphertext[], int frequency[]) {
    int length = strlen(ciphertext);
    int i;
    for ( i = 0; i < length; i++) {
        char c = ciphertext[i];
        if (c >= 'A' && c <= 'Z') {
            frequency[c - 'A']++;
        } else if (c >= 'a' && c <= 'z') {
            frequency[c - 'a']++;
        }
    }
}

// Function to find the most likely key based on letter frequency analysis
int findLikelyKey(int frequency[]) {
    int maxCount = 0;
    int likelyKey = 0;
    int i;
    for ( i = 0; i < ALPHABET_SIZE; i++) {
        if (frequency[i] > maxCount) {
            maxCount = frequency[i];
            likelyKey = (i - ('E' - 'A') + ALPHABET_SIZE) % ALPHABET_SIZE; // Assuming 'E' is the most frequent letter in English
        }
    }
    return likelyKey;
}

int main() {
    char ciphertext[] = "KHOOR ZRUOG";
    int frequency[ALPHABET_SIZE] = {0};

    // Count frequency of each letter in the ciphertext
    countFrequency(ciphertext, frequency);

    // Find the most likely key based on letter frequency analysis
    int likelyKey = findLikelyKey(frequency);

    printf("Most likely key: %d\n\n", likelyKey);

    // Decrypt with the most likely key
    decrypt(ciphertext, likelyKey);

    return 0;
}

