#include "provinces.h"

int64_t CountPassports(const std::vector<int>& provinces) {
    std::multiset<int64_t> arranged_provinces;
    for (const auto& province : provinces) {
        arranged_provinces.insert(province);
    }
    int64_t changed_passports = 0;
    while (arranged_provinces.size() >= 2) {
        int64_t smallest_province = *arranged_provinces.begin();
        arranged_provinces.erase(arranged_provinces.begin());
        int64_t next_smallest_province = *arranged_provinces.begin();
        arranged_provinces.erase(arranged_provinces.begin());
        int64_t new_province = smallest_province + next_smallest_province;
        changed_passports += new_province;
        arranged_provinces.insert(new_province);
    }
    return changed_passports;
}
