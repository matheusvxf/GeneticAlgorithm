#include "Knapsack.h"

#include <vector>
#include <algorithm>

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