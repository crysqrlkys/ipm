//
// Created by whyko on 05.10.2019.
//

#ifndef DES_DES3_H
#define DES_DES3_H


#include "DES.h"

class DES3
{
public:
    DES3(string key1, string key2, string key3);
    string encrypt(string block);
    string decrypt(string block);
private:
    DES des1;
    DES des2;
    DES des3;
};


#endif //DES_DES3_H
