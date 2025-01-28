#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long modular_exponentiation(long long base, long long exp, long long mod) {
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
    long long p, e1, e2, r, d, c1, c2, plaintext, decrypted;

    
    printf("Enter a large prime number (p): ");
    scanf("%lld", &p);

   
    printf("Enter primitive root modulo p (e1): ");
    scanf("%lld", &e1);

    
    printf("Enter private key (d): ");
    scanf("%lld", &d);

    
    e2 = modular_exponentiation(e1, d, p);
    printf("Computed public key e2: %lld\n", e2);

    
    printf("Enter random integer (r): ");
    scanf("%lld", &r);

    
    printf("Enter plaintext (integer): ");
    scanf("%lld", &plaintext);

    
    c1 = modular_exponentiation(e1, r, p);

    
    c2 = (modular_exponentiation(e2, r, p) * plaintext) % p;

    printf("Encrypted values: c1 = %lld, c2 = %lld\n", c1, c2);

   
    long long c1_d = modular_exponentiation(c1, d, p); 
    long long c1_d_inv = modular_exponentiation(c1_d, p - 2, p);
    decrypted = (c2 * c1_d_inv) % p;

    printf("Decrypted plaintext: %lld\n", decrypted);
    return 0;
}

// Output
// Enter a large prime number (p): 11
// Enter primitive root modulo p (e1): 2
// Enter private key (d): 3
// Computed public key e2: 8
// Enter random integer (r): 4
// Enter plaintext (integer): 7
// Encrypted values: c1 = 5, c2 = 6
// Decrypted plaintext: 7