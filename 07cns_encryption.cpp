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
void generateKeys(int &n, int &e, int &d, int p , int q) {
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
}
int encrypt(int message, int e, int n) {
    return modExp(message, e, n);
}
int main() {
    int p ,q ;
    std::cout << "Enter p: ";
    std::cin >> p;
    std::cout << "Enter q: ";
    std::cin >> q;
    srand(static_cast<unsigned int>(time(0)));
    int n, e, d;
    generateKeys(n, e, d, p, q);
    int message = 12; 
    int encryptedMessage = encrypt(message, e, n);

    std::ofstream keyFile("rsa_keys.txt");
    keyFile << n << '\n' << e << '\n' << d;
    keyFile.close();
    std::cout << "RSA Encryption:\n";
    std::cout << "Public Key (n, e): (" << n << ", " << e << ")\n";
    std::cout << "Encrypted Message: " << encryptedMessage << "\n";
    return 0;
}
