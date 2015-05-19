#include "Graph.h"

#include "Common.h"


Graph::Graph()
{
}


Graph::~Graph()
{
}

void Graph::set_num_nodes(int num_nodes)
{
    adj.resize(num_nodes);
    foreach(adj, vec)
    {
        vec->resize(num_nodes);
        std::fill(ALL((*vec)), INF);
    }

    for (int i = 0; i < num_nodes; ++i)
        adj[i][i] = 0;
}