//
// Created by whyko on 04.10.2019.
//

#ifndef DES_DESCBC_H
#define DES_DESCBC_H

#include "DES.h"

class DESCBC
{
public:
    DESCBC(uint64 key, uint64 iv);
    uint64 encrypt(uint64 block);
    uint64 decrypt(uint64 block);
    void reset();

private:
    DES des;
    uint64 iv;
    uint64 last_block;
};


#endif //DES_DESCBC_H
