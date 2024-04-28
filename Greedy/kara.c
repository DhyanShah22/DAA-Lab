#include<stdio.h>
#include<math.h>

int numDigits(long num){
    int count =0;
    while(num != 0){
        num /= 10;
        count++;
    }
    return count;
}

long karatsuba(long A, long B){
    if(A<10 && B<10){
        return A*B;
    }

    int size = fmax(numDigits(A), numDigits(B));
    if(size<10){
        return A*B;
    }

    size = size /2 + size % 2;
    long multiplier = pow(10, size);
    long b = A /multiplier;
    long a = A -(b * multiplier);
    long d = B / multiplier;
    long c = B - (d * multiplier);
    long u = karatsuba(a,c);
    long z = karatsuba((a+b),(d+c));
    long v = karatsuba(b,d);

    return u + ((z - u - v) * multiplier) + (v * (long)(pow(10, 2 * size)));

}
int main() {
    long num1;
    long num2;
    printf("Enter the first number: ");
    scanf("%ld", &num1);

    printf("Enter the last number: ");
    scanf("%ld", &num2);

    printf("The final product is: %ld\n", karatsuba(num1, num2));
    return 0;
}