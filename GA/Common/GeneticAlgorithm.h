#pragma once

#include <vector>
#include <set>
#include <bitset>

#include "Common.h"

class Bitarray;
class Solution;
class GeneticAlgorithm;

class BitArray
{
    typedef std::vector< std::bitset< 64 > > BitArray_t;

    BitArray_t array_;
    uint32_t size_;

public:
    uint32_t set_size(uint32_t size);
    inline uint32_t size() const { return size_; }
    inline void assign(BitArray_t::iterator begin, BitArray_t::iterator end) { array_.assign(begin, end); }
    
    inline bit get(uint32_t i) const
    {
        int word = i / 64;
        int bit = i % 64;
        return array_[word][bit];
    }

    inline bit set(uint32_t i, bit value)
    {
        int word = i / 64;
        int bit = i % 64;
        return array_[word][bit] = value;
    }

    inline bit flip(uint32_t i)
    {
        int word = i / 64;
        int bit = i % 64;
        return array_[word][bit] = ~array_[word][bit];
    }
};

typedef BitArray Genome;

class Solution
{
    Genome genome_;
    float fitness_;
public:
    Solution();
    Solution(const Genome& genome);

    void InitRandom();
    static bool compare(Solution *a, Solution *b);

    virtual Solution* get_random_solution();
    virtual Solution* clone();

    Solution* CrossOver(const Solution *s) const;
    Solution& Mutation();

    inline float fitness() { return fitness_; }
};

class GeneticAlgorithm
{
private:
    typedef uint64_t SelectionMask;
    typedef std::set< Solution*, bool(*)(Solution*, Solution*)> SolutionSet;
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
    static float crossover_rate_;
    static float mutation_rate_;
    int num_generation_;
    int actual_generation_;
    uint32_t population_size_;
    SelectionMask selection_mask_;
    SolutionSet population_;
    std::vector< float > fitness_;
    Solution *factory_;
    Selection *selection_;

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

    inline uint32_t population_size() const { return population_size_; }
    static inline float mutation_rate() { return mutation_rate_; }
    static inline float crossover_rate() { return crossover_rate_; }

private:
    class Tournament : Selection
    {
        friend class GeneticAlgorithm;

        float p_; // Probability of selecting the solution of higher fitness
        uint32_t tournemnt_size_;
    public:

        Tournament(const GeneticAlgorithm* owner) : Selection(owner), tournemnt_size_(2) {}

        void Select(SolutionSet &population);
    };
};

