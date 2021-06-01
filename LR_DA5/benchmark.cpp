#include <iostream>
#include <chrono>
#include "st.hpp"

std::vector<int> StandartFind(std::string const& text, std::string const& pattern)
{
    std::vector<int> arr;
    size_t n_pos = text.find(pattern, 0);
    arr.push_back(n_pos);
    while(n_pos != std::string::npos)
    {
        n_pos = text.find(pattern, n_pos + 1);
        if(n_pos != std::string::npos) { arr.push_back(n_pos); }
    }
    return arr;
}

int main()
{
    std::string text, pattern;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    uint64_t create_time = 0;
    uint64_t myfind_time = 0;
    uint64_t find_time = 0;

    std::cin >> text;
    start = std::chrono::system_clock::now();
    TSuffTree tree(text + "$");
    TSuffArr sa(&tree);
    end = std::chrono::system_clock::now();
    create_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    while(std::cin >> pattern)
    {
        start = std::chrono::system_clock::now();
        std::vector<int> res_sa = sa.Find(pattern);
        end = std::chrono::system_clock::now();
        myfind_time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        start = std::chrono::system_clock::now();
        std::vector<int> res_find = StandartFind(text, pattern);
        end = std::chrono::system_clock::now();
        find_time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }

    std::cout << "\nTime for create suffix tree and suffix array: " << (double)create_time/1000000000 << " seconds\n";
    std::cout << "Time for my find: " << (double)myfind_time/1000000000 << " seconds\n";
    std::cout << "Time for standart find: " << (double)find_time/1000000000 << " seconds\n";
    return 0;
}
