#include "search.hpp"
int main() {
    std::vector<int> zFunc;
    std::vector<std::string> sample;
    std::vector<int> stringEnd;
    std::vector<std::string> text;
    std::string word;
    word.append(MAX_WORD_LENGTH, 0);
    char c = getchar();
    bool sampleFinish = false;
    bool inputWord = false;
    int index = 0;
    while (c != EOF) {
        if (c == '\n') {
            if (inputWord) {
                if (!sampleFinish) {
                    sample.push_back(word);
                }
                else {
                    text.push_back(word);
                }   
                for (int i = 0; i < index; ++i) {
                    word[i] = 0;
                }
                index = 0;
                inputWord = false;
            }
            if (!sampleFinish) {
                sampleFinish = true;
            }
            else {
                stringEnd.push_back(text.size());
            }
        }
        else if (c == '\t' || c == ' ') {
            if (inputWord) {
                if (!sampleFinish) {
                    sample.push_back(word);
                }
                else {
                    text.push_back(word);
                }
                for (int i = 0; i < index; ++i) {
                    word[i] = 0;
                }
                index = 0;
                inputWord = false;
            }
        }
        else {
            word[index] = c;
            ++index;
            inputWord = true;
        }
        c = getchar();
    }
    zFunc.assign(sample.size(), 0);
    CalculateZFunc(sample, zFunc);
    std::vector<TAnswer> ans = FindOccurs(sample, zFunc, text, stringEnd);
    for (int j = 0; j < ans.size(); ++j) {
        std::cout << ans[j].strPos << ", " << ans[j].wordPos << std::endl;
    }
    return 0;
}