#include "GeneticTSP.h"

#include <algorithm>
#include <random>
#include <chrono>       // std::chrono::system_clock

#include "Common.h"

static GeneticAlgorithm::Solution *GenRandomSolution(GeneticAlgorithm &algorithm_manager);

GeneticAlgorithm::Solution *GenRandomSolution(GeneticAlgorithm &algorithm_manager)
{
    auto new_solution = new TSPSolution();
    auto manager = static_cast<const TSPGeneticAlgorithm*>(&algorithm_manager);

    new_solution->genome().set_size(manager->num_cities());
    new_solution->genome().Randomize(algorithm_manager);
    new_solution->CalcFitness(algorithm_manager);
    return new_solution;
}

TSPGene::TSPGene() {}

TSPGene::TSPGene(const TSPGene& number) : bit_(number.bit_) {}

Gene* TSPGene::clone() const
{
    return new TSPGene(*this);
}

TSPGenome::TSPGenome(uint32_t size) : Genome(size) {}

TSPGenome::TSPGenome(const TSPGenome& genome) : Genome(genome) {}

Genome *TSPGenome::clone() const
{
    return new TSPGenome(*this);
}

Genome& TSPGenome::Randomize(GeneticAlgorithm &algorithm_manager)
{
    auto *manager = static_cast<TSPGeneticAlgorithm*>(&algorithm_manager);
    auto &cities_array = manager->cities_array();
    int num_cities = manager->num_cities();
    auto seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
    
    std::shuffle(ALL(cities_array), std::default_random_engine(seed));

    for (int i = 0; i < num_cities; ++i)
        set_gene(i, i);

    return *this;
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

GeneticAlgorithm::Solution& TSPSolution::Mutation(GeneticAlgorithm& manager)
{
    

    return (*this);
}

float TSPSolution::CalcFitness(GeneticAlgorithm &algorithm_manager)
{
    TSPGeneticAlgorithm *manager = (TSPGeneticAlgorithm*)&algorithm_manager;
    Salesman &salesman = manager->salesman();
    std::vector< int > vec;
    int num_genes = genome_->size();
    int weight = 0;
    fitness_ = 0.0f;

    return fitness_;
}

TSPGeneticAlgorithm::TSPGeneticAlgorithm()
{
    set_solution_factory_(GenRandomSolution);
}

TSPGeneticAlgorithm::~TSPGeneticAlgorithm()
{
}

Salesman& TSPGeneticAlgorithm::set_salesman(Salesman &salesman)
{
    int num_cities = salesman.num_cities();
    salesman_ = &salesman;
    
    cities_array_.resize(num_cities);
    for (int i = 0; i < num_cities; ++i)
        cities_array_[i] = i;

    return *salesman_;
}