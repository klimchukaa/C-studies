#include "tests_checking.h"

#include <string_view>
#include <algorithm>
#include <deque>

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<std::string_view> order_of_tests;
    for (size_t i = 0; i < student_actions.size(); ++i) {
        if (student_actions[i].side == Side::Top) {
            order_of_tests.push_front(student_actions[i].name);
        } else {
            order_of_tests.push_back(student_actions[i].name);
        }
    }
    std::vector<std::string> responses;
    for (size_t i = 0; i < queries.size(); ++i) {
        responses.emplace_back(order_of_tests[queries[i] - 1]);
    }
    return responses;
}