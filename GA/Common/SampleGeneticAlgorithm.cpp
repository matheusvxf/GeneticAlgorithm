#include "SampleGeneticAlgorithm.h"

static Solution *GenRandomSolution(GeneticAlgorithm &algorithm_manager);

Solution *GenRandomSolution(GeneticAlgorithm &algorithm_manager)
{
    auto *new_solution = new NumberSolution();

    new_solution->genome().Randomize(algorithm_manager);
    new_solution->CalcFitness(algorithm_manager);
    return new_solution;
}

NumberGene::NumberGene() {
    set_random();
}

NumberGene::NumberGene(const NumberGene& number) : bit_(number.bit_) {}

Gene* NumberGene::clone() const
{
    return new NumberGene(*this);
}

Gene& NumberGene::Mutate()
{
    bit_ = !bit_;
    return *this;
}

Gene& NumberGene::set_random()
{
    bit_ = (rand() % 100) < 50 ? 0 : 1;
    return *this;
}

NumberGenome::NumberGenome(uint32_t size) : Genome(size) {}

NumberGenome::NumberGenome(const NumberGenome& genome) : Genome(genome) {}

Genome *NumberGenome::clone() const
{
    return new NumberGenome(*this);
}

NumberSolution::NumberSolution() {
    genome_ = new NumberGenome(kGenomeSize);
}

NumberSolution::NumberSolution(const NumberSolution& solution) : IHasInvidualMutation(solution) {}

Solution *NumberSolution::clone() const
{
    return new NumberSolution(*this);
}

SampleGeneticAlgorithm::SampleGeneticAlgorithm()
{
    set_solution_factory_(GenRandomSolution);
}

SampleGeneticAlgorithm::~SampleGeneticAlgorithm()
{
}

float NumberSolution::CalcFitness(GeneticAlgorithm &manager)
{
    fitness_ = 0.0f;

    for (int i = 0, size = genome_->size(); i < size; ++i)
    {
        fitness_ += ((NumberGene*)&genome_->gene(i))->bit();
    }

    return fitness_;
}
