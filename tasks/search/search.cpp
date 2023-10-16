#include "search.h"

#include <vector>
#include <cctype>
#include <cmath>
#include <algorithm>

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
    return a.tf_idf > b.tf_idf || (a.tf_idf == b.tf_idf && a.index < b.index);
}

void PickoutWords(const std::string_view& text, std::vector<std::string_view>& words) {
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
                words.push_back(text.substr(left, right - left + 1));
                left = -1;
                right = -1;
            }
        }
    }
    if (left != -1) {
        words.push_back(text.substr(left, right - left + 1));
        left = -1;
        right = -1;
    }
}

void PickoutStrings(const std::string_view& text, std::vector<std::string_view>& strings) {
    size_t first_ind = 0;
    for (size_t i = 0; i < text.size(); ++i) {
        if (text[i] == '\n') {
            strings.push_back(text.substr(first_ind, i - first_ind));
            first_ind = i + 1;
        }
    }
    if (first_ind < text.size()) {
        strings.push_back(text.substr(first_ind, text.size() - first_ind));
    }
}

std::vector<std::string_view> Search(std::string_view text, std::string_view query, size_t results_count) {
    std::vector<std::string_view> words;
    std::vector<std::string_view> strings;
    PickoutWords(query, words);
    PickoutStrings(text, strings);
    std::vector<size_t> count(words.size(), 0);
    std::vector<size_t> number_of_words(strings.size(), 0);
    std::vector<std::vector<size_t>> occurences(strings.size(), std::vector<size_t>(words.size(), 0));
    size_t empty_strings = 0;
    for (size_t string = 0; string < strings.size(); ++string) {
        std::vector<std::string_view> words_in_string;
        PickoutWords(strings[string], words_in_string);
        number_of_words[string] = words_in_string.size();
        if (number_of_words[string] == 0) {
            ++empty_strings;
        }
        for (size_t unique_word = 0; unique_word < words.size(); ++unique_word) {
            for (size_t word = 0; word < words_in_string.size(); ++word) {
                if (CaseEqual(words_in_string[word], words[unique_word])) {
                    if (occurences[string][unique_word] == 0) {
                        ++count[unique_word];
                    }
                    ++occurences[string][unique_word];
                }
            }
        }
    }
    std::vector<WeighedString> tf_idf(strings.size());
    for (size_t s = 0; s < strings.size(); ++s) {
        tf_idf[s].index = s;
    }
    for (size_t w = 0; w < words.size(); ++w) {
        double word_freq = 0;
        if (count[w] != 0) {
            word_freq = std::log(static_cast<double>(strings.size() - empty_strings) / static_cast<double>(count[w]));
        }
        for (size_t s = 0; s < strings.size(); ++s) {
            if (number_of_words[s] == 0) {
                continue;
            }
            tf_idf[s].tf_idf +=
                static_cast<double>(occurences[s][w]) / static_cast<double>(number_of_words[s]) * word_freq;
        }
    }
    std::sort(tf_idf.begin(), tf_idf.end(), StringsComp);
    std::vector<std::string_view> result;
    for (size_t i = 0; i < results_count; ++i) {
        if (i == strings.size()) {
            break;
        }
        if (tf_idf[i].tf_idf == 0) {
            break;
        }
        result.push_back(strings[tf_idf[i].index]);
    }
    return result;
}
