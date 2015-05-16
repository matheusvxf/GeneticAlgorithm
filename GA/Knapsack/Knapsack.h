#pragma once

#include <vector>

class Knapsack
{
private:
    class Item
    {
        friend class Knapsack;
    private:
        int weight;
        int value;
    };

    std::vector< Item > items_;
    int knapsack_capacity_;
public:
    Knapsack();
    ~Knapsack();

    inline void set_num_items(int num_items) { items_.resize(num_items); }
    inline void set_capacity(int capacity) { knapsack_capacity_ = capacity; }
    inline void set_item(int item_id, int value, int weight) { items_[item_id].value = value; items_[item_id].weight = weight; }
    int SolveDynamicProgramming();
};

