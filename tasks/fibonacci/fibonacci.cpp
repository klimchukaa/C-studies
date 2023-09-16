#include "fibonacci.h"

int64_t CalculateNthFibonacci(int64_t n) {
    int64_t fibonacci[n + 1];
    for (int64_t i = 0; i <= n; ++i) {
        if (i == 0) {
            fibonacci[i] = 0;
        } else if (i == 1) {
            fibonacci[i] = 1;
        } else {
            fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];
        }
    }
    return fibonacci[n];
}