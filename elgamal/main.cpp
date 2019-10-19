#include <iostream>
#include <cmath>
#include <vector>
#include <tuple>
#include <unordered_set>
#include <sstream>
#include <codecvt>
#include <fstream>


using namespace std;

class PublicKey {
public:
    PublicKey(long long _p, long long _g, long long _y) {
        p = _p;
        g = _g;
        y = _y;
    }

    long long p;
    long long g;
    long long y;
};

class PrivateKey {
public:
    PrivateKey(long long _x, long long _p) {
        x = _x;
        p = _p;
    }
    long long p;
    long long x;
};

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

long long power(long long base, long long exponent, long long mod) {
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

void findPrimeFactors(unordered_set<int> &s, long long n) {
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

    findPrimeFactors(s, phi);

    for (long long root = 2; root <= phi; root++) {
        bool flag = false;
        for (auto it = s.begin(); it != s.end(); it++) {
            if (power(root, phi / (*it), n) == 1) {
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
        long long r = rand() % range + min;
        if (isPrime(r)) return r;
    }
}

tuple<PublicKey, PrivateKey> generateKeys() {
    long long p = findPrime(100000, 1000000);
    long long g = findPrimitiveRoot(p);

    long long x = rand() % (long long) ((p - 1) / 2 - 1 + 1) + 1;
    long long y = power(g, x, p);

    PublicKey publicKey(p, g, y);
    PrivateKey privateKey(x, p);
    return make_tuple(publicKey, privateKey);
}

string encrypt(PublicKey pk, vector<char> text) {
    long long p = pk.p;
    long long g = pk.g;
    long long y = pk.y;

    string encText;
    for (auto const &m : text) {
        if (m > 0) {
            long long k = rand() % (p - 2) + 1; // 1 < k < (p-1)
            long long a = power(g, k, p);
            long long b = mul(power(y, k, p), m, p);
            encText += to_string(a) + " " + to_string(b) + " ";
        }
    }
    return encText;
}

string decrypt(PrivateKey pk, vector<vector<long long>> pairs) {
    long long p = pk.p;
    long long x = pk.x;

    string decryptedText;
    for (auto const& pair : pairs) {
        long long a = pair[0];
        long long b = pair[1];
        if (a != 0 && b != 0) {
            int deM = mul(b, power(a, p - 1 - x, p), p);// m=b*(a^x)^(-1)mod p =b*a^(p-1-x)mod p
            char m = static_cast<char>(deM);
            decryptedText+=m;
        }
    }
    return decryptedText;
}

int main() {
    tuple<PublicKey, PrivateKey> keys = generateKeys();

    string plainText;

    ifstream inFile;
    inFile.open("../input.txt");
    stringstream strStream;
    strStream << inFile.rdbuf();
    plainText = strStream.str();
    vector<char> bytes(plainText.begin(), plainText.end());
    string cipher = encrypt(get<0>(keys), bytes);
    cout << "Encoded text: " << endl;
    cout << cipher << endl;

    vector<vector<long long>> pairs;
    vector<long long> values;

    stringstream stream(cipher);
    long long n;
    while(stream >> n){
        values.push_back(n);
    }

    for(vector<int>::size_type i = 0; i != values.size(); i = i + 2) {
        long long a = values[i];
        long long b = values[i+1];
        vector<long long> pair;
        pair.push_back(a);
        pair.push_back(b);
        pairs.push_back(pair);
    }

    string decryptedText = decrypt(get<1>(keys), pairs);
    cout << "Decrypted Text: " << endl;
    cout << decryptedText << endl;
    return 0;
}