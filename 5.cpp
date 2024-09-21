#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::string columnarEncrypt(const std::string& plaintext, const std::string& keyword) {
    size_t numColumns = keyword.size();
    size_t numRows = (plaintext.size() + numColumns - 1) / numColumns;

    std::vector<std::vector<char>> grid(numRows, std::vector<char>(numColumns, ' '));
    for (size_t i = 0; i < plaintext.size(); ++i) {
        grid[i / numColumns][i % numColumns] = plaintext[i];
    }
    
    std::vector<int> colOrder(numColumns);
    for (size_t i = 0; i < numColumns; ++i) {
        colOrder[i] = i;
    }
    std::sort(colOrder.begin(), colOrder.end(), [&](int a, int b) {
        return keyword[a] < keyword[b];
    });
    
    std::string ciphertext;
    for (int col : colOrder) {
        for (size_t row = 0; row < numRows; ++row) {
            if (grid[row][col] != ' ') {
                ciphertext += grid[row][col];
            }
        }
    }
    return ciphertext;
}
int main() {
    std::string plaintext = "Aditya Gondane";
    std::string keyword = "KEY";
    std::string encrypted = columnarEncrypt(plaintext, keyword);
    std::cout << "Encrypted: " << encrypted << std::endl;
    return 0;
}
