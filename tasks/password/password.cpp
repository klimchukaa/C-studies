#include "password.h"

const int64_t MAX_ASCII = 126;
const int64_t MIN_ASCII = 33;

bool ValidatePassword(const std::string& password) {
    int64_t has_lower = 0;
    int64_t has_upper = 0;
    int64_t has_digit = 0;
    int64_t has_special = 0;
    for (size_t i = 0; i < password.size(); ++i) {
        if (password[i] < MIN_ASCII || MAX_ASCII < password[i]) {
            return false;
        }
        if ('a' <= password[i] && password[i] <= 'z') {
            has_lower = 1;
        } else if ('A' <= password[i] && password[i] <= 'Z') {
            has_upper = 1;
        } else if ('0' <= password[i] && password[i] <= '9') {
            has_digit = 1;
        } else {
            has_special = 1;
        }
    }
    if (has_lower + has_digit + has_special + has_upper >= 3) {
        return true;
    }
    return false;
}
