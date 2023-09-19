#include "is_leap.h"

const int GOOD_YEARS = 400;
const int BAD_YEARS = 100;
const int LEAP_YEARS = 4;

bool IsLeap(int year) {
    if (year % GOOD_YEARS == 0) {
        return true;
    }
    if (year % BAD_YEARS == 0) {
        return false;
    }
    if (year % LEAP_YEARS == 0) {
        return true;
    }
    return false;
}