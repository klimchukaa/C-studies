#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    size_t n = str.size();
    int64_t left_it = 0;
    int64_t right_it = static_cast<int64_t>(n) - 1;
    while (left_it < right_it) {
        if (str[left_it] == ' ') {
            ++left_it;
        } else if (str[right_it] == ' ') {
            --right_it;
        } else if (str[left_it] != str[right_it]) {
            return false;
        } else {
            ++left_it;
            --right_it;
        }
    }
    return true;
}
