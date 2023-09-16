#include "min_divisor.h"

int64_t MinDivisor(int64_t number) {
    for (int64_t d = 2; d * d <= number; ++d) {
        if (number % d == 0) {
            return d;
        }
    }
    return number;
}
