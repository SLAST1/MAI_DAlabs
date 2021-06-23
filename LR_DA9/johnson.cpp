#include "johnson.hpp"
#include "structures.hpp"

bool operator<(TEdge const& p1, TEdge const& p2) { return p1.weigth > p2.weigth; }

void Deikstra(TMatrix const& gr, size_t const& node, TMatrix& dist, size_t const& n)
{
    dist[node][node] = 0;
    std::priority_queue<TEdge> pq;
    TEdge t = {node, 0, 0};
    pq.push(t);
    while(!pq.empty())
    {
        TEdge s = pq.top();
        pq.pop();
        for(size_t i = 0; i < n; ++i)
        {
            if(dist[node][i] - dist[node][s.from] > gr[s.from][i])
            {
                dist[node][i] = dist[node][s.from] + gr[s.from][i];
                TEdge p = { i, 0, dist[node][i] };
                pq.push(p);
            }
        }
    }
}

bool BellmanFord(TGraph const& gr, size_t const& node, TMatrix& dist)
{
    dist[node][node] = 0;
    for(size_t j = 0; j < gr.v - 1; ++j)
    {
        for(auto& i: gr.edges)
            if(dist[node][i.from] != INT64_MAX &&  dist[node][i.to] > dist[node][i.from] + i.weigth)
                dist[node][i.to] = (dist[node][i.from] + i.weigth);
    }
    for(auto& i: gr.edges)
        if(dist[node][i.from] != INT64_MAX &&  dist[node][i.to] > dist[node][i.from] + i.weigth)
            return false;
    return true;
}

bool Johnson(TGraph const& gr, TMatrix& dist)
{
    TGraph new_gr;
    new_gr.v = gr.v + 1;
    new_gr.e = gr.e + gr.v;
    new_gr.edges = gr.edges;
    for(size_t i = 0; i < gr.v; ++i)
        new_gr.edges.push_back(TEdge{gr.v, i, 0});
    TMatrix new_dist(1, std::vector<int64_t>(new_gr.v, 0));
    if(!BellmanFord(new_gr, 0, new_dist))
    {
        std::cout << "Negative cycle\n";
        return false;
    }
    TMatrix graph(gr.v, std::vector<int64_t>(gr.v, INT64_MAX));
    for(size_t i = 0; i < gr.v; ++i)
        graph[i][i] = 0;
    for(auto& i: gr.edges)
        graph[i.from][i.to] = i.weigth + new_dist[0][i.from] - new_dist[0][i.to];
    for(size_t i = 0; i < gr.v; ++i)
        Deikstra(graph, i, dist, gr.v);
    for(size_t i = 0; i < gr.v; ++i)
        for(size_t j = 0; j < gr.v; ++j)
            if(dist[i][j] != INT64_MAX)
                dist[i][j] = dist[i][j] + new_dist[0][j] - new_dist[0][i];
    return true;
}
