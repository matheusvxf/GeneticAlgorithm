#pragma once

#include <vector>

#include "Common.h"

class Solution
{
    
public:
    Solution();

    void InitRandom();
    virtual float fitness() = 0;
    virtual Solution* get_random_solution() = 0; 
};

class GeneticAlgorithm
{
private:
    enum Selection
    {
        ROULETTE_WHEEL = (1 << 0),
        STOCHASTIC_UNIVERSAL_SAMPLING = (1 << 1),
        TOURNAMENT = (1 << 2),
        TRUNCATION = (1 << 3),
        ELITISM = (1 << 4)
    };

    typedef uint64_t SelectionMask;
private:
    int num_generation_;
    int actual_generation_;
    int population_size_;
    SelectionMask mask_;
    float crossover_rate_;
    float mutation_rate_;
    std::vector< Solution* > population_;
    std::vector< float > fitness_;
    Solution *factory_;

    void Loop();
    void GenPopulation();
    void CalcFitness();
    void Selection();
    void Crossover();
    void Reproduction();
    void Mutation();
    void Elitism();
    virtual bool Stop(); // Test if should stop. It can delegate task to specific problems
public:
    GeneticAlgorithm();
    virtual ~GeneticAlgorithm();

    void Run();

    Solution *set_factory(Solution *factory) { return factory_ = factory; }
    int set_population_size(int population_size);
    inline int set_num_generation_(int num_generation) { return num_generation_ = num_generation; }
};

