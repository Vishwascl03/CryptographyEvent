#include <stdio.h>
#include <string.h>
#include <ctype.h>

int mod_inverse(int a, int m) {
    for (int i = 1; i < m; i++) {
        if ((a * i) % m == 1) {
            return i;
        }
    }
    return -1;
}

void encrypt(char *plaintext, int a, int b, char *ciphertext) {
    int m = 26; 

    for (int i = 0; i < strlen(plaintext); i++) {
        if (isalpha(plaintext[i])) {
            int isLower = islower(plaintext[i]);
            ciphertext[i] = ((a * (plaintext[i] - (isLower ? 'a' : 'A')) + b) % m) + (isLower ? 'a' : 'A');
        } else {
            ciphertext[i] = plaintext[i]; 
        }
    }
    ciphertext[strlen(plaintext)] = '\0'; 
}

void decrypt(char *ciphertext, int a, int b, char *plaintext) {
    int m = 26; 
    int a_inverse = mod_inverse(a, m);

    if (a_inverse == -1) {
        printf("Error: 'a' has no modular inverse under modulo 26.\n");
        return;
    }

    for (int i = 0; i < strlen(ciphertext); i++) {
        if (isalpha(ciphertext[i])) {
            int isLower = islower(ciphertext[i]);
            
            plaintext[i] = (a_inverse * ((ciphertext[i] - (isLower ? 'a' : 'A') - b + m) % m) % m) + (isLower ? 'a' : 'A');
        } else {
            plaintext[i] = ciphertext[i]; 
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    char plaintext[100], ciphertext[100], decryptedText[100];
    int a, b;

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 

    printf("Enter the key 'a' (must be coprime with 26): ");
    scanf("%d", &a);
    printf("Enter the key 'b': ");
    scanf("%d", &b);

    if (mod_inverse(a, 26) == -1) {
        printf("Error: Key 'a' is not coprime with 26. Please choose another value.\n");
        return 1;
    }

    encrypt(plaintext, a, b, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);

    decrypt(ciphertext, a, b, decryptedText);
    printf("Decrypted text: %s\n", decryptedText);

    return 0;
}

// Output
// Enter the plaintext: HELLOVISHWAS
// Enter the key 'a' (must be coprime with 26): 5
// Enter the key 'b': 12
// Encrypted text: VGPPENAYVSMY
// Decrypted text: HELLOVISHWAS