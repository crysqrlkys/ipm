#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>
#include "utils.h"
#include "DES.h"

using namespace std;


int main() {
    string plainText, key;

    ifstream inFile;
    inFile.open("/home/whyko/CLionProjects/ipm/des/input.txt");
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

    int desChoice;
    cout << "Which DES? [1/2/3]" << endl;
    cin >> desChoice;
    if (desChoice<1 || desChoice>3){
        cout << "Wrong des algorithm" << endl;
        return -1;
    }

    char question;
    cout << "Input key by hand? y/n - ";
    cin >> question;
    if (question == 'y') {
        while (true) {
            cout << "Enter the key " << endl;
            cin >> key;
            bool check = inputVerifier(key, desChoice);
            if (check) break;
            else {
                cout << "Wrong Input" << endl;
            }
        }
    } else {
        switch (desChoice) {
            case 1:
                key = "12345678";
                break;
            case 2:
                key = "1234567812345678";
                break;
            case 3:
                key = "123456781234567812345678";
                break;
        }
    }

    cout << "Plain text:" << endl;
    cout << plainText << endl;
    vector<DES> deses;
    string encryptedText;
    for (vector<string>::const_iterator i = encodeBlocks.begin(); i != encodeBlocks.end(); ++i) {
        //cout << *i << endl;
        string desString = *i;

        string binKey = textToBinaryString(key);

        DES des(binKey);

        string binaryEncryptedBlock = des.encrypt(desString);
        deses.push_back(des);
        encryptedText += binaryEncryptedBlock;
    }
    cout << "Encrypted Text: " << endl;
    cout << binaryToString(encryptedText) << endl;

    vector<string> decodeBlocks = getBlocks(encryptedText);
    string decryptedText;
    int count = 0;
    for (vector<string>::const_iterator i = decodeBlocks.begin(); i != decodeBlocks.end(); ++i) {
        //cout << *i << endl;
        string desString = *i;

        DES des = deses[count];
        string binKey = textToBinaryString(key);
        string binaryEncryptedBlock = des.decrypt(desString);
        decryptedText += binaryEncryptedBlock;
        count++;
    }

    cout << "Decrypted text: " << endl;
    cout << binaryToString(decryptedText) << endl;

    return 0;
}



