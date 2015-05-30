#include "GeneticAlgorithmWrapper.h"

#include <chrono>

#include "Logger.h"

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