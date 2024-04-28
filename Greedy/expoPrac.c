#include<stdio.h>

int Exponent(int base, int exp) {
    int result =1;
    while(exp > 0){
        if(exp % 2 ==1 ){
            result *=base;
        }
        base *= base;
        exp /= 2;
    }
    return result;
}

int main() {
    int base;
    int exponent;
    printf("Enter the base: ");
    scanf("%d", &base);

    printf("Enter the exponent: ");
    scanf("%d", &exponent);

    int  result = Exponent(base, exponent);
    printf("\nResult is %d\n", result);

    return 0;
}