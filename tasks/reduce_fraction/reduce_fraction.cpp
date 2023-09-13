#include "reduce_fraction.h"

int64_t Gcd(int64_t a, int64_t b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int64_t ReduceFraction(int64_t numerator, int64_t denominator) {
    int64_t sign_of_numerator = 1;
    if (numerator < 0) {
        sign_of_numerator *= -1;
        numerator *= -1;
    }
    if (denominator < 0) {
        sign_of_numerator *= -1;
        denominator *= -1;
    }
    int64_t d = Gcd(numerator, denominator);
    int64_t new_numer = numerator / d;
    int64_t new_denom = denominator / d;
    return new_denom + sign_of_numerator * new_numer;
}
