#pragma once

#include <vector>

class Knapsack
{
public:

    class Item
    {
        friend class Knapsack;
    private:
        int weight;
        int value;
    };

    typedef std::vector< Item > KnapsackContainer;
private:
    KnapsackContainer items_;
    int knapsack_capacity_;
public:
    Knapsack();
    ~Knapsack();

    inline void set_num_items(int num_items) { items_.resize(num_items); }
    inline void set_capacity(int capacity) { knapsack_capacity_ = capacity; }
    inline void set_item(int item_id, int value, int weight) { items_[item_id].value = value; items_[item_id].weight = weight; }
    inline int num_items() const { return items_.size(); }
    inline int weight(int i) const { return items_[i].weight; }
    inline int value(int i) const { return items_[i].value; }
    inline int capacity() const { return knapsack_capacity_; }
    int SolveDynamicProgramming();
    int SolveGA();


};

