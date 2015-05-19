#pragma once

#include "GeneticAlgorithm.h"

class SolutionKnapsack : public GeneticAlgorithm::Solution
{
    virtual Fitness CalcFitness();

};

class GeneticKnapsack
{
public:
    GeneticKnapsack();
    ~GeneticKnapsack();
};

