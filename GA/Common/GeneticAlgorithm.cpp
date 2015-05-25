#include "GeneticAlgorithm.h"

#include <algorithm>
#include <time.h>
#include <chrono>

#include "Common.h"
#include "Log.h"

const GeneticAlgorithm::Rate kCrossoverRate = 70.0f;
const GeneticAlgorithm::Rate kMutationRate = 0.1f;
const uint32_t kElitismSize = 2;
const uint32_t kNumGenerations = 100;
const uint32_t kPopulationSize = 1000;

// Private functions
inline static float AverageFitness(const GeneticAlgorithm::SolutionVector& population);
inline static float VarianceFitness(const GeneticAlgorithm::SolutionVector& population);
inline static float StandardDeviation(const GeneticAlgorithm::SolutionVector& population);
inline static float BestFitness(const GeneticAlgorithm::SolutionVector& population);
inline static float WorstFitness(const GeneticAlgorithm::SolutionVector& population);
inline static void LogPopulationFitness(const GeneticAlgorithm::SolutionVector& population);

inline float AverageFitness(const GeneticAlgorithm::SolutionVector& population)
{
    float sum = 0.0f;

    foreach(population, it)
    {
        sum += (*it)->fitness();
    }
    return sum / static_cast<float>(population.size());
}

inline float VarianceFitness(const GeneticAlgorithm::SolutionVector& population)
{
    float avr = AverageFitness(population);
    float sum = 0.0f;

    foreach(population, it)
    {
        float diff = (*it)->fitness() - avr;
        sum += diff * diff;
    }
    return sum / static_cast<float>(population.size());
}

inline float StandardDeviation(const GeneticAlgorithm::SolutionVector& population)
{
    return sqrt(VarianceFitness(population));
}

inline float BestFitness(const GeneticAlgorithm::SolutionVector& population)
{
    return (*population.begin())->fitness();
}

inline float WorstFitness(const GeneticAlgorithm::SolutionVector& population)
{
    return (*(population.end() - 1))->fitness();
}

inline static void LogPopulationFitness(Log& log, const GeneticAlgorithm::SolutionVector& population)
{
    float avr, sdv, best, worst;
    std::fstream &fs = log.fstream();
    avr = AverageFitness(population);
    best = BestFitness(population);
    worst = WorstFitness(population);
    sdv = StandardDeviation(population);
    fs << best << " " << worst << " " << avr << " " << sdv << std::endl;
}

GeneticAlgorithm::GeneticAlgorithm() : GeneticAlgorithm(Compare()) {}

GeneticAlgorithm::GeneticAlgorithm(SolutionComparator comparator) : 
    num_generation_(kNumGenerations),
    population_size_(kPopulationSize),
    selection_mask_(TOURNAMENT | ONE_WAY_TOURNAMENT | ELITISM),
    population_(comparator),
    elitism_size_(kElitismSize),
    mutation_rate_(kMutationRate),
    crossover_rate_(kCrossoverRate),
    solution_factory_(nullptr),
    selection_(new Tournament(this)),
    statistic_output_file_(kStatisticFile),
    time_output_file_(kTimeFile)
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

GeneticAlgorithm::SolutionComparator GeneticAlgorithm::Compare() const
{
    return Solution::compare;
}

Solution* GeneticAlgorithm::Run()
{
    Log log; log.open(time_output_file());
    // Initialize random seed
    srand((uint32_t)time(NULL));
    auto start = std::chrono::system_clock::now();
    Loop();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start);
    printf("%lld\n", duration.count());
    log.close();
    return *population_.begin();
}

void GeneticAlgorithm::Loop()
{
    Log log; log.open(statistic_output_file());
    uint32_t actual_generation = 0;
    GenPopulation();

    LogPopulationFitness(log, population_array_);

    while (actual_generation < num_generation_ && !Stop())
    {
        Selection();
        actual_generation++;
        LogPopulationFitness(log, population_array_);
    }

    log.close();
}

void GeneticAlgorithm::GenPopulation()
{
    foreach(population_, it)
    if (*it != nullptr)
        delete *it;
    population_.clear();
    population_array_.resize(population_size_);
    for (uint32_t i = 0; i < population_size_; ++i)
        population_.insert(solution_factory_(*this));
    population_array_.assign(ALL(population_));
}

void GeneticAlgorithm::Selection()
{
    SolutionSet new_population(Compare());

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
    population_array_.assign(ALL(new_population));
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

GeneticAlgorithm::Selection::Selection(GeneticAlgorithm *owner) : owner_(owner) {}

void GeneticAlgorithm::Tournament::Select(SolutionSet &population)
{
    uint32_t population_size = owner_->population_size();
    Rate crossover_rate = owner_->crossover_rate();
    
    while (population.size() < population_size)
    {
        if (owner_->selection_mask_ & ONE_WAY_TOURNAMENT)
        {
            SolutionSet tournament_1 = SolutionTournament();
            SolutionSet tournament_2 = SolutionTournament();
            Solution* entity[] = { *tournament_1.begin(), *tournament_2.begin() };
            float cross_over_p = frand();

            if (cross_over_p <= crossover_rate)
            {
                Solution** children = entity[0]->Crossover(entity[1]);
                for (int i = 0; i < 2; ++i)
                {
                    children[i]->Mutation(*owner_);
                    children[i]->CalcFitness(*owner_);
                }
                
                population.insert({ children[0], children[1] });
                delete[]children;
            }
            else
            {
                for (int i = 0; i < 2; ++i)
                {
                    Solution *child = entity[i]->clone();
                    child->Mutation(*owner_);
                    child->CalcFitness(*owner_);
                    population.insert(child);
                }
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
    SolutionSet tournament(owner_->Compare());
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