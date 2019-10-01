#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <sstream>

using namespace std;


string BinaryToString(const string& binaryString){
    stringstream sstream(binaryString);
    string text;
    while(sstream.good()){
        bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        if (c != 0) {
            text += c;
        }
    }
    return  text;
}

string TextToBinaryString(const string& text){
    string binaryString;
    for (size_t i=0; i< text.size();i++){
        binaryString += bitset<8>(text.c_str()[i]).to_string();
    }
    return binaryString;
}

int main() {
    string plainText;
    cin >> plainText;
    string binaryString = TextToBinaryString(plainText);
    uint missingBitsCount = (64 - binaryString.length() % 64);

    string correctBinaryString;

    if (missingBitsCount != 64) {
        string missingBits(missingBitsCount, '0');
        correctBinaryString = missingBits + binaryString;
    }
    else {
        correctBinaryString = binaryString;
    }
    vector<string> blocks;
    string word;
    for (char _char : correctBinaryString){
        word += _char;
        if (word.length() == 64){
            blocks.push_back(word);
            word = "";
        }
    }

    string key = "ABCD123";
    string keyBinary = TextToBinaryString(key);

    for (vector<string>::const_iterator i = blocks.begin(); i!= blocks.end(); ++i){
        cout<< *i << endl;
        string desString = *i;

    }

    //string key;
    //cin >> key;
    //d 56 bit + 8
    //2d 112 bit + 16
    //3d 168 bit + 24

    return 0;
}