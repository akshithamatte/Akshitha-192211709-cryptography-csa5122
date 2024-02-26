#include <stdio.h>
#include <string.h>

// Function to decrypt the ciphertext using a simple substitution algorithm
void decrypt(char ciphertext[]) {
    // Define the substitution key based on the analysis
    char key[128];
    strcpy(key, " ETAONISRHLDCUMFPGWYBVKXJQZ"); // Most common letters in English
    
    // Declare loop variable
    int i;
    
    // Loop through each character in the ciphertext
    for (i = 0; i < strlen(ciphertext); i++) {
        char c = ciphertext[i];
        if (c >= 'a' && c <= 'z') {
            // Convert lowercase letters to uppercase
            c -= 32;
        }
        if (c >= 'A' && c <= 'Z') {
            // Decrypt uppercase letters using the substitution key
            printf("%c", key[c - 'A']);
        } else {
            // Print non-alphabetic characters as they are
            printf("%c", c);
        }
    }
}

int main() {
    char ciphertext[] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83 (88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8* ;4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81 (‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?";
    
    printf("Decrypted message:\n");
    decrypt(ciphertext);
    
    return 0;
}

