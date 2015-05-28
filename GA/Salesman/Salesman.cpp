#include "Salesman.h"

#include <algorithm>

#include "Common.h"
#include "TSPGenetic.h"

#define EMPTY_SET 0x00
#define INSERT_TO_SET(S, i) (S = (S | (1 << i)))
#define BELONGS_TO_SET(S, i) ((S & (1 << i)) == (1 << i))
#define REMOVE_FROM_SET(S, i) (S ^ (1 << i))

Salesman::Salesman()
{
}

Salesman::~Salesman()
{
}

void Salesman::set_num_vertices(int num_vertices)
{
    graph_.set_num_nodes(num_vertices);
}

void Salesman::set_connection(int src, int dst, int cost)
{
    graph_.set_cost(src, dst, cost);
    graph_.set_cost(dst, src, cost);
}

int Salesman::DynamicProgrammingRecursion(int i, int S)
{
    int minimum = INF;

    if (m[i][S] < INF)
        return m[i][S];

    for (int j = 0; j < graph_.num_nodes(); ++j)
    {
        int cost = graph_.cost(i, j);

        if (BELONGS_TO_SET(S, j) && cost < INF)
        {
            int Q = REMOVE_FROM_SET(S, j);
            minimum = std::min(minimum, cost + DynamicProgrammingRecursion(j, Q));
        }
    }

    return m[i][S] = minimum;
}

int Salesman::SolveDynamicProgramming()
{
    using namespace std;
    int N = graph_.num_nodes();
    int S = EMPTY_SET;

    m.resize(N);
    foreach(m, vec)
    {
        vec->resize(1 << N);
        std::fill(ALL((*vec)), INF);
    }

    for (int i = 1; i < N; ++i)
    {
        INSERT_TO_SET(S, i);
        m[i][0] = graph_.cost(i, 0);
    }

    return DynamicProgrammingRecursion(0, S);
}

float Salesman::SolveGA(int test_num)
{
    TSPGeneticAlgorithm genetic;
    std::string str_builder = "statistic-salesman-test-" + int2str(test_num) + ".txt";
    
    genetic.set_salesman(*this);
    genetic.set_generation_statistic_output_file(str_builder);

    auto &salesman = genetic.Run();
    return salesman.fitness();
}

