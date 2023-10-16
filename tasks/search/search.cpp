#include "search.h"

#include <vector>
#include <cctype>
#include <cmath>
#include <algorithm>

const double EPS = 1e-9;

struct Subsegment {
    size_t begin;
    size_t len;
};

struct WeighedString {
    size_t index;
    double tf_idf;
    WeighedString() {
        index = 0;
        tf_idf = 0;
    }
};

bool CaseEqual(const std::string_view& a, const std::string_view& b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (size_t i = 0; i < a.size(); ++i) {
        if (tolower(a[i]) != tolower(b[i])) {
            return false;
        }
    }
    return true;
}

bool StringsComp(const WeighedString& a, const WeighedString& b) {
    return a.tf_idf - b.tf_idf >= -EPS;
}

void PickoutWords(const std::string_view& text, std::vector<Subsegment>& words) {
    size_t left = -1;
    size_t right = -1;
    for (size_t i = 0; i < text.size(); ++i) {
        if (std::isalpha(text[i])) {
            right = i;
            if (left == -1) {
                left = i;
            }
        } else {
            if (left != -1) {
                words.push_back({left, right - left + 1});
                left = -1;
                right = -1;
            }
        }
    }
    if (left != -1) {
        words.push_back({left, right - left + 1});
        left = -1;
        right = -1;
    }
}

void PickoutStrings(const std::string_view& text, std::vector<Subsegment> strings) {
    size_t first_ind = 0;
    for (size_t i = 0; i < text.size(); ++i) {
        if (text[i] == '\n') {
            strings.push_back({first_ind, i - first_ind});
            first_ind = i + 1;
        }
    }
    if (first_ind < text.size()) {
        strings.push_back({first_ind, text.size() - first_ind - 1});
    }
}

std::vector<std::string_view> Search(std::string_view text, std::string_view query, size_t results_count) {
    std::vector<Subsegment> words;
    std::vector<Subsegment> strings;
    PickoutWords(query, words);
    PickoutStrings(text, strings);
    std::vector<int> count(words.size(), 0);
    std::vector<int> number_of_words(strings.size(), 0);
    std::vector<std::vector<int>> occurences(strings.size(), std::vector<int>(words.size(), 0));
    for (size_t string = 0; string < strings.size(); ++string) {
        const auto& [begin, len] = strings[string];
        std::vector<Subsegment> words_in_string;
        PickoutWords(text.substr(begin, len), words_in_string);
        number_of_words[string] = words_in_string.size();
        for (size_t unique_word = 0; unique_word < words.size(); ++unique_word) {
            const auto& [begin_of_query_word, len_of_query_word] = words[unique_word];
            for (size_t word = 0; word < words_in_string.size(); ++word) {
                const auto& [begin_of_the_word, len_of_the_word] = words_in_string[word];
                if (CaseEqual(text.substr(begin_of_the_word, len_of_the_word), 
                              query.substr(begin_of_query_word, len_of_query_word))) {
                    if (occurences[string][word] == 0) {
                        ++count[word];
                    }
                    ++occurences[string][word];
                }
            }
        }
    }
    std::vector<WeighedString> tf_idf(strings.size());
    for (size_t w = 0; w < words.size(); ++w) {
        double word_freq = std::log(static_cast<double>(strings.size()) / static_cast<double>(count[w]));
        for (size_t s = 0; s < strings.size(); ++s) {
            tf_idf[s].tf_idf += 
                static_cast<double>(occurences[s][w]) / static_cast<double>(number_of_words[s]) * word_freq;
        }
    }
    for (size_t s = 0; s < strings.size(); ++s) {
        tf_idf[s].index = s;
    }
    std::sort(tf_idf.begin(), tf_idf.end(), StringsComp);
    std::vector<std::string_view> result;
    for (size_t i = 0; i < results_count; ++i) {
        if (i == strings.size()) {
            break;
        }
        result.push_back(text.substr(strings[tf_idf[i].index].begin, strings[tf_idf[i].index].len));
    }
    return result;
}
