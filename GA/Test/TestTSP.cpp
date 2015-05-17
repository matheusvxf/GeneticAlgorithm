#include "TestTSP.h"

#include "Salesman.h"

#include <stdio.h>

namespace TestTSP
{
    bool ReadNextTestCase(std::fstream &fs, Salesman &salesman)
    {
        int num_vertices, num_edges;

        fs >> num_vertices >> num_edges;

        if (num_vertices == 0)
            return false;

        salesman.set_num_vertices(num_vertices);

        for (int i = 0; i < num_edges; ++i)
        {
            int src, dst, cost;

            fs >> src >> dst >> cost;
            salesman.set_connection(src - 1, dst - 1, cost);
        }

        return true;
    }
}