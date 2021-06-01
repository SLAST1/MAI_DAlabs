#include <iostream>
#include "st.hpp"

int main()
{
    std::string text, pattern;
    std::cin >> text;
    TSuffTree tree(text + "$");
    TSuffArr sa(&tree);
    size_t test_number = 1;
    while(std::cin >> pattern)
    {
        std::vector<int> result = sa.Find(pattern);
        if(!result.empty())
        {
            std::cout << test_number << ": ";
            for(size_t i = 0; i < result.size(); ++i)
            {
                std::cout << result[i] + 1;
                if(i < result.size() -  1) { std::cout << ", "; }
            }
            std::cout << "\n";
        }
        ++test_number;
    }
    return 0;
}
