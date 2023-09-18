#include "fibonacci.h"

int64_t CalculateNthFibonacci(int64_t n) {
    if (n == 0) {
        return 0;
    }
    int64_t before_last = 0;
    int64_t last = 1;
    for (int64_t i = 1; i < n; ++i) {
        int64_t new_last = last + before_last;
        before_last = last;
        last = new_last;
    }
    return last;
}