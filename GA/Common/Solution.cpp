#include "Solution.h"
#include "Common.h"
#include "GeneticAlgorithm.h"

Solution::Solution() : fitness_(0.0f) {}

Solution::Solution(const Solution& solution) : fitness_(solution.fitness_)
{
    genome_ = solution.genome_->clone();
}

Solution::~Solution()
{
    delete genome_;
}

bool Solution::compare(Solution *lhs, Solution *rhs)
{
    return lhs->fitness() > rhs->fitness();
}

Solution** Solution::Crossover(const Solution* s) const
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
        child_1->genome_->set_gene(i, s->genome_->gene(i));
        i++;
    }

    while (i < gnm_size)
    {
        child_2->genome_->set_gene(i, s->genome_->gene(i));
        i++;
    }

    result[0] = child_1;
    result[1] = child_2;
    return result;
}

Solution& IHasInvidualMutation::Mutation(GeneticAlgorithm& manager)
{
    auto genome = static_cast<IGenomeGeneIndependent*>(genome_);
    GeneticAlgorithm::Rate mutation_rate = manager.mutation_rate();

    for (int i = 0, size = genome_->size(); i < size; ++i)
    {
        float value = frand();
        if (value <= mutation_rate)
            genome->Mutate(i);
    }

    return (*this);
}