#include "GeneticAlgorithm.h"
#include "Common.h"

GeneticAlgorithm::Solution::Solution() : fitness_(0.0f) {}

GeneticAlgorithm::Solution::Solution(const Solution& solution) : fitness_(solution.fitness_)
{
    genome_ = solution.genome_->clone();
}

GeneticAlgorithm::Solution::~Solution()
{
    delete genome_;
}

bool GeneticAlgorithm::Solution::compare(Solution *lhs, Solution *rhs)
{
    return lhs->fitness() > rhs->fitness();
}

GeneticAlgorithm::Solution** GeneticAlgorithm::Solution::Crossover(const Solution* s) const
{
    Solution ** result = new Solution*[2];
    Solution *child_1 = this->clone();
    Solution *child_2 = this->clone();
    uint32_t gnm_size = genome_->size();
    uint32_t break_point;
    uint32_t i = 0;

    break_point = rand() % gnm_size;
    
    while (i <= break_point)
    {
        child_1->genome_->set(i, s->genome_->get(i));
        i++;
    }

    while (i < gnm_size)
    {
        child_2->genome_->set(i, s->genome_->get(i));
        i++;
    }

    child_1->CalcFitness();
    child_2->CalcFitness();
    result[0] = child_1;
    result[1] = child_2;
    return result;
}

GeneticAlgorithm::Solution& GeneticAlgorithm::Solution::Mutation(Rate mutation_rate)
{
    for (int i = 0, size = genome_->size(); i < size; ++i)
    {
        float value = frand();
        if (value <= mutation_rate)
            genome_->Mutate(i);
    }

    CalcFitness();
    return (*this);
}