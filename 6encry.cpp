#include <openssl/evp.h>
#include <openssl/err.h>  // For error handling
#include <iostream>
#include <cstring>

void handleErrors() {
    ERR_print_errors_fp(stderr);
    abort();
}

void desEncrypt(const unsigned char* plaintext, int plaintext_len, const unsigned char* key, unsigned char* ciphertext, int& ciphertext_len) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) handleErrors();

    // Initialize encryption operation
    if (EVP_EncryptInit_ex(ctx, EVP_des_ecb(), NULL, key, NULL) != 1) handleErrors();

    int len;
    if (EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len) != 1) handleErrors();
    ciphertext_len = len;

    if (EVP_EncryptFinal_ex(ctx, ciphertext + len, &len) != 1) handleErrors();
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);
}

int main() {
    unsigned char key[] = "ABCDEFGH";  // 8-byte DES key
    unsigned char plaintext[] = "HELLO!!"; // 8-byte block
    unsigned char ciphertext[128];
    int ciphertext_len;

    std::cout << "Original Plaintext: " << plaintext << std::endl;

    // Encrypt the plaintext
    desEncrypt(plaintext, strlen((char*)plaintext), key, ciphertext, ciphertext_len);

    // Print the encrypted ciphertext
    std::cout << "Encrypted Ciphertext: ";
    for (int i = 0; i < ciphertext_len; ++i) {
        printf("%02X ", ciphertext[i]);
    }
    std::cout << std::endl;

    return 0;
}
