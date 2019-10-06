#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>
#include "utils.h"
#include "DES.h"
#include "DES2.h"
#include "DES3.h"

using namespace std;


int main() {
    string plainText, key;

    ifstream inFile;
    inFile.open("../input.txt");
    stringstream strStream;
    strStream << inFile.rdbuf();
    plainText = strStream.str();

    string binaryString = textToBinaryString(plainText);

    uint missingBitsCount = (64 - binaryString.length() % 64);
    string correctBinaryString;
    if (missingBitsCount != 64) {
        string missingBits(missingBitsCount, '0');
        correctBinaryString = missingBits + binaryString;
    } else {
        correctBinaryString = binaryString;
    }

    vector<string> encodeBlocks;
    encodeBlocks = getBlocks(correctBinaryString);

    char question;
    cout << "Input key by hand? y/n - ";
    cin >> question;
    if (question == 'y') {
        while (true) {
            cout << "Enter the key " << endl;
            cin >> key;
            bool check = inputVerifier(key, 3);
            if (check) break;
            else {
                cout << "Wrong Input" << endl;
            }
        }
    } else {
        key = "194726529875472846827124";
    }

    cout << "Plain text:" << endl;
    cout << plainText << endl << endl;

    string desEncryptedText;
    string doubleDesEncryptedText;
    string tripleDesEncryptedText;

    for (vector<string>::const_iterator i = encodeBlocks.begin(); i != encodeBlocks.end(); ++i) {
        //cout << *i << endl;
        string desString = *i;

        string binKey = textToBinaryString(key);

        string key1 = binKey.substr(0, 64);
        string key2 = binKey.substr(64, 64);
        string key3 = binKey.substr(128, 64);

        DES des(key1);
        DES2 des2(key1, key2);
        DES3 des3(key1, key2, key3);

        string desBinaryEncryptedBlock = des.encrypt(desString);
        string doubleDesBinaryEncryptedBlock = des2.encrypt(desString);
        string tripleDesBinaryEncryptedBlock = des3.encrypt(desString);

        desEncryptedText += desBinaryEncryptedBlock;
        doubleDesEncryptedText += doubleDesBinaryEncryptedBlock;
        tripleDesEncryptedText += tripleDesBinaryEncryptedBlock;
    }

    cout << "des: Encrypted Text: " << endl;
    cout << binaryToString(desEncryptedText) << endl << endl;

    cout << "2des: Encrypted Text: " << endl;
    cout << binaryToString(doubleDesEncryptedText) << endl << endl;

    cout << "3des: Encrypted Text: " << endl;
    cout << binaryToString(tripleDesEncryptedText) << endl << endl;

    vector<string> desDecodeBlocks = getBlocks(desEncryptedText);
    vector<string> doubleDesDecodeBlocks = getBlocks(doubleDesEncryptedText);
    vector<string> tripleDesDecodeBlocks = getBlocks(tripleDesEncryptedText);

    string desDecryptedText;

    for (vector<string>::const_iterator i = desDecodeBlocks.begin(); i != desDecodeBlocks.end(); ++i) {
        string desString = *i;
        string binKey = textToBinaryString(key);

        string key1 = binKey.substr(0, 64);
        DES des(key1);

        string desBinaryDecryptedBlock = des.decrypt(desString);
        desDecryptedText += desBinaryDecryptedBlock;
    }

    cout << "des: Decrypted text: " << endl;
    cout << binaryToString(desDecryptedText) << endl << endl;

    string doubleDesDecryptedText;

    for (vector<string>::const_iterator i = doubleDesDecodeBlocks.begin(); i != doubleDesDecodeBlocks.end(); ++i) {
        string desString = *i;
        string binKey = textToBinaryString(key);

        string key1 = binKey.substr(0, 64);
        string key2 = binKey.substr(64, 64);
        DES2 des2(key1, key2);

        string doubleDesBinaryDecryptedBlock = des2.decrypt(desString);
        doubleDesDecryptedText += doubleDesBinaryDecryptedBlock;
    }

    cout << "2des: Decrypted text: " << endl;
    cout << binaryToString(doubleDesDecryptedText) << endl << endl;

    string tripleDesDecryptedText;

    for (vector<string>::const_iterator i = tripleDesDecodeBlocks.begin(); i != tripleDesDecodeBlocks.end(); ++i) {
        string desString = *i;
        string binKey = textToBinaryString(key);

        string key1 = binKey.substr(0, 64);
        string key2 = binKey.substr(64, 64);
        string key3 = binKey.substr(128, 64);
        DES3 des3(key1, key2, key3);

        string tripleDesBinaryDecryptedBlock = des3.decrypt(desString);
        tripleDesDecryptedText += tripleDesBinaryDecryptedBlock;
    }

    cout << "3des: Decrypted text: " << endl;
    cout << binaryToString(tripleDesDecryptedText) << endl << endl;

    return 0;
}



