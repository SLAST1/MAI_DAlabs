#include "johnson.hpp"
#include "structures.hpp"

int main()
{
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
    if(Johnson(gr, dist))
    {
        for(size_t i = 0; i < n; ++i)
        {
            for(size_t j = 0; j < n; ++j)
            {
                if(dist[i][j] == INT64_MAX)
                    std::cout << "inf";
                else
                    std::cout << dist[i][j];
                if(j != n - 1)
                    std::cout << ' ';
            }
            std::cout << "\n";
        }
    }
    return 0;
}
