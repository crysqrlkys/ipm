//
// Created by whyko on 05.10.2019.
//

#include "DES3.h"

DES3::DES3(string key1, string key2, string key3) :
        des1(key1),
        des2(key2),
        des3(key3)
{}

string DES3::encrypt(string block) {
    return des3.encrypt(des2.decrypt(des1.encrypt(block)));
}

string DES3::decrypt(string block) {
    return des1.decrypt(des2.encrypt(des3.decrypt(block)));
}