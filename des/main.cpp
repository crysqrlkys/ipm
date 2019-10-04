#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "utils.h"
#include "DES.h"

using namespace std;


int main() {
    string plainText, key;
    cout << "Enter plain text" << endl;
    cin >> plainText;
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

    string binaryEncodedText;

    string binKey = TextToBinaryString(key);
    DES des(binKey);
    string binString = TextToBinaryString(plainText);
    string encT = des.encrypt(binaryString);
    cout << encT << endl;
    cout << BinaryToString(encT) << endl;

    cout << BinaryToString(des.decrypt(encT));

//    for (vector<string>::const_iterator i = encodeBlocks.begin(); i != encodeBlocks.end(); ++i) {
//        cout << *i << endl;
//        string desString = *i;
//
//        string binString = TextToBinaryString(desString);
//        string binKey = TextToBinaryString(key);
//        string enc_msg = des_process(binString, binKey, true);
//        cout << "DES Encrypted Message:" << BinaryToString(enc_msg) << endl;
//        binaryEncodedText += enc_msg;
//    }
//
//    cout << "Encrypted text:" << endl;
//    string encodedText;
//    encodedText = BinaryToString(binaryEncodedText);
//    cout << encodedText << endl;
//
//    vector<string> decodeBlocks;
//    decodeBlocks = getBlocks(binaryEncodedText);
//    string decodedText;
//    for (vector<string>::const_iterator i = decodeBlocks.begin(); i != decodeBlocks.end(); ++i) {
//        string desString = *i;
//        string binString = TextToBinaryString(desString);
//        string binKey = TextToBinaryString(key);
//
//        string de_msg = des_process(desString, binKey, false);
//
//        cout << "DES Decrypted Message:" << BinaryToString(de_msg) << endl;
//        decodedText += de_msg;
//    }
//    cout << "Decrypted text:" << endl;
//    cout << decodedText;
    return 0;
}



