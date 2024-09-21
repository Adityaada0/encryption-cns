#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip>

// Constants for SHA-1
const unsigned int K[4] = {0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6};
const unsigned int H0 = 0x67452301;
const unsigned int H1 = 0xEFCDAB89;
const unsigned int H2 = 0x98BADCFE;
const unsigned int H3 = 0x10325476;
const unsigned int H4 = 0xC3D2E1F0;

class SHA1 {
public:
    SHA1() {
        reset();
    }

    void update(const unsigned char* data, size_t length) {
        size_t index = (size_t)((bitcount[0] >> 3) & 63);
        bitcount[0] += (length << 3);
        if (bitcount[0] < (length << 3))
            bitcount[1]++;
        bitcount[1] += (length >> 29);

        size_t partLen = 64 - index;
        size_t i = 0;

        if (length >= partLen) {
            std::memcpy(buffer + index, data, partLen);
            transform(buffer);
            for (i = partLen; i + 63 < length; i += 64)
                transform(data + i);
            index = 0;
        } else {
            i = 0;
        }
        std::memcpy(buffer + index, data + i, length - i);
    }

    void finalize() {
        unsigned char bits[8];
        encode(bits, bitcount, 8);

        size_t index = (size_t)((bitcount[0] >> 3) & 63);
        size_t padLen = (index < 56) ? (56 - index) : (120 - index);

        static unsigned char padding[64] = {0x80};
        update(padding, padLen);
        update(bits, 8);

        encode(digest, state, 20);
    }

    const unsigned char* getDigest() const {
        return digest;
    }

private:
    unsigned int state[5];
    unsigned char buffer[64];
    unsigned int bitcount[2];
    unsigned char digest[20];

    void reset() {
        state[0] = H0;
        state[1] = H1;
        state[2] = H2;
        state[3] = H3;
        state[4] = H4;
        bitcount[0] = bitcount[1] = 0;
    }

    void transform(const unsigned char* data) {
        unsigned int W[80];
        unsigned int a, b, c, d, e;

        for (int i = 0; i < 16; ++i)
            W[i] = ((unsigned int)data[i * 4]) << 24 |
                   ((unsigned int)data[i * 4 + 1]) << 16 |
                   ((unsigned int)data[i * 4 + 2]) << 8 |
                   ((unsigned int)data[i * 4 + 3]);
        for (int i = 16; i < 80; ++i)
            W[i] = leftRotate(W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16], 1);

        a = state[0];
        b = state[1];
        c = state[2];
        d = state[3];
        e = state[4];

        for (int i = 0; i < 80; ++i) {
            unsigned int temp = leftRotate(a, 5) + e + W[i];
            if (i < 20)
                temp += ((b & c) | (~b & d)) + K[0];
            else if (i < 40)
                temp += (b ^ c ^ d) + K[1];
            else if (i < 60)
                temp += ((b & c) | (b & d) | (c & d)) + K[2];
            else
                temp += (b ^ c ^ d) + K[3];
            e = d;
            d = c;
            c = leftRotate(b, 30);
            b = a;
            a = temp;
        }

        state[0] += a;
        state[1] += b;
        state[2] += c;
        state[3] += d;
        state[4] += e;
    }

    unsigned int leftRotate(unsigned int value, unsigned int amount) {
        return (value << amount) | (value >> (32 - amount));
    }

    void encode(unsigned char* output, const unsigned int* input, size_t length) {
        for (size_t i = 0; i < length; ++i) {
            output[i * 4] = (unsigned char)(input[i] >> 24);
            output[i * 4 + 1] = (unsigned char)(input[i] >> 16);
            output[i * 4 + 2] = (unsigned char)(input[i] >> 8);
            output[i * 4 + 3] = (unsigned char)(input[i]);
        }
    }
};

int main() {
    SHA1 sha1;
    const char* data = "Hello, World!";
    sha1.update(reinterpret_cast<const unsigned char*>(data), strlen(data));
    sha1.finalize();

    const unsigned char* hash = sha1.getDigest();
    std::cout << "SHA-1 hash: ";
    for (int i = 0; i < 20; ++i)
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    std::cout << std::endl;

    return 0;
}
