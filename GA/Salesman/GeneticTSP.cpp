#include "GeneticTSP.h"

#include <algorithm>
#include <random>
#include <chrono>       // std::chrono::system_clock

#include "Common.h"

/*
static GeneticAlgorithm::Solution *GenRandomSolution(GeneticAlgorithm *algorithm_manager);

GeneticAlgorithm::Solution *GenRandomSolution(GeneticAlgorithm *algorithm_manager)
{
    auto *new_solution = new TSPSolution();
    auto *manager = (TSPGeneticAlgorithm*)algorithm_manager;

    new_solution->genome().set_size(manager->num_items());
    new_solution->genome().Randomize();
    new_solution->CalcFitness(*algorithm_manager);
    return new_solution;
}

TSPGene::TSPGene()
{
    set_random();
}

TSPGene::TSPGene(const TSPGene& number) : bit_(number.bit_) {}

Gene* TSPGene::clone() const
{
    return new TSPGene(*this);
}

Gene& TSPGene::Mutate()
{
    bit_ = !bit_;
    return *this;
}

Gene& TSPGene::set_random()
{
    bit_ = (rand() % 100) < 50 ? 0 : 1;
    return *this;
}

TSPGenome::TSPGenome(uint32_t size) : Genome(size) {}

TSPGenome::TSPGenome(const TSPGenome& genome) : Genome(genome) {}

Genome *TSPGenome::clone() const
{
    return new TSPGenome(*this);
}

TSPSolution::TSPSolution()
{
    genome_ = new TSPGenome(kGenomeSize);
}

TSPSolution::TSPSolution(const TSPSolution& solution) : Solution(solution) {}

GeneticAlgorithm::Solution *TSPSolution::clone() const
{
    return new TSPSolution(*this);
}



float TSPSolution::CalcFitness(const GeneticAlgorithm &algorithm_manager)
{
    TSPGeneticAlgorithm *manager = (TSPGeneticAlgorithm*)&algorithm_manager;
    TSP &TSP = manager->TSP();
    std::vector< int > vec;
    int num_genes = genome_->size();
    int weight = 0;
    fitness_ = 0.0f;


    for (int i = 0; i < num_genes; ++i)
    {
        Bit bit = ((TSPGene*)&genome_->gene(i))->bit();
        if (bit == true)
        {
            vec.push_back(i); // Store items in the TSP to remove if weight is exceeded
            fitness_ += TSP.value(i);
            weight += TSP.weight(i);
        }
    }

    if (weight > TSP.capacity())
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(ALL(vec), std::default_random_engine(seed));

        // Randomly remove items from the TSP
        while (weight > TSP.capacity())
        {
            int i = vec.back(); vec.pop_back();

            genome_->gene(i).Mutate();
            fitness_ -= TSP.value(i);
            weight -= TSP.weight(i);
        }
    }

    return fitness_;
}

TSPGeneticAlgorithm::TSPGeneticAlgorithm()
{
    set_solution_factory_(GenRandomSolution);
}

TSPGeneticAlgorithm::~TSPGeneticAlgorithm()
{
}

void TSPGeneticAlgorithm::set_TSP(TSP &TSP)
{
    num_items_ = TSP.num_items();
    TSP_ = &TSP;
}*/