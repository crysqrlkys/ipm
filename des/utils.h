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
string binaryToString(const string &binaryString);
string textToBinaryString(const string &text);
int binaryToDecimal(string bin);
string decimalToBinary(int dec);
bool inputVerifier(const string &message, int count);
vector <string> getBlocks(string &binaryString);
void logToConsole(bool isEnabled, const string& message, const string& value);
#endif //DES_UTILS_H
