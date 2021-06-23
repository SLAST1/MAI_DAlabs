#pragma once
#include <iostream>
#include <vector>
#include <queue>

typedef std::vector<std::vector<int64_t>> TMatrix;

struct TEdge
{
    size_t from;
    size_t to;
    int64_t weigth;
};

struct TGraph
{
    size_t v, e;
    std::vector<TEdge> edges;
    TGraph() {}
    TGraph(size_t n, size_t m) : v(n), e(m) {}
};
