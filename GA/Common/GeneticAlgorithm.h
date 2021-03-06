#pragma once

#include <vector>
#include <set>
#include <bitset>

#include "Common.h"
#include "Genome.h"
#include "Solution.h"

class GeneticAlgorithm
{
public:
    typedef float Rate;
    typedef bool(*SolutionComparator)(Solution*, Solution*);
    typedef std::multiset< Solution*, SolutionComparator> SolutionSet;
    typedef std::vector< Solution* > SolutionVector;
    typedef Solution*(*SolutionFactory)(GeneticAlgorithm &algorithm_manager);

private:
    typedef uint64_t SelectionMask;
    

    enum SELECTION_MASK
    {
        ROULETTE_WHEEL = (1 << 0),
        STOCHASTIC_UNIVERSAL_SAMPLING = (1 << 1),
        REWARD_BASED = (1 << 2),
        TOURNAMENT = (1 << 3),
        ONE_WAY_TOURNAMENT = (1 << 4),
        TRUNCATION = (1 << 5),
        ELITISM = (1 << 6)
    };

    class Selection
    {
    protected:
        friend class GeneticAlgorithm;
        GeneticAlgorithm *owner_;

        Selection(GeneticAlgorithm *owner);

        virtual void Select(SolutionSet &population) = 0;
    };

    class Tournament : Selection
    {
        friend class GeneticAlgorithm;

        float p_; // Probability of selecting the solution of higher fitness
        uint32_t tournemnt_size_;
    public:

        Tournament(GeneticAlgorithm* owner) : Selection(owner), tournemnt_size_(2) {}

        void Select(SolutionSet &population);
        SolutionSet SolutionTournament();
    };

protected:
    Rate crossover_rate_;
    Rate mutation_rate_;
    uint32_t elitism_size_;
    uint32_t num_generation_;
    uint32_t population_size_;
    SelectionMask selection_mask_;
    SolutionSet population_;
    SolutionVector population_array_;
    SolutionFactory solution_factory_;
    Selection *selection_;

protected:
    void Elitism(SolutionSet &population);
    virtual void Selection();
    virtual void GenPopulation();
    virtual void Loop();
    virtual bool Stop(); // Test if should stop. It can delegate task to specific problems
public:
    GeneticAlgorithm();
    GeneticAlgorithm(SolutionComparator compare);
    virtual ~GeneticAlgorithm();

    virtual SolutionVector& Run();
    virtual SolutionComparator Compare() const;

    int set_population_size(int population_size);

    inline SolutionFactory& set_solution_factory_(SolutionFactory factory) { return solution_factory_ = factory; }
    inline int set_num_generation_(int num_generation) { return num_generation_ = num_generation; }
    inline uint32_t population_size() const { return population_size_; }
    inline float mutation_rate() const { return mutation_rate_; }
    inline float set_mutation_rate(float mutation_rate) { return mutation_rate_ = mutation_rate; }
    inline float crossover_rate() const { return crossover_rate_; }
    inline float set_crossover_rate(float crossover_rate) { return crossover_rate_ = crossover_rate; }
};

