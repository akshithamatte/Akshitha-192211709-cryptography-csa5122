#include <stdio.h>
#include <stdint.h>

// Initial permutation table
int initial_permutation_table[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

// Final permutation table
int final_permutation_table[64] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};

// Expansion table
int expansion_table[48] = {
    32, 1, 2, 3, 4, 5, 4, 5,
    6, 7, 8, 9, 8, 9, 10, 11,
    12, 13, 12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21, 20, 21,
    22, 23, 24, 25, 24, 25, 26, 27,
    28, 29, 28, 29, 30, 31, 32, 1
};

// Permutation table for P-box
int permutation_table_p[32] = {
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25
};

// S-boxes (substitution boxes)
int s_boxes[8][4][16] = {
    {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    },
    // More S-boxes...
};

// Initial permutation function
void initial_permutation(uint32_t *left, uint32_t *right, uint64_t input) {
    uint64_t permuted = 0;
    for (int i = 0; i < 64; ++i) {
        uint64_t bit = (input >> (64 - initial_permutation_table[i])) & 1;
        permuted |= bit << (63 - i);
    }
    *left = (uint32_t)(permuted >> 32);
    *right = (uint32_t)permuted;
}

// Final permutation function
uint64_t final_permutation(uint32_t left, uint32_t right) {
    uint64_t combined = ((uint64_t)left << 32) | right;
    uint64_t permuted = 0;
    for (int i = 0; i < 64; ++i) {
        uint64_t bit = (combined >> (64 - final_permutation_table[i])) & 1;
        permuted |= bit << (63 - i);
    }
    return permuted;
}

// DES decryption function
uint64_t des_decrypt(uint64_t input, uint64_t *keys) {
    uint32_t left, right, next_right, temp;

    initial_permutation(&left, &right, input);

    for (int i = 15; i >= 0; --i) {
        next_right = left;
        temp = ((right >> 16) | (right << 16)) ^ keys[i];
        left = right;
        right = next_right ^ temp;
    }

    return final_permutation(left, right);
}

int main() {
    // Example keys (K1, K2, ..., K16)
    uint64_t keys[16] = {0x0123456789ABCDEF, 0x0123456789ABCDEF, 0x0123456789ABCDEF, 0x0123456789ABCDEF,
                          0x0123456789ABCDEF, 0x0123456789ABCDEF, 0x0123456789ABCDEF, 0x0123456789ABCDEF,
                          0x0123456789ABCDEF, 0x0123456789ABCDEF, 0x0123456789ABCDEF, 0x0123456789ABCDEF,
                          0x0123456789ABCDEF, 0x0123456789ABCDEF, 0x0123456789ABCDEF, 0x0123456789ABCDEF};

    // Example ciphertext
    uint64_t ciphertext = 0x85E813540F0AB405;

    // Decrypt the ciphertext
    uint64_t plaintext = des_decrypt(ciphertext, keys);

    // Display the results
    printf("Ciphertext: 0x%016lX\n", ciphertext);
    printf("Plaintext : 0x%016lX\n", plaintext);

    return 0;
}
