//
// Created by whyko on 19.10.2019.
//

#ifndef RSA_RSA_H
#define RSA_RSA_H

typedef struct key {
    long N;
    long publicKey;
    long privateKey;
} Key;

class RSA {
public:
    RSA();

    virtual ~RSA();

public:
    Key generateKeys();

    long cipher(long msg, long key, long pkey);

private:
    static long calculateMul(long prime1, long prime2);

    static long generatePublicKey(long eul);

    static long generatePrivateKey(long ekey, long eul);

    static long generateEulerFunc(long prime1, long prime2);
};

#endif //RSA_RSA_H
