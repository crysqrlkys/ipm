#include <iostream>
#include <cmath>
#include <vector>
#include <tuple>
#include <unordered_set>


using namespace std;

class PublicKey {
public:
    PublicKey(long long _p, long long _g, long long _y, long long _iNumBits) {
        p = _p;
        g = _g;
        y = _y;
        iNumBits = _iNumBits;
    }

    long long iNumBits;
    long long p;
    long long g;
    long long y;
};

class PrivateKey {
public:
    PrivateKey(long long _p, long long _g, long long _x, long long _iNumBits) {
        p = _p;
        g = _g;
        x = _x;
        iNumBits = _iNumBits;
    }

    long long p;
    long long g;
    long long x;
    long long iNumBits;
};

long long gcd(long long a, long long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

bool isPrime(long long number) {
    if (number == 0) {
        return false;
    } else {
        for (int i = 2; i < number; i++)
            if (number % i == 0)
                return false;
    }
    return true;
}

long long modulo(long long base, long long exponent, long long mod) {
    long long x = 1;
    long long y = base;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            x = (x * y) % mod;
        }
        y = (y * y) % mod;
        exponent = exponent / 2;
    }
    return x % mod;
}

void findPrimefactors(unordered_set<int> &s, long long n) {
    while (n % 2 == 0) {
        s.insert(2);
        n = n / 2;
    }
    for (int i = 3; i <= sqrt(n); i = i + 2) {
        while (n % i == 0) {
            s.insert(i);
            n = n / i;
        }
    }

    if (n > 2)
        s.insert(n);
}

int findPrimitiveRoot(long long n) {
    unordered_set<int> s{};
    if (!isPrime(n))
        return -1;
    long long phi = n - 1;

    findPrimefactors(s, phi);

    for (long long root = 2; root <= phi; root++) {
        bool flag = false;
        for (auto it = s.begin(); it != s.end(); it++) {
            if (modulo(root, phi / (*it), n) == 1) {
                flag = true;
                break;
            }
        }

        if (!flag)
            return root;
    }
    return -1;
}

vector<long long> encode(string plainText, long long iNumBits) {
    vector<char> bytes(plainText.begin(), plainText.end());
    vector<long long> z;
    int k = iNumBits / 8;
    int j = -1 * k;

    for (vector<long long>::size_type i = 0; i != bytes.size(); i++) {
        if (i % k == 0) {
            j += k;
            z.push_back(0);
        }
        z[j / k] += bytes[i] * (pow(2, 8 * (i % k)));
    }
    return z;
}

string encrypt(PublicKey pk, string plaintText) {
    vector<long long> z = encode(plaintText, pk.iNumBits);
    vector<vector<long long>> cipher_pairs;
    for (auto const &i : z) {
        long long range = pk.p + 1;
        long long k = rand() % range;
        long long a = modulo(pk.g, k, pk.p);
        long long b = (i * modulo(pk.y, k, pk.p)) % pk.p;
        vector<long long> pair;
        pair.push_back(a);
        pair.push_back(b);
        cipher_pairs.push_back(pair);
    }
    string encText;
    for (auto const &pair : cipher_pairs) {
        encText += to_string(pair[0]) + " " + to_string(pair[1]) + " ";
    }
    return encText;
}

long long findPrime(long long min, long long max) {
    long long range = max - min + 1;
    while (true) {
        int r = rand() % range + min;
        if (isPrime(r)) return r;
    }
}

tuple<PublicKey, PrivateKey> generateKeys() {
    int iNumBits = 64;
    long long p = findPrime(100000, 1000000);
    long long g = findPrimitiveRoot(p);
    g = modulo(g, 2, p);
    long long x = rand() % (int) ((p - 1) / 2 - 1 + 1) + 1;
    long long y = modulo(g, x, p);
    PublicKey publicKey(p, g, y, iNumBits);
    PrivateKey privateKey(p, g, x, iNumBits);
    return make_tuple(publicKey, privateKey);
}

int main() {
    tuple<PublicKey, PrivateKey> a = generateKeys();
    string t = "My name is Jeff";
    string cipher = encrypt(get<0>(a), t);
    cout << cipher;
    return 0;
}