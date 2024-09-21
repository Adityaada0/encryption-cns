#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}
int modExp(int base, int exp, int mod) {
    int result = 1;
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
bool isPrime(int num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}
int nextPrime(int start) {
    while (!isPrime(start)) {
        start++;
    }
    return start;
}
int generateKeys(int &n, int &e, int &d) {
    int p = 3;
    int q = 7;

    n = p * q;
    int phi = (p - 1) * (q - 1);

    e = 2;
    while (e < phi && gcd(e, phi) != 1) {
        e++;
    }
    int k = 1;
    while ((k * phi + 1) % e != 0) {
        k++;
    }
    d = (k * phi + 1) / e;
    return p, q;
}
int decrypt(int encryptedMessage, int d, int n) {
    return modExp(encryptedMessage, d, n);
}
int main() {
    srand(static_cast<unsigned int>(time(0)));
    int n, e, d;
    std::ifstream keyFile("rsa_keys.txt");
    if (keyFile.is_open()) {
        keyFile >> n >> e >> d;
        keyFile.close();
    } else {
        std::cerr << "Error opening key file\n";
        return 1;
    }
    int encryptedMessage = 12; 
    int decryptedMessage = decrypt(encryptedMessage, d, n);
    std::cout << "RSA Decryption:\n";
    std::cout << "Private Key (n, d): (" << n << ", " << d << ")\n";
    std::cout << "Encrypted Message: " << encryptedMessage << "\n";
    std::cout << "Decrypted Message: " << decryptedMessage << "\n";
    return 0;
}