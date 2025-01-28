#include <stdio.h>

int extended_gcd(int a, int b, int *x, int *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }

    int x1, y1; 
    int gcd = extended_gcd(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}

int main() {
    int a, b, x, y;

    printf("Enter two integers (a and b): ");
    scanf("%d %d", &a, &b);

    int gcd = extended_gcd(a, b, &x, &y);

    printf("GCD of %d and %d is: %d\n", a, b, gcd);
    printf("Coefficients x and y are: x = %d, y = %d\n", x, y);
    printf("Verification: %d * %d + %d * %d = %d\n", a, x, b, y, gcd);
    return 0;
}

// Output
// Enter two integers (a and b): 7 26
// GCD of 7 and 26 is: 1
// Coefficients x and y are: x = -11, y = 3
// Verification: 7 * -11 + 26 * 3 = 1