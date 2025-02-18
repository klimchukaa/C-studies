#include "scorer.h"

#include <tuple>
#include <algorithm>

bool CmpByStudent(const Event* a, const Event* b) {
    return std::tie(a->student_name, a->task_name, a->time) < std::tie(b->student_name, b->task_name, b->time);
}

bool IsNewState(const std::vector<const Event*>& sorted_events, size_t i) {
    if (i + 1 == sorted_events.size() || sorted_events[i]->student_name != sorted_events[i + 1]->student_name ||
        sorted_events[i]->task_name != sorted_events[i + 1]->task_name) {
        return true;
    }
    return false;
}

void UpdateStatus(const EventType& event_type, bool& request_closed, bool& task_accepted) {
    if (event_type == EventType::CheckFailed) {
        task_accepted = false;
    } else if (event_type == EventType::CheckSuccess) {
        task_accepted = true;
    } else if (event_type == EventType::MergeRequestClosed) {
        request_closed = true;
    } else if (event_type == EventType::MergeRequestOpen) {
        request_closed = false;
    }
}

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    std::vector<const Event*> sorted_events;
    for (size_t i = 0; i < events.size(); ++i) {
        if (events[i].time <= score_time) {
            sorted_events.push_back(&events[i]);
        }
    }
    std::sort(sorted_events.begin(), sorted_events.end(), CmpByStudent);
    ScoreTable score_table;
    bool request_closed = true;
    bool task_accepted = false;
    for (size_t i = 0; i < sorted_events.size(); ++i) {
        UpdateStatus(sorted_events[i]->event_type, request_closed, task_accepted);
        if (IsNewState(sorted_events, i)) {
            if (request_closed && task_accepted) {
                score_table[sorted_events[i]->student_name].insert(sorted_events[i]->task_name);
            }
            request_closed = true;
            task_accepted = false;
        }
    }
    return score_table;
}
