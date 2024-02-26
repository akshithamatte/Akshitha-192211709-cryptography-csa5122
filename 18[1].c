#include <stdio.h>
#include <stdint.h>

// Function prototypes
void generateSubkeys(uint64_t key, uint64_t subkeys[]);
uint64_t permute(uint64_t input, const int *table, int table_size);
void printSubkeys(uint64_t subkeys[]);

// Define the initial permutation table (PC-1)
int PC_1[] = {57, 49, 41, 33, 25, 17, 9,
              1, 58, 50, 42, 34, 26, 18,
              10, 2, 59, 51, 43, 35, 27,
              19, 11, 3, 60, 52, 44, 36,
              63, 55, 47, 39, 31, 23, 15,
              7, 62, 54, 46, 38, 30, 22,
              14, 6, 61, 53, 45, 37, 29,
              21, 13, 5, 28, 20, 12, 4};

// Define the permutation table for the key schedule (PC-2)
int PC_2[] = {14, 17, 11, 24, 1, 5, 3, 28,
              15, 6, 21, 10, 23, 19, 12, 4,
              26, 8, 16, 7, 27, 20, 13, 2,
              41, 52, 31, 37, 47, 55, 30, 40,
              51, 45, 33, 48, 44, 49, 39, 56,
              34, 53, 46, 42, 50, 36, 29, 32};

int main() {
    // Initial key (64 bits)
    uint64_t key = 0x133457799BBCDFF1; // Example key

    // Array to store subkeys (48 bits each)
    uint64_t subkeys[16];

    // Generate subkeys
    generateSubkeys(key, subkeys);

    // Print subkeys
    printf("Subkeys:\n");
    printSubkeys(subkeys);

    return 0;
}

// Function to generate subkeys for DES
void generateSubkeys(uint64_t key, uint64_t subkeys[]) {
    // Apply permutation PC-1 to the key
    uint64_t permuted_key = permute(key, PC_1, 56);

    // Split the 56-bit permuted key into two 28-bit halves
    uint32_t C = (permuted_key >> 28) & 0xFFFFFFF;
    uint32_t D = permuted_key & 0xFFFFFFF;

    // Key schedule: generate 16 subkeys
    int i;
    for (i = 0; i < 16; i++) {
        // Apply left circular shift to C and D
        int shift_amount = (i < 2 || i == 8 || i == 15) ? 1 : 2; // First 24 bits come from the same subset
        C = ((C << shift_amount) | (C >> (28 - shift_amount))) & 0xFFFFFFF;
        D = ((D << shift_amount) | (D >> (28 - shift_amount))) & 0xFFFFFFF;

        // Combine C and D into a 56-bit value
        uint64_t combined_cd = ((uint64_t)C << 28) | D;

        // Apply permutation PC-2 to obtain subkey
        subkeys[i] = permute(combined_cd, PC_2, 48);
    }
}

// Function to perform permutation using a given permutation table
uint64_t permute(uint64_t input, const int *table, int table_size) {
    uint64_t output = 0;
    int i;
    for (i = 0; i < table_size; i++) {
        output <<= 1;
        output |= (input >> (64 - table[i])) & 1;
    }
    return output;
}

// Function to print the subkeys
void printSubkeys(uint64_t subkeys[]) {
    int i;
    for (i = 0; i < 16; i++) {
        printf("Subkey %2d: 0x%012lx\n", i + 1, subkeys[i]);
    }
}

