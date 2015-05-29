#include "Knapsack.h"

#include <vector>
#include <algorithm>

#include "KnapsackGenetic.h"
#include "Logger.h"

#define all(Q) Q.begin(), Q.end()

Knapsack::Knapsack()
{
}


Knapsack::~Knapsack()
{
}

int Knapsack::SolveDynamicProgramming()
{
    using namespace std;

    vector< vector<int> > m;
    int W = knapsack_capacity_;
    int N = items_.size();

    m.resize(N);
    for (int i = 0, size = m.size(); i < size; ++i)
    {
        m[i].resize(W + 1);
        fill(all(m[i]), 0);
    }

    for (int w = 0; w <= W; ++w)
    if (w >= items_[N - 1].weight)
        m[N - 1][w] = items_[N - 1].value;

    for (int i = N - 2; i >= 0; --i)
    {
        for (int w = 0; w <= W; ++w)
        {
            if (w >= items_[i].weight)
                m[i][w] = max(items_[i].value + m[i + 1][w - items_[i].weight], m[i + 1][w]);
            else
                m[i][w] = m[i + 1][w];
        }
    }

    return m[0][W];
}

GeneticAlgorithm::SolutionVector& Knapsack::SolveGeneticAlgorithm()
{
    ga_manager_.set_capacity(knapsack_capacity_);
    ga_manager_.set_knapsack(*this);
    ga_manager_.set_generation_statistic_output_file(generation_statistic_file_);

    return ga_manager_.Run();
}

bool Knapsack::ReadNextTestCase(std::fstream &fs)
{
    int num_items, capacity;

    fs >> num_items >> capacity;

    if (num_items == 0)
        return false;

    set_num_items(num_items);
    set_capacity(capacity);

    for (int i = 0; i < num_items; ++i)
    {
        int value, weight;

        fs >> value >> weight;
        set_item(i, value, weight);
    }

    return true;
}

std::string Knapsack::ProblemGenerator(int num_items, int weight)
{
    std::string str;

    str += int2str(num_items) + " " + int2str(weight) + "\n";

    for (int i = 0; i < num_items; ++i)
        str += int2str(rand() % 100 + 1) + " " + int2str(rand() % (weight + 1)) + "\n";
    
    return str;
}