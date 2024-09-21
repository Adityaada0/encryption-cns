#include <iostream>
#include <string>

std::string caesarEncrypt(const std::string& plaintext, int shift) {
    std::string encryptedText;
    
    for (char c : plaintext) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char encryptedChar = (c - base + shift) % 26 + base;
            encryptedText += encryptedChar;
        } else {
            encryptedText += c;
        }
    }
    
    return encryptedText;
}

int main() {
    std::string plaintext = "Aditya";
    int shift = 3;
    
    std::string encrypted = caesarEncrypt(plaintext, shift);
    std::cout << "Encrypted: " << encrypted << std::endl;
    
    return 0;
}
