#include "johnson.hpp"
#include "structures.hpp"
#include <chrono>

int main()
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    uint64_t johnson_time = 0;
    size_t test_count = 0;

    std::cout << "Enter graph:\n";
    size_t n = 0;
    size_t m = 0;
    std::cin >> n >> m;
    TGraph gr(n, m);
    TMatrix dist(n, std::vector<int64_t>(n, INT64_MAX));
    for(size_t i = 0; i < n; ++i)
        dist[i][i] = 0;
    size_t from = 0;
    size_t to = 0;
    int64_t weight = 0;
    for(size_t k = 0; k < m; ++k)
    {
        std::cin >> from >> to >> weight;
        gr.edges.push_back(TEdge{from - 1, to - 1, weight});
    }

    std::cout << "Enter test count:\n";
    std::cin >> test_count;

    start = std::chrono::system_clock::now();
    for(size_t i = 0; i < test_count; ++i)
    {
        for(size_t i = 0; i < dist.size(); ++i)
        {
            for(size_t j = 0; j < dist[i].size(); ++j)
            {
                if(i != j)
                    dist[i][j] = INT64_MAX;
                else
                    dist[i][j] = 0;
            }
        }
        Johnson(gr, dist);
    }
    end = std::chrono::system_clock::now();
    johnson_time = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

    start = std::chrono::system_clock::now();
    for(size_t i = 0; i < test_count; ++i)
    {
        for(size_t i = 0; i < dist.size(); ++i)
        {
            for(size_t j = 0; j < dist[i].size(); ++j)
            {
                if(i != j)
                    dist[i][j] = INT64_MAX;
                else
                    dist[i][j] = 0;
            }
        }
    }
    end = std::chrono::system_clock::now();
    johnson_time -= std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

    std::cout << "Time for Johnson on " << test_count << " tests: " << johnson_time << " seconds\n";
}
