#include "tests_checking.h"
#include <string_view>

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::vector<std::string> top, bottom;
    for (size_t i = 0; i < student_actions.size(); ++i) {
        if (student_actions[i].side == Side::Top) {
            top.push_back(student_actions[i].name);
        } else {
            bottom.push_back(student_actions[i].name);
        }
    }
    std::vector<std::string> order;
    for (size_t i = top.size() - 1; i >= 0; --i) {
        order.push_back(top[i]);
    }
    for (size_t i = 0; i < bottom.size(); ++i) {
        order.push_back(bottom[i]);
    }
    std::vector<std::string> responses;
    for (size_t i = 0; i < queries.size(); ++i) {
        responses.push_back(order[queries[i] - 1]);
    }
    return responses;
}