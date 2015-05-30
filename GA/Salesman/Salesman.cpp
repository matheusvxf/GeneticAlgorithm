#include "Salesman.h"

#include <algorithm>
#include <fstream>

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

std::string Salesman::SolveExactSolution()
{
    int result = SolveDynamicProgramming();
    printf("Dynamic Programming Solution: %d\n", result);

    return int2str(result);
}

GeneticAlgorithm::SolutionVector& Salesman::SolveGeneticAlgorithm()
{
    ga_manager_.set_salesman(*this);
    ga_manager_.set_generation_statistic_output_file(generation_statistic_file_);

    return ga_manager_.Run();
}

bool Salesman::ReadNextTestCase(std::fstream &fs)
{
    int num_vertices, num_edges;

    fs >> num_vertices >> num_edges;

    if (num_vertices == 0)
        return false;

    set_num_vertices(num_vertices);

    for (int i = 0; i < num_edges; ++i)
    {
        int src, dst, cost;

        fs >> src >> dst >> cost;
        set_connection(src, dst, cost);
    }

    return true;
}

std::string Salesman::ProblemGenerator(int num_cities)
{
    std::string str;
    std::vector< std::pair< int, int > > Q(num_cities);
    int num_edges = (num_cities) * (num_cities - 1) / 2;
    int counter = 0;
    for (auto &p : Q)
    {
        p.first = rand() % (1000 + 1);
        p.second = rand() % (1000 + 1);
    }

    str += int2str(num_cities) + " " + int2str(num_edges) + "\n";
    for (int i = 0; i < num_cities; ++i)
    {
        for (int j = i + 1; j < num_cities; ++j)
        {
            int delta_x = Q[i].first - Q[j].first;
            int delta_y = Q[i].second - Q[j].second;

            str += int2str(i) + " " + int2str(j) + " " + int2str((int)sqrt(delta_x * delta_x + delta_y * delta_y)) + "\n";
            counter++;
        }
    }

    return str;
}