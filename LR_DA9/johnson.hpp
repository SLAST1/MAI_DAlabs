#pragma once
#include "structures.hpp"

bool operator<(TEdge const&, TEdge const&);
void Deikstra(TMatrix const&, size_t const&, TMatrix&, size_t const&);
bool BellmanFord(TGraph const&, size_t const&, TMatrix&);
bool Johnson(TGraph const&, TMatrix&);
