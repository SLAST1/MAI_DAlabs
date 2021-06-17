#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

bool CompareFunc(int const& lhs, int const& rhs) { return lhs > rhs; }

bool ValidTriangle(int const& s_1, int const& s_2, int const& s_3)
{
    if((s_1 < (s_2 + s_3)) && (s_2 < (s_1 + s_3)) && (s_3 < (s_1 + s_2)))
        return true;
    else
        return false;
}

double Area(int const& s_1, int const& s_2, int const& s_3)
{
    double p = 0.5 * (s_1 + s_2 + s_3);
    return sqrt(p) * sqrt(p - s_1) * sqrt(p - s_2) * sqrt(p - s_3);
}

int main()
{
    std::vector<int> data;
    int n = 0, s = 0, s_1 = 0, s_2 = 0, s_3 = 0;
    double max_area = 0.0, cur_area = 0.0;

    std::cin >> n;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> s;
        data.push_back(s);
    }

    std::sort(data.begin(), data.end(), CompareFunc);

    for(int i = 1; i < int(data.size() - 1); ++i)
    {
        if(data.size() < 3)
            break;
        if(ValidTriangle(data[i - 1], data[i], data[i + 1]))
        {
            cur_area = Area(data[i - 1], data[i], data[i + 1]);
            if(cur_area > max_area)
            {
                max_area = cur_area;
                s_1 = data[i + 1];
                s_2 = data[i];
                s_3 = data[i - 1];
            }
        }
    }

    if(max_area == 0)
        std::cout << 0 << '\n';
    else
    {
        printf("%.3f\n", max_area);
        std::cout << s_1 << ' ' << s_2 << ' ' << s_3 << '\n';
    }
    return 0;
}
