#include <stdio.h>
#include <string.h>

// Simple XOR operation for blocks
void xor_blocks(const unsigned char *a, const unsigned char *b, unsigned char *result, size_t block_size) {
    for (size_t i = 0; i < block_size; ++i) {
        result[i] = a[i] ^ b[i];
    }
}

// Function to perform CBC MAC
void cbc_mac(const unsigned char *key, const unsigned char *message, size_t message_length, unsigned char *mac) {
    size_t block_size = 16; // Assuming a block size of 16 bytes
    unsigned char ivec[block_size]; // Initialization Vector
    unsigned char block[block_size];

    // Set the Initialization Vector (IV) to zero
    memset(ivec, 0, block_size);

    // Process each block of the message using simple XOR
    size_t i;
    for (i = 0; i < message_length; i += block_size) {
        // XOR the current block of the message with the previous ciphertext (or IV for the first block)
        xor_blocks(&message[i], ivec, block, block_size);

        // Copy the result to the IV for the next iteration
        memcpy(ivec, block, block_size);
    }

    // Copy the final MAC value to the output buffer
    memcpy(mac, ivec, block_size);
}

int main() {
    // Key for CBC MAC (128 bits)
    unsigned char key[16] = "0123456789ABCDEF";

    // One-block message X
    unsigned char message_single_block[16] = "HelloWorld123456";

    // Compute CBC MAC for one-block message
    unsigned char mac_single_block[16];
    cbc_mac(key, message_single_block, 16, mac_single_block);

    // Two-block message X || (X ? T)
    unsigned char message_two_blocks[32];
    memcpy(message_two_blocks, message_single_block, 16);

    // XOR the first block of X with the CBC MAC of X
    xor_blocks(message_single_block, mac_single_block, &message_two_blocks[16], 16);

    // Compute CBC MAC for the two-block message
    unsigned char mac_two_blocks[16];
    cbc_mac(key, message_two_blocks, 32, mac_two_blocks);

    // Print the CBC MAC for the one-block message
    printf("CBC MAC for one-block message: ");
    for (size_t i = 0; i < 16; ++i) {
        printf("%02X", mac_single_block[i]);
    }
    printf("\n");

    // Print the CBC MAC for the two-block message
    printf("CBC MAC for two-block message: ");
    for (size_t i = 0; i < 16; ++i) {
        printf("%02X", mac_two_blocks[i]);
    }
    printf("\n");

    return 0;
}

