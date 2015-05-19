#include "GeneticAlgorithm.h"

#include <algorithm>
#include <time.h>

#include "Common.h"

const GeneticAlgorithm::Rate kCrossoverRate = 70.0f;
const GeneticAlgorithm::Rate kMutationRate = 0.1f;
const uint32_t kElitismSize = 2;
const uint32_t kNumGenerations = 100;
const uint32_t kPopulationSize = 100;

GeneticAlgorithm::Solution *GenRandomSolution()
{
    auto *new_solution = new GeneticAlgorithm::Solution();

    for (int i = 0, size = new_solution->genome().size(); i < size; ++i)
    {
        new_solution->genome().set_random(i);
    }

    new_solution->CalcFitness();
    return new_solution;
}

GeneticAlgorithm::GeneticAlgorithm() :
    num_generation_(kNumGenerations),
    population_size_(kPopulationSize),
    selection_mask_(TOURNAMENT | ONE_WAY_TOURNAMENT | ELITISM),
    population_(Solution::compare),
    elitism_size_(kElitismSize),
    mutation_rate_(kMutationRate),
    crossover_rate_(kCrossoverRate),
    solution_factory_(GenRandomSolution),
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

    return population_size_ = population_size;
}

GeneticAlgorithm::Solution* GeneticAlgorithm::Run()
{
    // Initialize random seed
    srand((uint32_t)time(NULL));
    Loop();
    return *population_.begin();
}

void GeneticAlgorithm::Loop()
{
    uint32_t actual_generation = 0;
    GenPopulation();

    while (actual_generation < num_generation_ && !Stop())
    {
        Selection();
        actual_generation++;
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
        population_.insert(solution_factory_());
    population_array_.assign(ALL(population_));
}

void GeneticAlgorithm::Selection()
{
    SolutionSet new_population(Solution::compare);

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
    population_.insert(ALL(new_population));
    population_array_.insert(population_array_.begin(), ALL(new_population));
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
    Rate mutation_rate = owner_->mutation_rate();
    Rate crossover_rate = owner_->crossover_rate();
    
    while (population.size() < population_size)
    {
        if (owner_->selection_mask_ & ONE_WAY_TOURNAMENT)
        {
            SolutionSet tournament_1 = SolutionTournament();
            SolutionSet tournament_2 = SolutionTournament();
            auto entity_1 = *tournament_1.begin();
            auto entity_2 = *tournament_2.begin();
            float cross_over_p = frand();

            if (cross_over_p <= crossover_rate)
            {
                Solution** children = entity_1->Crossover(entity_2);
                children[0]->Mutation(mutation_rate);
                children[1]->Mutation(mutation_rate);
                population.insert({ children[0], children[1] });
            }
            else
            {
                Solution *child_1 = entity_1->clone();
                Solution *child_2 = entity_2->clone();

                child_1->Mutation(mutation_rate);
                child_2->Mutation(mutation_rate);
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
    SolutionSet tournament(Solution::compare);
    int pop_size = owner_->population_size();
    
    while (tournament.size() < tournemnt_size_)
    {
        int i = rand() % pop_size;
        tournament.insert(owner_->population_array_[i]); // Can repeat
    }

    return tournament;
}

bool GeneticAlgorithm::Stop()
{
    return false;
}