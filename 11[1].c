#include <stdio.h>

// Function to calculate the factorial of a number
unsigned long long factorial(int n) {
    if (n == 0 || n == 1)
        return 1;
    else
        return n * factorial(n - 1);
}

int main() {
    int size = 5; // Size of the matrix
    unsigned long long unique_keys;

    // Calculate the unique arrangements of the first row
    unsigned long long first_row_arrangements = factorial(size);

    // Calculate the total number of effectively unique keys
    unique_keys = first_row_arrangements * factorial(size - 1);

    printf("The total number of effectively unique keys for Playfair cipher is approximately 2^%.0f\n", log2(unique_keys));

    return 0;
}
