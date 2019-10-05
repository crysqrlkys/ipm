//
// Created by whyko on 04.10.2019.
//

#include <iostream>
#include <string>
#include <bitset>
#include <sstream>
#include <vector>
#include <cmath>
#include "utils.h"

using namespace std;

char *itoa(int value, char *result, int base) {
    // check that the base if valid
    if (base < 2 || base > 36) {
        *result = '\0';
        return result;
    }

    char *ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 +
                                                                                           (tmp_value - value * base)];
    } while (value);

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

string binaryToString(const string &binaryString) {
    stringstream sstream(binaryString);
    string text;
    while (sstream.good()) {
        bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        if (c != 0) {
            text += c;
        }
    }
    return text;
}

string textToBinaryString(const string &text) {
    string binaryString;
    for (size_t i = 0; i < text.size(); i++) {
        binaryString += bitset<8>(text.c_str()[i]).to_string();
    }
    return binaryString;
}

int binaryToDecimal(string bin) {
    int dec = 0, incr = 0, sum = 0;
    for (int i = (bin.length() - 1); i >= 0; i--) {
        dec = bin[i] - '0';
        sum = sum + (int) (dec * (pow(2, incr)));
        incr++;
    }
    return sum;
}

string decimalToBinary(int dec) {
    int i = dec;
    string str = "";
    char binary[4];
    while (1) {
        int quotient = i / 2;
        int remainder = i % 2;
        i = quotient;
        itoa(remainder, binary, 10);
        str = str + binary;
        if (quotient == 0)break;
    }
    string fin_str = "";
    for (int i = (str.length() - 1); i >= 0; i--) {
        fin_str = fin_str + str[i];
    }
    return fin_str;
}

bool inputVerifier(const string &message, int count) {
    return message.length() == 8 * count;
}

vector <string> getBlocks(string &binaryString) {
    vector <string> blocks;
    string word;
    for (char _char : binaryString) {
        word += _char;
        if (word.length() == 64) {
            blocks.push_back(word);
            word = "";
        }
    }
    return blocks;
}

void logToConsole(bool isEnabled, const string& message, const string& value){
    if (isEnabled){
        cout << message << value << endl;
    }
}

