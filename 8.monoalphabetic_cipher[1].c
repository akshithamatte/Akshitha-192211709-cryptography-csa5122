#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to generate the cipher sequence from the keyword
void generateCipherSequence(char keyword[], char cipherSeq[]) {
    int i, j;
    int keywordLength = strlen(keyword);
    int index = 0;
    // Copy the keyword to the cipher sequence
    strcpy(cipherSeq, keyword);
    
    // Mark the letters in the keyword as used by changing them to a special character
    for (i = 0; i < keywordLength; i++) {
        keyword[i] = toupper(keyword[i]);
        cipherSeq[i] = toupper(cipherSeq[i]);
        for (j = i + 1; j < keywordLength; j++) {
            if (cipherSeq[j] == keyword[i])
                cipherSeq[j] = '*'; // Change repeated letters to a special character
        }
    }
    
    // Fill the remaining unused letters in the cipher sequence
    for (i = 0; i < 26; i++) {
        if (cipherSeq[i] != '*')
            cipherSeq[i] = 'A' + index++;
    }
}

// Function to encrypt the plaintext using the generated cipher sequence
void encrypt(char plaintext[], char keyword[]) {
    char cipherSeq[26];
    int i;
    generateCipherSequence(keyword, cipherSeq);
    
    // Encrypt the plaintext using the generated cipher sequence
    for ( i = 0; i < strlen(plaintext); i++) {
        if (isalpha(plaintext[i])) {
            int index = toupper(plaintext[i]) - 'A';
            if (islower(plaintext[i]))
                printf("%c", tolower(cipherSeq[index]));
            else
                printf("%c", cipherSeq[index]);
        } else {
            printf("%c", plaintext[i]); // Non-alphabetic characters remain unchanged
        }
    }
    printf("\n");
}

int main() {
    char plaintext[] = "Hello, World!";
    char keyword[] = "CIPHER";
    
    printf("Plaintext: %s\n", plaintext);
    printf("Keyword: %s\n", keyword);
    printf("Encrypted text: ");
    encrypt(plaintext, keyword);
    
    return 0;
}

