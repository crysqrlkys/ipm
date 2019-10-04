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
    //by hand
    //cout << "Enter plain text" << endl;
    //cin >> plainText;

    ifstream inFile;
    inFile.open("/home/whyko/CLionProjects/ipm/des/input.txt");

    stringstream strStream;
    strStream << inFile.rdbuf(); //read the file
    plainText = strStream.str();

    string binaryString = TextToBinaryString(plainText);

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
    cout << "Y/N" << endl;
    cin >> question;
    if (question == 'y') {
        while (true) {
            cout << "Enter the key " << endl;
            cin >> key;
            bool check = input_verifier(key);
            if (check) break;
            else {
                cout << "Wrong Input" << endl;
            }
        }
    } else {
        key = "12345678";
    }

    cout << "Plain text:" << endl;
    cout << plainText << endl;
    vector<DES> deses;
    vector<string> poprikoly;
    string encryptedText;
    for (vector<string>::const_iterator i = encodeBlocks.begin(); i != encodeBlocks.end(); ++i) {
        cout << *i << endl;
        string desString = *i;

        string binKey = TextToBinaryString(key);
        string binString = desString;

        DES des(binKey);

        string binaryEncryptedBlock = des.encrypt(binString);
        deses.push_back(des);
        poprikoly.push_back(BinaryToString(binaryEncryptedBlock));
        encryptedText += binaryEncryptedBlock;
    }
    cout << BinaryToString(encryptedText) << endl;

    vector<string> decodeBlocks = getBlocks(encryptedText);
    string decryptedText;
    int count = 0;
    for (vector<string>::const_iterator i = decodeBlocks.begin(); i != decodeBlocks.end(); ++i) {
        cout << *i << endl;
        string desString = *i;

        DES des = deses[count];
        string binKey = TextToBinaryString(key);
        string encString = desString;
        string binaryEncryptedBlock = des.decrypt(desString);
        decryptedText += binaryEncryptedBlock;
        count++;
    }

    cout << BinaryToString(decryptedText) << endl;

    return 0;
}



