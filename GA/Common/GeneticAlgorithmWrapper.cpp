#include "GeneticAlgorithmWrapper.h"

#include <chrono>

#include "Logger.h"

GeneticAlgorithm::SolutionVector& GeneticAlgorithmWrapper::Run()
{
    if (!statistic_output_file().empty())
    {
        Logger logger;

        GeneticAlgorithm::Run();

        logger.open(statistic_output_file(), std::fstream::app);
        logger.LogPopulationFitness(population_array_);        
        logger.close();
        return population_array_;
    }
    else
    {
        return GeneticAlgorithm::Run();
    }
}

void GeneticAlgorithmWrapper::GenPopulation()
{
    if (!generation_statistic_output_file().empty())
    {
        Logger logger;

        GeneticAlgorithm::GenPopulation();

        logger.open(generation_statistic_output_file(), std::fstream::out);
        logger.LogPopulationFitness(population_array_);
        logger.close();
    }
    else
    {
        GeneticAlgorithm::GenPopulation();
    }
}

void GeneticAlgorithmWrapper::Selection()
{
    if (!generation_statistic_output_file().empty())
    {
        Logger logger;

        GeneticAlgorithm::Selection();

        logger.open(generation_statistic_output_file(), std::fstream::app);
        logger.LogPopulationFitness(population_array_);
        logger.close();
    }
    else
    {
        GeneticAlgorithm::GenPopulation();
    }
}

void GeneticAlgorithmWrapper::prepare()
{
}