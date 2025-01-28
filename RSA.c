#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int is_prime(long long n, int iterations) {
    if (n < 2) return 0;
    if (n == 2 || n == 3) return 1;
    if (n % 2 == 0) return 0;

    long long s = 0, d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }

    for (int i = 0; i < iterations; i++) {
        long long a = 2 + rand() % (n - 4);
        long long x = 1, temp = d;

        for (; temp > 0; temp /= 2) {
            if (temp % 2 == 1) x = (x * a) % n;
            a = (a * a) % n;
        }

        if (x == 1 || x == n - 1) continue;

        int is_composite = 1;
        for (long long j = 0; j < s - 1; j++) {
            x = (x * x) % n;
            if (x == n - 1) {
                is_composite = 0;
                break;
            }
        }

        if (is_composite) return 0;
    }
    return 1;
}

long long generate_large_prime() {
    long long prime;
    do {
        prime = rand() % 100000 + 10000; 
    } while (!is_prime(prime, 5));      
    return prime;
}

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    srand(time(NULL));

    long long p = generate_large_prime();
    long long q = generate_large_prime();
    while (p == q) { 
        q = generate_large_prime();
    }

    long long n = p * q;
    long long phi = (p - 1) * (q - 1);

    long long e;
    do {
        e = rand() % (phi - 2) + 2; 
    } while (gcd(e, phi) != 1);

    long long d = 0;
    for (long long k = 1; k < phi; k++) {
        if ((1 + k * phi) % e == 0) {
            d = (1 + k * phi) / e;
            break;
        }
    }

    printf("Generated Prime p: %lld\n", p);
    printf("Generated Prime q: %lld\n", q);
    printf("Public Key: (e = %lld, n = %lld)\n", e, n);
    printf("Private Key: (d = %lld, n = %lld)\n", d, n);

    char message[256];
    printf("Enter a message to encrypt: ");
    scanf("%s", message);

    long long encrypted[256];
    printf("Encrypted message: ");
    for (int i = 0; message[i] != '\0'; i++) {
        encrypted[i] = mod_exp((long long)message[i], e, n);
        printf("%lld ", encrypted[i]);
    }
    printf("\n");

    printf("Decrypted message: ");
    for (int i = 0; message[i] != '\0'; i++) {
        char decrypted_char = (char)mod_exp(encrypted[i], d, n);
        printf("%c", decrypted_char);
    }
    printf("\n");
    return 0;
}

//Output
// Generated Prime p: 32429
// Generated Prime q: 21799
// Public Key: (e = 31513, n = 706919771)
// Private Key: (d = 407435209, n = 706919771)
// Enter a message to encrypt: SHEISLISTENING
// Encrypted message: 525283347 534686148 392983059 240060037 525283347 602634667 240060037 525283347 388817816 392983059 6831066 240060037 6831066 385034831
// Decrypted message: SHEISLISTENING