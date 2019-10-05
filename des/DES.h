//
// Created by whyko on 04.10.2019.
//

#ifndef DES_DES_H
#define DES_DES_H

#include <string>
using namespace std;

class DES {
public:
    DES(string key);
    string des(string message, bool encrypt);
    string encrypt(string block);
    string decrypt(string block);

protected:
    static string rolKeys(string key, int i);
    static string getKey56(string key);
    static string getKeys48(string C, string D);
    string processString(string substring, int p);
    string expandedMessage(string R);
    string xoredMessage(string epMsg, string feKey);
    string substitutionFunction(string xoredMessage);
    void keygen(string fs_key);
    static string ip(string block);
    static string fp(string reversedMsg);

private:
    string sub_key[16];
};

#endif //DES_DES_H
