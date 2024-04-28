#include <stdio.h>

int exponentiation(int base, int exponent) {
    int result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result *= base;
        }
        base *= base; 
        exponent /= 2; 
    }
    return result;
}

int main() {
    int base, exponent;
    printf("Enter the base: ");
    scanf("%d", &base);
    printf("Enter the exponent: ");
    scanf("%d", &exponent);
    
    int result = exponentiation(base, exponent);
    printf("%d raised to the power of %d is %d\n", base, exponent, result);

    return 0;
}
