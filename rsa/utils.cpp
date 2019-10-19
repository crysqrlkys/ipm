//
// Created by whyko on 19.10.2019.
//

#include <ctime>
#include <cstdlib>

bool isPrime(long number) {
    if (number == 0) {
        return false;
    } else {
        for (int i = 2; i < number; i++)
            if (number % i == 0)
                return false;
    }
    return true;
}

long generatePrime() {
    long prime = 0;
    srand(time(0));
    while (true) {
        prime = rand() % 100 + 100;
        if (isPrime(prime))
            break;
    }
    return prime;
}

long gcd(const long a, const long b) {
    long dividend = a;
    long divisor = b;
    long residual = dividend % divisor;
    while (residual) {
        dividend = divisor;
        divisor = residual;
        residual = dividend % divisor;
    }
    return divisor;
}

