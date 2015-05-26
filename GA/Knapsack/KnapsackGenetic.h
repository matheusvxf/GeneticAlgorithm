#pragma once

#include "GeneticAlgorithmWrapper.h"
#include "Knapsack.h"

class KnapsackGene : public IGeneIndependent
{
    typedef bool Bit;

    Bit bit_;

    virtual Gene& set_random();
    virtual Gene* clone() const;

public:
    KnapsackGene();
    KnapsackGene(const KnapsackGene& gene);

    virtual Gene& Mutate();

    inline Bit& bit() { return bit_; }
};

class KnapsackGenome : public IGenomeGeneIndependent
{
public:
    KnapsackGenome();
    KnapsackGenome(const KnapsackGenome& genome);

    Gene *RandomGeneFactory() { return new KnapsackGene(); };
    Genome *clone() const;
};

class KnapsackSolution : public IHasInvidualMutation
{
public:
    KnapsackSolution();
    KnapsackSolution(const KnapsackSolution& solution);

    virtual Solution* clone() const;

    virtual Fitness CalcFitness(GeneticAlgorithm &algorithm_manager);

};

class KnapsackGeneticAlgorithm : public GeneticAlgorithmWrapper
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
    int num_items() const { return num_items_; }
    int capacity() const { return capacity_; }
    const Knapsack& knapsack() const { return *knapsack_; }
};
