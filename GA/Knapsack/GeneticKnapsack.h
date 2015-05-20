#pragma once

#include "GeneticAlgorithm.h"
#include "Knapsack.h"

class KnapsackGene : public Gene
{
    typedef bool Bit;

    Bit bit_;

    virtual Gene& Mutate();
    virtual Gene& set_random();
    virtual Gene* clone() const;

public:
    KnapsackGene();
    KnapsackGene(const KnapsackGene& gene);
    inline Bit bit() { return bit_; }
};

class KnapsackGenome : public Genome
{
public:
    KnapsackGenome(uint32_t size);
    KnapsackGenome(const KnapsackGenome& genome);

    Gene *RandomGeneFactory() { return new KnapsackGene(); };
    Genome *clone() const;
};

class KnapsackSolution : public GeneticAlgorithm::Solution
{
public:
    KnapsackSolution();
    KnapsackSolution(const KnapsackSolution& solution);

    virtual Solution* clone() const;

    virtual Fitness CalcFitness(const GeneticAlgorithm &algorithm_manager);

};

class KnapsackGeneticAlgorithm : public GeneticAlgorithm
{
private:
    int capacity_;
    int num_items_;
    Knapsack *knapsack_; // lent

public:

    KnapsackGeneticAlgorithm();
    virtual ~KnapsackGeneticAlgorithm();

    int set_capacity(int capacity) { return capacity_ = capacity; }
    void set_knapsack(Knapsack &knapsack);
    int num_items() { return num_items_; }
    int capacity() { return capacity_; }
    Knapsack &knapsack() { return *knapsack_; }
};
