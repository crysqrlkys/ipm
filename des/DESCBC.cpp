//
// Created by whyko on 04.10.2019.
//

#include "DESCBC.h"

DESCBC::DESCBC(uint64 key, uint64 iv) :
        des(key),
        iv(iv),
        last_block(iv)
{
}

uint64 DESCBC::encrypt(uint64 block)
{
    last_block = des.encrypt(block ^ last_block);
    return last_block;
}

uint64 DESCBC::decrypt(uint64 block)
{
    uint64 result = des.decrypt(block) ^ last_block;
    last_block = block;
    return result;
}

void DESCBC::reset()
{
    last_block = iv;
}