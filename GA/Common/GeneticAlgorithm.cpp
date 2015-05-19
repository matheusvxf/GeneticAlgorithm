#include "GeneticAlgorithm.h"

#include <algorithm>
#include <time.h>

#include "Common.h"


float GeneticAlgorithm::crossover_rate_ = 70.0f;
float GeneticAlgorithm::mutation_rate_ = 0.1f;

uint32_t BitArray::set_size(uint32_t size)
{
    array_.resize(DivideCeil(size, 64));
    return size_ = size;
}

Solution::Solution() : fitness_(0.0f) {}

Solution::Solution(const Genome &genome) : genome_(genome), fitness_(0.0f) {
    fitness_;
}

bool Solution::compare(Solution *lhs, Solution *rhs)
{
    return lhs->fitness() < rhs->fitness();
}

float Solution::CalcFitness()
{
    fitness_ = 0.0f;

    for (int i = 0, size = genome_.size(); i < size; ++i)
    {
        fitness_ += genome_.get(i);
    }

    return fitness_;
}

Solution** Solution::CrossOver(const Solution* s) const
{
    Solution ** result = new Solution*[2];
    Solution *child_1 = new Solution(this->genome_);
    Solution *child_2 = new Solution(s->genome_);
    uint32_t gnm_size = genome_.size();
    uint32_t break_point;
    
    break_point = rand() % gnm_size;

    for (uint32_t i = break_point + 1; i < gnm_size; ++i)
    {
        child_1->genome_.set(i, s->genome_.get(i));
        child_2->genome_.set(i, this->genome_.get(i));
    }

    child_1->CalcFitness();
    child_2->CalcFitness();
    result[0] = child_1;
    result[1] = child_2;
    return result;
}

Solution& Solution::Mutation()
{
    for (int i = 0, size = genome_.size(); i < size; ++i)
    {
        float value = frand();
        if (value <= GeneticAlgorithm::mutation_rate())
            genome_.flip(i);
    }

    return (*this);
}

Solution *Solution::gen_random_solution()
{
    Solution *new_solution = new Solution();

    for (int i = 0, size = genome_.size(); i < size; ++i)
    {
        new_solution->genome_.set_random(i);
    }

    new_solution->CalcFitness();
    return new_solution;
}

GeneticAlgorithm::GeneticAlgorithm() : actual_generation_(0),
    num_generation_(30),
    population_size_(100),
    selection_mask_(TOURNAMENT | ONE_WAY_TOURNAMENT | ELITISM),
    population_(Solution::compare),
    elitism_size_(2)
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
    foreach(population_, it)
    if (*it != nullptr)
        delete *it;
    population_.clear();
    population_array_.resize(population_size_);
    for (uint32_t i = 0; i < population_size_; ++i)
        population_.insert(factory_->gen_random_solution());
    population_array_.insert(population_array_.begin(), all(population_));
}

void GeneticAlgorithm::Selection()
{
    SolutionSet new_population;

    // Initialize random seed
    srand((uint32_t)time(NULL));

    if (selection_mask_ & ELITISM)
    {
        Elitism(new_population);
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
    population_array_.insert(population_array_.begin(), all(new_population));
}

void GeneticAlgorithm::Elitism(SolutionSet &population)
{
    auto it = population_.begin();
    int limite = elitism_size_, i = 0;

    while (i < limite && it != population_.end())
    {
        auto entity = *it;
        population.insert(entity->clone());
        it++;
        i++;
    }
}

GeneticAlgorithm::Selection::Selection(const GeneticAlgorithm *owner) : owner_(owner) {}

void GeneticAlgorithm::Tournament::Select(SolutionSet &population)
{
    uint32_t population_size = owner_->population_size();
    
    while (population.size() < population_size)
    {
        if (owner_->selection_mask_ & ONE_WAY_TOURNAMENT)
        {
            SolutionSet tournament_1 = SolutionTournament();
            SolutionSet tournament_2 = SolutionTournament();
            auto entity_1 = *tournament_1.begin();
            auto entity_2 = *tournament_2.begin();
            float cross_over_p = frand();

            if (cross_over_p <= GeneticAlgorithm::crossover_rate())
            {
                Solution** children = entity_1->CrossOver(entity_2);
                children[0]->Mutation();
                children[1]->Mutation();
                population.insert({ children[0], children[1] });
            }
            else
            {
                Solution *child_1 = entity_1->clone();
                Solution *child_2 = entity_2->clone();

                child_1->Mutation();
                child_2->Mutation();
                population.insert({ child_1, child_2 });
            }
        }
        else
        {
            // TODO
        }
    }
}

GeneticAlgorithm::SolutionSet GeneticAlgorithm::Tournament::SolutionTournament()
{
    SolutionSet tournament;
    
    while (tournament.size() < tournemnt_size_)
        tournament.insert(owner_->population_array_[rand() % owner_->population_size()]); // Can repeat

    return tournament;
}

bool GeneticAlgorithm::Stop()
{
    return actual_generation_ > num_generation_;
}