//
// Created by whyko on 05.10.2019.
//

#ifndef DES_DES2_H
#define DES_DES2_H

#include "DES.h"

class DES2 {
public:
    DES2(string key1, string key2);
    string encrypt(string block);
    string decrypt(string block);
private:
    DES des1;
    DES des2;
};

#endif //DES_DES2_H
