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
        int weight_;
        int value_;

    public:
        inline int weight() const { return weight_; }
        inline int set_weight(int weight) { return weight_ = weight; }
        inline int value() const { return value_; }
        inline int set_value(int value) { return value_ = value; }
    };

    typedef std::vector< Item > KnapsackContainer;
private:
    KnapsackContainer items_;
    int knapsack_capacity_;
public:
    Knapsack();
    ~Knapsack();

    std::pair< int, std::set< int > > SolveDynamicProgramming();
    std::set<int> FindKnapsack(const std::vector< std::vector<int> > &m, int item, int weight);
    std::string SolveExactSolution();
    GeneticAlgorithm::SolutionVector& SolveGeneticAlgorithm();
    bool ReadNextTestCase(std::fstream &fs);
    std::string problem_size() const { return int2str(items_.size()) + " " + int2str(knapsack_capacity_); }

    std::string name() const { return "knapsack"; }
    std::string& set_generation_statistic_file(const std::string& file) { return generation_statistic_file_ = file; }


    inline void set_num_items(int num_items) { items_.resize(num_items); }
    inline void set_capacity(int capacity) { knapsack_capacity_ = capacity; }
    inline void set_item(int item_id, int value, int weight) { items_[item_id].set_value(value); items_[item_id].set_weight(weight); }
    inline int num_items() const { return items_.size(); }
    inline int weight(int i) const { return items_[i].weight(); }
    inline int value(int i) const { return items_[i].value(); }
    inline int capacity() const { return knapsack_capacity_; }
    inline GeneticAlgorithm& ga_manager() { return ga_manager_; }


    static std::string ProblemGenerator(int num_items, int weight);
};

