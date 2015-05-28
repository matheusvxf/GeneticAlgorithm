#include "GeneticAlgorithmWrapper.h"

#include <chrono>

#include "Logger.h"

void GeneticAlgorithmWrapper::Loop()
{
    if (!time_output_file().empty())
    {
        Logger logger;
        auto start = std::chrono::system_clock::now();

        GeneticAlgorithm::Loop();

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start);
        logger.open(time_output_file(), std::fstream::app);
        logger.fstream() << duration.count() << std::endl;
        logger.close();
    }
    else
    {
        GeneticAlgorithm::Loop();
    }
}

Solution& GeneticAlgorithmWrapper::Run()
{
    if (!statistic_output_file().empty())
    {
        Logger logger;

        GeneticAlgorithm::Run();

        logger.open(statistic_output_file(), std::fstream::app);
        logger.LogPopulationFitness(population_array_);        
        logger.close();
        return **population_.begin();
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