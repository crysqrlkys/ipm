//
// Created by whyko on 04.10.2019.
//

#ifndef DES_DES_H
#define DES_DES_H

#include <cstdint>
using namespace std;

#define uint64 uint64_t
#define uint32 uint32_t
#define uint8  uint8_t

class DES
{
public:
    DES(uint64 key);
    uint64 des(uint64 block, bool mode);

    uint64 encrypt(uint64 block);
    uint64 decrypt(uint64 block);

    static uint64 encrypt(uint64 block, uint64 key);
    static uint64 decrypt(uint64 block, uint64 key);

protected:
    void keygen(uint64 key);

    uint64 ip(uint64 block);
    uint64 fp(uint64 block);

    void feistel(uint32 &L, uint32 &R, uint32 F);
    uint32 f(uint32 R, uint64 k);

private:
    uint64 sub_key[16];
};

#endif //DES_DES_H
