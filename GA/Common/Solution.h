#pragma once

#include "Genome.h"

class GeneticAlgorithm;

class Solution
{
protected:
    Genome *genome_;
    Fitness fitness_;
public:
    Solution();
    Solution(const Solution& genome);
    virtual ~Solution();

    inline Genome& genome() const { return *genome_; }
    inline Fitness fitness() { return fitness_; }

    static bool compare(Solution *a, Solution *b);
    static Solution* GenRandomSolution();

    virtual Solution** Crossover(const Solution *s) const;
    
    virtual Solution& Mutation(GeneticAlgorithm &manager) = 0;
    virtual Solution* clone() const = 0;
    virtual float CalcFitness(GeneticAlgorithm &algorithm_manager) = 0;
};

class IHasInvidualMutation : public Solution
{
public:
    IHasInvidualMutation() {}
    IHasInvidualMutation(const IHasInvidualMutation& solution) : Solution(solution) {}
    virtual Solution& Mutation(GeneticAlgorithm &manager);
};