#pragma once

#include <vector>

#include "Graph.h"
#include "Common.h"

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
    inline int num_vertices() { return graph_.num_nodes(); }
    inline int num_cities() { return num_vertices(); }
};

