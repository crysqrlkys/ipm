#include <iostream>
#include <cmath>
#include <vector>
#include <tuple>
#include <unordered_set>
#include <sstream>
#include <codecvt>


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
    PrivateKey(long long _x) {
        x = _x;
    }

    long long x;
};

std::wstring utf8_to_utf16(const std::string &utf8) {
    std::vector<unsigned long> unicode;
    size_t i = 0;
    while (i < utf8.size()) {
        unsigned long uni;
        size_t todo;
        bool error = false;
        unsigned char ch = utf8[i++];
        if (ch <= 0x7F) {
            uni = ch;
            todo = 0;
        } else if (ch <= 0xBF) {
            throw std::logic_error("not a UTF-8 string");
        } else if (ch <= 0xDF) {
            uni = ch & 0x1F;
            todo = 1;
        } else if (ch <= 0xEF) {
            uni = ch & 0x0F;
            todo = 2;
        } else if (ch <= 0xF7) {
            uni = ch & 0x07;
            todo = 3;
        } else {
            throw std::logic_error("not a UTF-8 string");
        }
        for (size_t j = 0; j < todo; ++j) {
            if (i == utf8.size())
                throw std::logic_error("not a UTF-8 string");
            unsigned char ch = utf8[i++];
            if (ch < 0x80 || ch > 0xBF)
                throw std::logic_error("not a UTF-8 string");
            uni <<= 6;
            uni += ch & 0x3F;
        }
        if (uni >= 0xD800 && uni <= 0xDFFF)
            throw std::logic_error("not a UTF-8 string");
        if (uni > 0x10FFFF)
            throw std::logic_error("not a UTF-8 string");
        unicode.push_back(uni);
    }
    std::wstring utf16;
    for (size_t i = 0; i < unicode.size(); ++i) {
        unsigned long uni = unicode[i];
        if (uni <= 0xFFFF) {
            utf16 += (wchar_t) uni;
        } else {
            uni -= 0x10000;
            utf16 += (wchar_t) ((uni >> 10) + 0xD800);
            utf16 += (wchar_t) ((uni & 0x3FF) + 0xDC00);
        }
    }
    return utf16;
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

long long mul(long long a, long long b, long long n) {// a*b mod n
    int sum = 0;
    for (int i = 0; i < b; i++) {
        sum += a;
        if (sum >= n) {
            sum -= n;
        }
    }
    return sum;
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

long long findPrime(long long min, long long max) {
    long long range = max - min + 1;
    while (true) {
        int r = rand() % range + min;
        if (isPrime(r)) return r;
    }
}

tuple<PublicKey, PrivateKey> generateKeys() {
    int iNumBits = 128;
    long long p = findPrime(100000, 1000000);
    long long g = findPrimitiveRoot(p);

    long long x = rand() % (int) ((p - 1) / 2 - 1 + 1) + 1;
    long long y = modulo(g, x, p);

    PublicKey publicKey(p, g, y, iNumBits);
    PrivateKey privateKey(x);
    return make_tuple(publicKey, privateKey);
}

string crypt(PublicKey pk, vector<char> text) {
    long long p = pk.p;
    long long g = pk.g;
    long long y = pk.y;

    string encText;
    for (auto const &m : text) {
        if (m > 0) {
            long long k = rand() % (p - 2) + 1; // 1 < k < (p-1)
            long long a = modulo(g, k, p);
            long long b = mul(modulo(y, k, p), m, p);
            encText += to_string(a) + " " + to_string(b) + " ";
        }
    }
    return encText;
}


int main() {
    tuple<PublicKey, PrivateKey> a = generateKeys();
    string t = "My name is Jeff and Jeff";
    vector<char> bytes(t.begin(), t.end());
    string cipher = crypt(get<0>(a), bytes);
    cout<< "Encoded text: " << endl;
    cout << cipher;



//    string plain_t = decrypt(get<1>(a), cipher);
//    cout << plain_t;
    return 0;
}