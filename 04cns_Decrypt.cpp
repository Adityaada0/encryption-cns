#include <bits/stdc++.h>
using namespace std;

string decryptRailFence(string cipher, int key) {
    char rail[key][cipher.length()];
    for (int i = 0; i < key; i++)
        for (int j = 0; j < cipher.length(); j++)
            rail[i][j] = '\n';

    bool dir_down = false;
    int row = 0, col = 0;
    for (int i = 0; i < cipher.length(); i++) {
        if (row == 0 || row == key - 1)
            dir_down = !dir_down;
        rail[row][col++] = '*'; // Mark spots with '*'
        dir_down ? row++ : row--;
    }

    int index = 0;
    for (int i = 0; i < key; i++)
        for (int j = 0; j < cipher.length(); j++)
            if (rail[i][j] == '*')
                rail[i][j] = cipher[index++];

    string result;
    row = 0, col = 0;
    for (int i = 0; i < cipher.length(); i++) {
        result.push_back(rail[row][col++]);
        if (row == 0 || row == key - 1)
            dir_down = !dir_down;
        dir_down ? row++ : row--;
    }
    return result;
}

int main() {
    string encryptedText = "AywadtaAahri te";
    int key = 3;

    string decryptedText = decryptRailFence(encryptedText, key);
    cout << "Decrypted: " << decryptedText << endl;

    return 0;
}

