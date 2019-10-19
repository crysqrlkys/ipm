//
// Created by whyko on 19.10.2019.
//

#include "RSA.h"
#include "utils.h"
#include <cstdlib>

using namespace std;

RSA::RSA()
= default;

RSA::~RSA()
= default;

long RSA::cipher(const long msg, const long key, const long pkey) {
    long msg_des = 1;
    long root = msg;
    long index = key;
    while (index) {
        if (index & 1)
            msg_des = (msg_des * root) % pkey;
        index >>= 1;
        root = (root * root) % pkey;
    }
    return msg_des;
}

Key RSA::generateKeys() {
    long prime1 = generatePrime();
    long prime2 = generatePrime();
    while (prime2 == prime1)
        prime2 = generatePrime();

    Key key;
    long eulerFunc = generateEulerFunc(prime1, prime2);
    key.N = calculateMul(prime1, prime2);
    key.publicKey = generatePublicKey(eulerFunc);
    key.privateKey = generatePrivateKey(key.publicKey, eulerFunc);
    return key;
}

long RSA::calculateMul(const long prime1, const long prime2) {
    return prime1 * prime2;
}

long RSA::generateEulerFunc(const long prime1, const long prime2) {
    return (prime1 - 1) * (prime2 - 1);
}

long RSA::generatePublicKey(long eul) {
    long ekey;
    while (true) {
        ekey = rand() % eul;
        if (ekey >= 2 && gcd(ekey, eul) == 1)
            break;
    }
    return ekey;
}

long RSA::generatePrivateKey(long ekey, long eul) {
    long dkey = eul / ekey;
    while (true) {
        if (((dkey * ekey) % eul) == 1)
            break;
        else
            ++dkey;
    }
    return dkey;
}

