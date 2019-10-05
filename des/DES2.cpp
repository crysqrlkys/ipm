//
// Created by whyko on 05.10.2019.
//

#include "DES2.h"

DES2::DES2(string key1, string key2) :
    des1(key1),
    des2(key2)
{}

string DES2::encrypt(string block) {
    return des2.encrypt(des1.encrypt(block));
}

string DES2::decrypt(string block) {
    return des1.decrypt(des2.decrypt(block));
}