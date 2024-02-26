// Function to encrypt the plaintext using the Playfair matrix
void encryptPlayfair(char message[], char key[5][5]) {
    int i; // Declare loop variable
    
    // Loop through each pair of characters in the message
    for (i = 0; i < strlen(message); i += 2) {
        char c1 = message[i];
        char c2 = (i + 1 < strlen(message)) ? message[i + 1] : 'X'; // If message length is odd, append 'X' to the last character
        
        // Find the positions of the characters in the Playfair matrix
        int row,col, row1, col1, row2, col2;
        int i;
        for (row = 0; row < 5; row++) {
            for ( col = 0; col < 5; col++) {
                if (key[row][col] == c1 || (c1 == 'I' && key[row][col] == 'J')) {
                    row1 = row;
                    col1 = col;
                }
                if (key[row][col] == c2 || (c2 == 'I' && key[row][col] == 'J')) {
                    row2 = row;
                    col2 = col;
                }
            }
        }
        
        // Encrypt the pair of characters
        if (row1 == row2) {
            // Characters are in the same row
            printf("%c%c", key[row1][(col1 + 1) % 5], key[row2][(col2 + 1) % 5]);
        } else if (col1 == col2) {
            // Characters are in the same column
            printf("%c%c", key[(row1 + 1) % 5][col1], key[(row2 + 1) % 5][col2]);
        } else {
            // Characters form a rectangle
            printf("%c%c", key[row1][col2], key[row2][col1]);
        }
    }
    printf("\n");
}

