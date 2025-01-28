#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char *plaintext, char *key, char *ciphertext) {
    int textLength = strlen(plaintext);
    int keyLength = strlen(key);
    int i, j = 0;

    for (i = 0; i < textLength; i++) {
        if (isalpha(plaintext[i])) {  
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = (plaintext[i] - base + (toupper(key[j % keyLength]) - 'A')) % 26 + base;
            j++;  
        } else {
            ciphertext[i] = plaintext[i];  
        }
    }
    ciphertext[textLength] = '\0'; 
}

void decrypt(char *ciphertext, char *key, char *plaintext) {
    int textLength = strlen(ciphertext);
    int keyLength = strlen(key);
    int i, j = 0;

    for (i = 0; i < textLength; i++) {
        if (isalpha(ciphertext[i])) {  
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = (ciphertext[i] - base - (toupper(key[j % keyLength]) - 'A') + 26) % 26 + base;
            j++; 
        } else {
            plaintext[i] = ciphertext[i];  
        }
    }
    plaintext[textLength] = '\0';  
}

int main() {
    char plaintext[256], key[256], ciphertext[256];
    int choice;

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; 

    printf("Choose an option:\n");
    printf("1. Encrypt\n");
    printf("2. Decrypt\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        encrypt(plaintext, key, ciphertext);
        printf("Ciphertext: %s\n", ciphertext);
    } else if (choice == 2) {
        decrypt(plaintext, key, ciphertext);
        printf("Decrypted text: %s\n", ciphertext);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}

//Output:
// Enter the plaintext: Hello
// Enter the key: Key
// Choose an option:
// 1. Encrypt
// 2. Decrypt
// Enter your choice: 1
// Ciphertext: Rijvs

// Enter the plaintext: Rijvs
// Enter the key: Key
// Choose an option:
// 1. Encrypt
// 2. Decrypt
// Enter your choice: 2
// Decrypted text: Hello