#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
#include "bigint.hpp"

int main()
{
    NBigInt::TBigInt num1, num2;
    NBigInt::TBigInt zero("0");
    char action = '?';
    while(std::cin >> num1 >> num2 >> action)
    {
        if(action == '+')
        {
            NBigInt::TBigInt res = num1 + num2;
            std::cout << res << "\n";
        }
        else if(action == '-')
        {
            if(num1 < num2)
            {
                std::cout << "Error\n";
                continue;
            }
            NBigInt::TBigInt res = num1 - num2;
            std::cout << res << "\n";
        }
        else if(action == '*')
        {
            NBigInt::TBigInt res = num1 * num2;
            std::cout << res << "\n";
        }
        else if(action == '^')
        {
            if(num1 == zero && num2 == zero)
            {
                std::cout << "Error\n";
                continue;
            }
            NBigInt::TBigInt res = num1 ^ num2;
            std::cout << res << "\n";
        }
        else if(action == '/')
        {
            if(num2 == zero)
            {
                std::cout << "Error\n";
                continue;
            }
            NBigInt::TBigInt res = num1 / num2;
            std::cout << res << "\n";
        }
        else if(action == '<')
        {
            if(num1 < num2) { std::cout << "true\n"; }
            else { std::cout << "false\n"; }
        }
        else if(action == '>')
        {
            if(num1 > num2) { std::cout << "true\n"; }
            else { std::cout << "false\n"; }
        }
        else if(action == '=')
        {
            if(num1 == num2) { std::cout << "true\n"; }
            else { std::cout << "false\n"; }
        }
        else { std::cout << "Error\n"; }
    }
    return 0;
}
