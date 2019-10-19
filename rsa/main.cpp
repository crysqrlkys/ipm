#include <iostream>
#include <vector>
#include <sstream>
#include <codecvt>
#include <fstream>
#include "RSA.h"

using namespace std;

int main() {
    string plainText;
    ifstream inFile;
    inFile.open("../input.txt");
    stringstream strStream;
    strStream << inFile.rdbuf();
    plainText = strStream.str();
    vector<char> bytes(plainText.begin(), plainText.end());

    RSA rsa;
    Key key = rsa.generateKeys();
    cout << "Keys：" << endl;
    cout << "Public key： {" << key.publicKey << "; " << key.N << "}" << endl;
    cout << "Private key： {" << key.privateKey << "; " << key.N << "}" << endl;

    string encText;

    for (auto msg : bytes) {
        long encodedText = rsa.cipher(msg, key.publicKey, key.N);
        encText += to_string(encodedText) + ' ';
    }

    cout << "Encoded Text" << endl;
    cout << encText << endl;

    vector<long> values;

    stringstream stream(encText);
    long n;
    while (stream >> n) {
        values.push_back(n);
    }
    string decText;
    for (auto encMsg : values) {
        long decodedText = rsa.cipher(encMsg, key.privateKey, key.N);
        decText += decodedText;
    }

    cout << "Decoded Text" << endl;
    cout << decText << endl;

    return 0;
}