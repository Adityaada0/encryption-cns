#include <iostream>
#include <string>

std::string caesarDecrypt(const std::string& ciphertext, int shift) {
    std::string decryptedText;
    
    for (char c : ciphertext) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char decryptedChar = (c - base - shift + 26) % 26 + base;  // Adding 26 to ensure positive result
            decryptedText += decryptedChar;
        } else {
            decryptedText += c;
        }
    }
    
    return decryptedText;
}

int main() {
    std::string ciphertext = "Dglwbd Jrqgdqh";
    int shift = 3;
    
    std::string decrypted = caesarDecrypt(ciphertext, shift);
    std::cout << "Decrypted: " << decrypted << std::endl;
    
    return 0;
}
