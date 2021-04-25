#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
struct TAnswer {
    int strPos;
    int wordPos;
};
const int MAX_WORD_LENGTH = 16;
bool Equals(const std::string& first, const std::string& second) {
    for (int i = 0; i < MAX_WORD_LENGTH; ++i) {
        char c1 = ('A' <= first[i] && first[i] <= 'Z' ? first[i] - 'A' + 'a' : first[i]);
        char c2 = ('A' <= second[i] && second[i] <= 'Z' ? second[i] - 'A' + 'a' : second[i]);
        if (c1 != c2) {
            return false;
        }
    }
    return true;
}
void CalculateZFunc(const std::vector<std::string>& sample, std::vector<int>& zFunc) {
    for (int i = 1, l = 0, r = 0; i < zFunc.size(); ++i) {
        if (i <= r) {
            zFunc[i] = std::min(zFunc[i - l], r - i + 1);
        }
        while (zFunc[i] + i < zFunc.size() && Equals(sample[zFunc[i]], sample[zFunc[i] + i])) {
            ++zFunc[i];
        }
        if (r < i + zFunc[i] - 1) {
            l = i;
            r = i + zFunc[i] - 1;
        }
    }
}
std::vector<TAnswer> FindOccurs(const std::vector<std::string>& sample, const std::vector<int>& zFunc, const std::vector<std::string>& text, const std::vector<int>& stringEnd) {
    int value;
    int wordPos = 0;
    int strPos = 0;
    std::vector<TAnswer> answer;
    for (int i = 0, l = 0, r = 0; i < text.size(); ++i) {
        value = 0;
        while (i == stringEnd[strPos]) {
            ++strPos;
            wordPos = 0;
        }
        ++wordPos;
        if (i <= r) {
            value = std::min(zFunc[i - l], r - i + 1);
        }
        while (value < sample.size() && value + i < text.size() && Equals(sample[value], text[value + i])) {
            ++value;
        }
        if (r < i + value - 1) {
            l = i;
            r = i + value - 1;
        }
        if (value == sample.size()) {
            answer.push_back({strPos + 1, wordPos});
        }
    }
    return answer;
}