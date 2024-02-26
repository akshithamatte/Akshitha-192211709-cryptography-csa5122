#include <stdio.h>
#include <string.h>

void encrypt_3des_cbc(const char *input, const char *key, const char *iv, char *output) {
    DES_cblock desKey1, desKey2, desKey3, desIV;
    DES_key_schedule ks1, ks2, ks3;

    // Set the keys
    memcpy(desKey1, key, 8);
    memcpy(desKey2, key + 8, 8);
    memcpy(desKey3, key + 16, 8);

    // Set the IV
    memcpy(desIV, iv, 8);

    // Set encryption keys
    DES_set_key(&desKey1, &ks1);
    DES_set_key(&desKey2, &ks2);
    DES_set_key(&desKey3, &ks3);

    // Initialize the previous block with IV
    DES_cblock previousBlock;
    memcpy(previousBlock, desIV, 8);

    int inputLen = strlen(input);
    DES_cblock block;
    char encryptedBlock[8];

    for (int i = 0; i < inputLen; i += 8) {
        // XOR the current block with the previous ciphertext block
        memcpy(block, input + i, 8);
        DES_cblock xorResult;
        DES_ncbc_encrypt(&block, encryptedBlock, 8, &ks1, &previousBlock, DES_ENCRYPT);

        // Update the previous block with the current ciphertext block
        memcpy(previousBlock, encryptedBlock, 8);

        // Copy the result to the output
        memcpy(output + i, encryptedBlock, 8);
    }

    output[inputLen] = '\0';  // Null-terminate the output
}

int main() {
    const char *input = "Hello123";
    const char *key = "0123456789abcdef0123456789abcdef0123456789abcdef";
    const char *iv = "abcdefgh";
    char output[64];  // Output buffer should be large enough

    encrypt_3des_cbc(input, key, iv, output);

    printf("Original: %s\n", input);
    printf("Encrypted: %s\n", output);

    return 0;
}
