#pragma once

#include <vector>

class Graph
{
private:
    std::vector< std::vector< int > > adj;
public:
    Graph();
    ~Graph();

    void set_num_nodes(int num_nodes);
    inline int num_nodes() { return adj.size(); }
    inline int cost(int src, int dst) { return adj[src][dst]; }
    inline int set_cost(int src, int dst, int cost) { return adj[src][dst] = cost; }
};

