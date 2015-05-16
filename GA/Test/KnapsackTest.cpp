#include "KnapsackTest.h"

namespace KnapsackTest
{
    bool ReadNextTestCase(Knapsack &knapsack)
    {
        int num_items, capacity;

        scanf_s("%d %d\n", &num_items, &capacity);

        if (num_items == 0)
            return false;

        knapsack.set_num_items(num_items);
        knapsack.set_capacity(capacity);

        for (int i = 0; i < num_items; ++i)
        {
            int value, weight;

            scanf_s("%d %d\n", &value, &weight);
            knapsack.set_item(i, value, weight);
        }

        return true;
    }
}