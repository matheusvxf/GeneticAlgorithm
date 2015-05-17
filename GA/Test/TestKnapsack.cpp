#include "TestKnapsack.h"

#include "Common.h"

namespace TestKnapsack
{
    bool ReadNextTestCase(std::fstream &fs, Knapsack &knapsack)
    {
        int num_items, capacity;

        fs >> num_items >> capacity;

        if (num_items == 0)
            return false;

        knapsack.set_num_items(num_items);
        knapsack.set_capacity(capacity);

        for (int i = 0; i < num_items; ++i)
        {
            int value, weight;

            fs >> value >> weight;
            knapsack.set_item(i, value, weight);
        }

        return true;
    }
}