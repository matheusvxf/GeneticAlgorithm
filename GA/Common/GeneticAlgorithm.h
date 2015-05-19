#pragma once

#include <vector>
#include <set>
#include <bitset>

#include "Common.h"
#include "Genome.h"

class GeneticAlgorithm
{
public:
    class Solution;

    typedef float Rate;
    typedef std::multiset< Solution*, bool(*)(Solution*, Solution*)> SolutionSet;
    typedef Solution*(*SolutionFactory)();

    class Solution
    {
    protected:
        Genome *genome_;
        Fitness fitness_;
    public:
        Solution();
        Solution(const Solution& genome);
        virtual ~Solution();

        static bool compare(Solution *a, Solution *b);
        static Solution* GenRandomSolution();

        Solution** Crossover(const Solution *s) const;
        Solution& Mutation(Rate mutation_rate);

        inline Genome& genome() const { return *genome_; }
        inline Fitness fitness() { return fitness_; }

        virtual Solution* clone() const = 0;
        virtual float CalcFitness() = 0;
    };

private:
    typedef uint64_t SelectionMask;
    typedef std::vector< Solution* > SolutionVector;
    

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
        friend class GeneticAlgorithm;
        const GeneticAlgorithm *owner_;

        Selection(const GeneticAlgorithm *owner);

        virtual void Select(SolutionSet &population) = 0;
    };

private:
    Rate crossover_rate_;
    Rate mutation_rate_;
    uint32_t elitism_size_;
    uint32_t num_generation_;
    uint32_t population_size_;
    SelectionMask selection_mask_;
    SolutionSet population_;
    SolutionVector population_array_;
    std::vector< Fitness > fitness_;
    SolutionFactory solution_factory_;
    Selection *selection_;

    void Loop();
    void GenPopulation();
    void CalcFitness();
    void Selection();
    void Elitism(SolutionSet &population);
    void Crossover();
    void Mutation();
    void Elitism();
    virtual bool Stop(); // Test if should stop. It can delegate task to specific problems
public:
    GeneticAlgorithm();
    virtual ~GeneticAlgorithm();

    Solution* Run();

    int set_population_size(int population_size);

    inline SolutionFactory& set_solution_factory_(SolutionFactory factory) { return solution_factory_ = factory; }
    inline int set_num_generation_(int num_generation) { return num_generation_ = num_generation; }
    inline uint32_t population_size() const { return population_size_; }
    inline float mutation_rate() const { return mutation_rate_; }
    inline float crossover_rate() const { return crossover_rate_; }

private:
    class Tournament : Selection
    {
        friend class GeneticAlgorithm;

        float p_; // Probability of selecting the solution of higher fitness
        uint32_t tournemnt_size_;
    public:

        Tournament(const GeneticAlgorithm* owner) : Selection(owner), tournemnt_size_(2) {}

        void Select(SolutionSet &population);
        SolutionSet SolutionTournament();
    };
};

