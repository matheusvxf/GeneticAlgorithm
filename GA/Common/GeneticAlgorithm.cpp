#include "GeneticAlgorithm.h"

#include <algorithm>
#include <time.h>

#include "Common.h"

void Solution::InitRandom()
{

}

GeneticAlgorithm::GeneticAlgorithm() : actual_generation_(0),
    num_generation_(30),
    population_size_(100)
{
}


GeneticAlgorithm::~GeneticAlgorithm()
{
    foreach(population_, entity)
        delete *entity;
}

int GeneticAlgorithm::set_population_size(int population_size)
{
    for (int i = 0; i < population_size_; ++i)
        delete population_[i];
    population_.resize(population_size);
    std::fill(all(population_), nullptr);

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
        CalcFitness();
        Selection();
        actual_generation_++;
    }
}

void GeneticAlgorithm::CalcFitness()
{
    for (int i = 0; i < population_size_; ++i)
        fitness_[i] = population_[i]->fitness();
}

void GeneticAlgorithm::GenPopulation()
{
    for (int i = 0; i < population_size_; ++i)
    {
        if (population_[i] != nullptr)
            delete population_[i];
        population_[i] = factory_->get_random_solution();
    }
}

void GeneticAlgorithm::Selection()
{
    std::vector< Solution* > new_population;

    srand((uint32_t)time(NULL));

    while (new_population.size() < population_size_)
    {
        Solution *s_1, *s_2;
        
        
    }

    for (int i = 0; i < population_size_; ++i)
    {
        delete population_[i];
        population_[i] = new_population[i];
    }
}

bool GeneticAlgorithm::Stop()
{
    return actual_generation_ > num_generation_;
}