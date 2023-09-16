#include "is_leap.h"

const int GOOD_YEARS = 400;
const int BAD_YEARS = 100;

bool IsLeap(int year) {
    if (year % GOOD_YEARS == 0) {
        return true;
    }
    if (year % BAD_YEARS == 0) {
        return false;
    }
    if (year % 4 == 0) {
        return true;
    }
    return false;
}

