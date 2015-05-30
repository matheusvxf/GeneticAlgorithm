#include "Knapsack.h"

#include <vector>
#include <set>
#include <algorithm>

#include "KnapsackGenetic.h"
#include "Logger.h"
#include "Common.h"

#define all(Q) Q.begin(), Q.end()

Knapsack::Knapsack()
{
}


Knapsack::~Knapsack()
{
}

std::set<int> Knapsack::FindKnapsack(const std::vector< std::vector<int> > &m, int item, int weight)
{
    if (item == m.size() - 1)
    {
        if (items_[item].weight() <= weight)
            return{ item };
        else
            return{};
    }
    else
    {
        if (m[item][weight] == m[item + 1][weight])
        {
            return FindKnapsack(m, item + 1, weight);
        }
        else
        {
            std::set< int > &res = FindKnapsack(m, item + 1, weight - items_[item].weight());
            res.insert(item);
            return res;
        }
    }
}

std::pair< int, std::set< int > > Knapsack::SolveDynamicProgramming()
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
    if (items_[N - 1].weight() <= w)
        m[N - 1][w] = items_[N - 1].value();

    for (int i = N - 2; i >= 0; --i)
    {
        for (int w = 0; w <= W; ++w)
        {
            if (items_[i].weight() <= w)
                m[i][w] = max(items_[i].value() + m[i + 1][w - items_[i].weight()], m[i + 1][w]);
            else
                m[i][w] = m[i + 1][w];
        }
    }

    return std::pair< int, std::set< int > >(std::make_pair(m[0][W], FindKnapsack(m, 0, W)));
}

std::string Knapsack::SolveExactSolution()
{
    auto solution = SolveDynamicProgramming();

    printf("Dynamic Programming Solution: %d\n", solution.first);

#if(DEBUG == TRUE)
    printf("Items:\n");
    for (int item : solution.second)
    {
        printf("%d value: %d weight: %d\n", item, items_[item].value(), items_[item].weight());
    }
    printf("\n");
#endif
    return int2str(solution.first);
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
        str += int2str(rand() % 100 + 1) + " " + int2str(rand() % (weight/2 + 1)) + "\n";
    
    return str;
}