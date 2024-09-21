#ifndef DES_H
#define DES_H

#include <vector>
#include <cstdint>

class DES {
public:
    DES(const std::vector<uint8_t>& key);
    std::vector<uint8_t> encrypt(const std::vector<uint8_t>& plaintext);
    std::vector<uint8_t> decrypt(const std::vector<uint8_t>& ciphertext);

private:
    void initKey(const std::vector<uint8_t>& key);
    void permute(std::vector<uint8_t>& data, const std::vector<uint8_t>& permutation);
    void applyFFunction(std::vector<uint8_t>& data, const std::vector<uint8_t>& subkey);
    std::vector<uint8_t> generateSubkey(int round);

    std::vector<uint8_t> key;
};

#endif // DES_H
