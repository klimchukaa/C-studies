#include "sort_students.h"
#include <tuple>
#include <algorithm>

bool CmpByDate(const Student& a, const Student& b) {
    return std::tie(a.birth_date, a.last_name, a.name) < std::tie(b.birth_date, b.last_name, b.name);
}

bool CmpByName(const Student& a, const Student& b) {
    return std::tie(a.last_name, a.name, a.birth_date) < std::tie(b.last_name, b.name, b.birth_date);
}

void SortStudents(std::vector<Student>& students, SortKind sortKind) {
    if (sortKind == SortKind::Date) {
        std::sort(students.begin(), students.end(), CmpByDate);
    } else {
        std::sort(students.begin(), students.end(), CmpByName);
    }
}
