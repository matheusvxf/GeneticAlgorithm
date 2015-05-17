#include "GeneticAlgorithm.h"

#include <algorithm>
#include <time.h>

#include "Common.h"


float GeneticAlgorithm::crossover_rate_ = 0.0f;
float GeneticAlgorithm::mutation_rate_ = 0.0f;

uint32_t BitArray::set_size(uint32_t size)
{
    size_ = size;
    array_.resize(DivideCeil(size, 64));
}

Solution::Solution() : fitness_(0.0f) {}

Solution::Solution(const Genome &genome) : genome_(genome), fitness_(0.0f) {}

void Solution::InitRandom()
{

}

bool Solution::compare(Solution *lhs, Solution *rhs)
{
    return lhs->fitness() < rhs->fitness();
}

Solution* Solution::CrossOver(const Solution* s) const
{
    Solution *cross_over = new Solution(this->genome_);
    uint32_t gnm_size = genome_.size();
    uint32_t break_point;
    
    srand((uint32_t)time(NULL)); 
    break_point = rand() % gnm_size;

    for (int i = break_point + 1; i < gnm_size; ++i)
        cross_over->genome_.set(i, s->genome_.get(i));

    cross_over->Mutation();
    return cross_over;
}

Solution& Solution::Mutation()
{
    uint32_t gnm_size = genome_.size();

    srand((uint32_t)time(NULL));

    for (int i = 0; i < gnm_size; ++i)
    {
        float value = frand();
        if (value <= GeneticAlgorithm::mutation_rate())
            genome_.flip(i);
    }
}

GeneticAlgorithm::GeneticAlgorithm() : actual_generation_(0),
    num_generation_(30),
    population_size_(100),
    selection_mask_(TOURNAMENT | ONE_WAY_TOURNAMENT | ELITISM),
    population_(Solution::compare),
    selection_(new Tournament(this))
{
}


GeneticAlgorithm::~GeneticAlgorithm()
{
    foreach(population_, it)
        delete *it;
    delete selection_;
}

int GeneticAlgorithm::set_population_size(int population_size)
{
    foreach(population_, entity)
        delete *entity;
    population_.clear();

    return population_size_ = population_size;
}

void GeneticAlgorithm::Run()
{
    Loop();
}

void GeneticAlgorithm::Loop()
{
    GenPopulation();

    actual_generation_ = 0;
    while (!Stop())
    {
        Selection();
        actual_generation_++;
    }
}

void GeneticAlgorithm::GenPopulation()
{
    for (int i = 0; i < population_size_; ++i)
    {
        population_.insert(factory_->get_random_solution());
    }
}

void GeneticAlgorithm::Selection()
{
    SolutionSet new_population;

    if (selection_mask_ & ELITISM)
    {
        auto it = population_.begin();
        int limite = 2, i = 0;

        while (i < limite && it != population_.end())
        {
            auto entity = *it;
            new_population.insert(entity->clone());
            it++;
            i++;
        }
    }

    if (selection_mask_ & TOURNAMENT)
    {
        selection_->Select(new_population);
    }
    else
    {
        // TODO
    }

    foreach(population_, it)
        delete *it;
    population_.clear();
    population_.insert(all(new_population));
}

GeneticAlgorithm::Selection::Selection(const GeneticAlgorithm *owner) : owner_(owner) {}

void GeneticAlgorithm::Tournament::Select(SolutionSet &population)
{
    SolutionSet new_population;
    SolutionVector vec(all(owner_->population_));
    uint32_t population_size = owner_->population_size();
    float cross_over;

    srand((uint32_t)time(NULL));
    cross_over = frand();
    
    while (new_population.size() < population_size)
    {
        SolutionSet tournament;

        while (tournament.size() < tournemnt_size_)
        {
            tournament.insert(vec[rand() % population_size]); // Can repeat
        }

        if (owner_->selection_mask_ & ONE_WAY_TOURNAMENT)
        {
            auto it = tournament.begin();
            auto entity_1 = *it++;
            auto entity_2 = *it++;

            cross_over = frand();
            if (cross_over <= GeneticAlgorithm::crossover_rate())
                new_population.insert(entity_1->CrossOver(entity_2));
        }
        else
        {
            // TODO
        }
    }
}

bool GeneticAlgorithm::Stop()
{
    return actual_generation_ > num_generation_;
}