#pragma once

#include <vector>

#include "Graph.h"

class Salesman
{
private:
    Graph graph_;
    std::vector< std::vector< int > > m;

    int DynamicProgrammingRecursion(int i, int S);
public:
    Salesman();
    ~Salesman();

    int SolveDynamicProgramming();
    void set_num_vertices(int num_vertices);
    void set_connection(int src, int dst, int cost);
};

