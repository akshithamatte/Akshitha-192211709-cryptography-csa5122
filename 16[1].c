#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define MAX_PLAINTEXTS 10

// Function to decrypt the ciphertext using a given key (monoalphabetic substitution)
void decrypt(char ciphertext[], char key[]) {
    int length = strlen(ciphertext);
    int i;
    printf("Decrypted plaintext: ");
    for ( i = 0; i < length; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            printf("%c", key[ciphertext[i] - 'A']);
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            printf("%c", key[ciphertext[i] - 'a'] + 32); // Convert to lowercase
        } else {
            printf("%c", ciphertext[i]); // Preserve non-alphabetic characters
        }
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

// Function to find the most likely plaintexts based on letter frequency analysis
void findLikelyPlaintexts(char ciphertext[], int frequency[]) {
    int maxCount = 0;
    int i,k;
    char mostFrequentChar = 'A'; // Assume 'A' is the most frequent letter in English
    for (i = 0; i < ALPHABET_SIZE; i++) {
        if (frequency[i] > maxCount) {
            maxCount = frequency[i];
            mostFrequentChar = 'A' + i;
        }
    }

    // Calculate the shift required to map the most frequent ciphertext character to 'E' (most frequent letter in English)
    int shift = (mostFrequentChar - 'E' + ALPHABET_SIZE) % ALPHABET_SIZE;

    // Generate possible plaintexts based on the calculated shift
    printf("Top %d possible plaintexts:\n", MAX_PLAINTEXTS);
    for (k = 0; k < MAX_PLAINTEXTS; k++) {
        char key[ALPHABET_SIZE];
        for ( i = 0; i < ALPHABET_SIZE; i++) {
            key[i] = ((i - shift + ALPHABET_SIZE) % ALPHABET_SIZE) + 'A'; // Shift the alphabet
        }
        decrypt(ciphertext, key);
        shift++; // Try the next possible shift
    }
}

int main() {
    char ciphertext[] = "KHOOR ZRUOG";
    int frequency[ALPHABET_SIZE] = {0};

    // Count frequency of each letter in the ciphertext
    countFrequency(ciphertext, frequency);

    // Find the most likely plaintexts based on letter frequency analysis
    findLikelyPlaintexts(ciphertext, frequency);

    return 0;
}

