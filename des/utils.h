//
// Created by whyko on 04.10.2019.
//

#ifndef DES_UTILS_H
#define DES_UTILS_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

char *itoa(int value, char *result, int base);
string BinaryToString(const string &binaryString);
string TextToBinaryString(const string &text);
int bin_to_dec(string bin);
string dec_to_bin(int dec);
bool input_verifier(const string &message);
vector <string> getBlocks(string &binaryString);
#endif //DES_UTILS_H
