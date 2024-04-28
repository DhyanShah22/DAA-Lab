#include <stdio.h>
#include <math.h>

int numDigits(long num) {
    int count = 0;
    while (num != 0) {
        num /= 10;
        count++;
    }
    return count;
}

long karatsuba(long X, long Y) {
    if (X < 10 && Y < 10)
        return X * Y;

    int size = fmax(numDigits(X), numDigits(Y));
    if (size < 10)
        return X * Y;

    size = (size / 2) + (size % 2);
    long multiplier = pow(10, size);
    long b = X / multiplier;
    long a = X - (b * multiplier);
    long d = Y / multiplier;
    long c = Y - (d * multiplier);
    long u = karatsuba(a, c);
    long z = karatsuba(a + b, c + d);
    long v = karatsuba(b, d);
    return u + ((z - u - v) * multiplier) + (v * (long)(pow(10, 2 * size)));
}

int main() {
    long x = 999999;
    long y = 99;
    printf("The final product is: %ld\n", karatsuba(x, y));
    return 0;
}
