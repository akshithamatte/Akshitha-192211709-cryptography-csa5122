#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void ecb_mode();
void cbc_mode();
void cfb_mode();

int main() {
    ecb_mode();
    cbc_mode();
    cfb_mode();
    
    return 0;
}

void ecb_mode() {
    // ECB mode implementation
    printf("ECB Mode\n");
    // Add your ECB mode code here
}

void cbc_mode() {
    // CBC mode implementation
    printf("CBC Mode\n");
    // Add your CBC mode code here
}

void cfb_mode() {
    // CFB mode implementation
    printf("CFB Mode\n");
    // Add your CFB mode code here
}
