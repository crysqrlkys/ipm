//
// Created by whyko on 04.10.2019.
//

#include "DES.h"
#include "constants.h"

DES::DES(uint64 key)
{
    keygen(key);
}

uint64 DES::encrypt(uint64 block)
{
    return des(block, false);
}

uint64 DES::decrypt(uint64 block)
{
    return des(block, true);
}

uint64 DES::encrypt(uint64 block, uint64 key)
{
    DES des(key);
    return des.des(block, false);
}

uint64 DES::decrypt(uint64 block, uint64 key)
{
    DES des(key);
    return des.des(block, true);
}

void DES::keygen(uint64 key)
{
    uint64 permuted_choice_1 = 0;
    for (uint8 i = 0; i < 56; i++)
    {
        permuted_choice_1 <<= 1;
        permuted_choice_1 |= (key >> (64-PC1[i])) & LB64_MASK;
    }

    // 28 bits
    uint32 C = (uint32) ((permuted_choice_1 >> 28) & 0x000000000fffffff);
    uint32 D = (uint32)  (permuted_choice_1 & 0x000000000fffffff);

    // Calculation of the 16 keys
    for (uint8 i = 0; i < 16; i++)
    {
        // key schedule, shifting Ci and Di
        for (uint8 j = 0; j < ITERATION_SHIFT[i]; j++)
        {
            C = (0x0fffffff & (C << 1)) | (0x00000001 & (C >> 27));
            D = (0x0fffffff & (D << 1)) | (0x00000001 & (D >> 27));
        }

        uint64 permuted_choice_2 = (((uint64) C) << 28) | (uint64) D;

        sub_key[i] = 0; // 48 bits (2*24)
        for (uint8 j = 0; j < 48; j++)
        {
            sub_key[i] <<= 1;
            sub_key[i] |= (permuted_choice_2 >> (56-PC2[j])) & LB64_MASK;
        }
    }
}

uint64 DES::des(uint64 block, bool mode)
{
    block = ip(block);

    uint32 L = (uint32) (block >> 32) & L64_MASK;
    uint32 R = (uint32) (block & L64_MASK);

    for (uint8 i = 0; i < 16; i++)
    {
        uint32 F = mode ? f(R, sub_key[15 - i]) : f(R, sub_key[i]);
        feistel(L, R, F);
    }

    block = (((uint64) R) << 32) | (uint64) L;
    return fp(block);
}

uint64 DES::ip(uint64 block)
{
    uint64 result = 0;
    for (uint8 i = 0; i < 64; i++)
    {
        result <<= 1;
        result |= (block >> (64-IP[i])) & LB64_MASK;
    }
    return result;
}

uint64 DES::fp(uint64 block)
{
    uint64 result = 0;
    for (uint8 i = 0; i < 64; i++)
    {
        result <<= 1;
        result |= (block >> (64-FP[i])) & LB64_MASK;
    }
    return result;
}

void DES::feistel(uint32 &L, uint32 &R, uint32 F)
{
    uint32 temp = R;
    R = L ^ F;
    L = temp;
}

uint32 DES::f(uint32 R, uint64 k) // f(R,k) function
{
    uint64 s_input = 0;
    for (uint8 i = 0; i < 48; i++)
    {
        s_input <<= 1;
        s_input |= (uint64) ((R >> (32 - EXPANSION[i])) & LB32_MASK);
    }

    s_input = s_input ^ k;

    uint32 s_output = 0;
    for (uint8 i = 0; i < 8; i++)
    {
        char row = (char) ((s_input & (0x0000840000000000 >> 6*i)) >> (42-6*i));
        row = (row >> 4) | (row & 0x01);

        char column = (char) ((s_input & (0x0000780000000000 >> 6*i)) >> (43-6*i));

        s_output <<= 4;
        s_output |= (uint32) (SBOX[i][16 * row + column] & 0x0f);
    }

    uint32 f_result = 0;
    for (uint8 i = 0; i < 32; i++)
    {
        f_result <<= 1;
        f_result |= (s_output >> (32 - PBOX[i])) & LB32_MASK;
    }

    return f_result;
}