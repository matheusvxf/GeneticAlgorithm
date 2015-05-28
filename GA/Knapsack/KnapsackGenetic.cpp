#include "KnapsackGenetic.h"

#include <algorithm>
#include <random>
#include <chrono>       // std::chrono::system_clock

#include "Common.h"

static Solution *GenRandomSolution(GeneticAlgorithm &algorithm_manager);

Solution *GenRandomSolution(GeneticAlgorithm &algorithm_manager)
{
    auto new_solution = new KnapsackSolution();
    auto &manager = *static_cast<KnapsackGeneticAlgorithm*>(&algorithm_manager);

    new_solution->genome().set_size(manager.num_items());
    new_solution->genome().Randomize(manager);
    new_solution->CalcFitness(algorithm_manager);
    return new_solution;
}

KnapsackGene::KnapsackGene()
{
    set_random();
}

KnapsackGene::KnapsackGene(const KnapsackGene& number) : bit_(number.bit_) {}

Gene* KnapsackGene::clone() const
{
    return new KnapsackGene(*this);
}

Gene& KnapsackGene::Mutate()
{
    bit_ = !bit_;
    return *this;
}

Gene& KnapsackGene::set_random()
{
    bit_ = (rand() % 100) < 50 ? 0 : 1;
    return *this;
}

KnapsackGenome::KnapsackGenome() : IGenomeGeneIndependent() {}

KnapsackGenome::KnapsackGenome(const KnapsackGenome& genome) : IGenomeGeneIndependent(genome) {}

Genome *KnapsackGenome::clone() const
{
    return new KnapsackGenome(*this);
}

KnapsackSolution::KnapsackSolution()
{
    genome_ = new KnapsackGenome();
}

KnapsackSolution::KnapsackSolution(const KnapsackSolution& solution) : IHasInvidualMutation(solution) {}

Solution *KnapsackSolution::clone() const
{
    return new KnapsackSolution(*this);
}

float KnapsackSolution::CalcFitness(GeneticAlgorithm &algorithm_manager)
{
    auto &manager = *static_cast<KnapsackGeneticAlgorithm*>(&algorithm_manager);
    auto &knapsack = manager.knapsack();
    std::vector< int > vec;
    int num_genes = genome_->size();
    int weight = 0;
    fitness_ = 0.0f;
    
    for (int i = 0; i < num_genes; ++i)
    {
        Bit &bit = ((KnapsackGene*)&genome_->gene(i))->bit();
        if (bit == true)
        {
            vec.push_back(i); // Store items in the knapsack to remove if weight is exceeded
            fitness_ += knapsack.value(i);
            weight += knapsack.weight(i);
        }
    }

    if (weight > knapsack.capacity())
    {
        auto seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
        std::shuffle(ALL(vec), std::default_random_engine(seed));

        // Randomly remove items from the knapsack
        while (weight > knapsack.capacity())
        {
            int i = vec.back(); vec.pop_back();

            static_cast<KnapsackGene*>(&genome_->gene(i))->Mutate();
            fitness_ -= knapsack.value(i);
            weight -= knapsack.weight(i);
        }
    }

    return fitness_;
}

KnapsackGeneticAlgorithm::KnapsackGeneticAlgorithm()
{
    set_solution_factory_(GenRandomSolution);
    set_time_output_file(kKnapsackTimeFile);
    set_statistic_output_file(kKnapsackStatistFile);
    GeneticAlgorithmWrapper::prepare();
}

KnapsackGeneticAlgorithm::~KnapsackGeneticAlgorithm()
{
}

void KnapsackGeneticAlgorithm::set_knapsack(Knapsack &knapsack)
{
    num_items_ = knapsack.num_items();
    knapsack_ = &knapsack;
}