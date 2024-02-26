#include <stdio.h>
#include <string.h>

// Function to decrypt the Playfair code message
void decryptPlayfair(char message[]) {
    // Define the Playfair cipher key (5x5 matrix)
    char key[5][5] = {
        {'A', 'B', 'C', 'D', 'E'},
        {'F', 'G', 'H', 'I', 'K'},
        {'L', 'M', 'N', 'O', 'P'},
        {'Q', 'R', 'S', 'T', 'U'},
        {'V', 'W', 'X', 'Y', 'Z'}
    };
    
    // Declare loop variable
    int i;
    
    // Loop through each pair of characters in the message
    for (i = 0; i < strlen(message); i += 2) {
        char c1 = message[i];
        char c2 = message[i + 1];
        
        // Find the row and column of each character in the key
        int col,row,row1, col1, row2, col2;
        for ( row = 0; row < 5; row++) {
            for (col = 0; col < 5; col++) {
                if (key[row][col] == c1) {
                    row1 = row;
                    col1 = col;
                }
                if (key[row][col] == c2) {
                    row2 = row;
                    col2 = col;
                }
            }
        }
        
        // Decrypt the pair of characters
        if (row1 == row2) {
            // Characters are in the same row
            printf("%c%c", key[row1][(col1 - 1 + 5) % 5], key[row2][(col2 - 1 + 5) % 5]);
        } else if (col1 == col2) {
            // Characters are in the same column
            printf("%c%c", key[(row1 - 1 + 5) % 5][col1], key[(row2 - 1 + 5) % 5][col2]);
        } else {
            // Characters form a rectangle
            printf("%c%c", key[row1][col2], key[row2][col1]);
        }
    }
    printf("\n");
}

int main() {
    char message[] = "KXJEY UREBE ZWEHE WRYTU HEYFS KREHE GOYFI WTTTU OLKSY CAJPO BOTEI ZONTX BYBNT GONEY CUZWR GDSON SXBOU YWRHE BAAHY USEDQ";
    
    printf("Decrypted message:\n");
    decryptPlayfair(message);
    
    return 0;
}

