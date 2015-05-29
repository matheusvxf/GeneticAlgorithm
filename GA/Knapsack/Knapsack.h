#pragma once

#include <vector>

#include "KnapsackGenetic.h"
#include "TestWrapper.h"
#include "Common.h"

class Knapsack : public SolverInterface
{
private:
    KnapsackGeneticAlgorithm ga_manager_;
    std::string generation_statistic_file_;
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

    int SolveDynamicProgramming();
    GeneticAlgorithm::SolutionVector& SolveGeneticAlgorithm();
    bool ReadNextTestCase(std::fstream &fs);
    std::string problem_size() const { return int2str(items_.size()) + " " + int2str(knapsack_capacity_); }

    std::string statistic_file() const { return kKnapsackStatistFile; }
    std::string default_time_file() const { return kKnapsackTimeFile; }
    std::string test_file() const { return KKnapsackTestFile; }
    std::string name() const { return "knapsack"; }
    std::string& set_generation_statistic_file(const std::string& file) { return generation_statistic_file_ = file; }


    inline void set_num_items(int num_items) { items_.resize(num_items); }
    inline void set_capacity(int capacity) { knapsack_capacity_ = capacity; }
    inline void set_item(int item_id, int value, int weight) { items_[item_id].value = value; items_[item_id].weight = weight; }
    inline int num_items() const { return items_.size(); }
    inline int weight(int i) const { return items_[i].weight; }
    inline int value(int i) const { return items_[i].value; }
    inline int capacity() const { return knapsack_capacity_; }
};

