#include "admission.h"
#include <tuple>
#include <algorithm>

bool operator<(const Student&a, const Student& b) {
    return std::tie(a.birth_date.year, a.birth_date.month, a.birth_date.day, a.name) <
                std::tie(b.birth_date.year, b.birth_date.month, b.birth_date.day, b.name);
}

bool CmpByScore(const Applicant& a, const Applicant& b) {
    return std::tie(a.points, a.student) < std::tie(b.points, b.student);
}

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    std::sort(applicants.begin(), applicants.end(), CmpByScore);
    AdmissionTable admission_table;
    std::unordered_map<std::string, size_t> available_places;
    for (size_t i = 0; i < universities.size(); ++i) {
        admission_table.emplace(universities[i].name);
        available_places[universities[i].name] = universities[i].max_students;
    }
    for (size_t i = 0; i < applicants.size(); ++i) {
        for (size_t j = 0; j < applicants[i].wish_list.size(); ++j) {
            if (available_places[applicants[i].wish_list[j]] > 0) {
                Student* applicant = new Student(applicants[i].student);
                admission_table[applicants[i].wish_list[j]].push_back(applicant);
                --available_places[applicants[i].wish_list[j]];
                break;
            }
        }
    }
    return admission_table;
}
