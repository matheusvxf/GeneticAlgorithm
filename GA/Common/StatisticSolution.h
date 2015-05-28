#pragma once

#include "GeneticAlgorithm.h"

extern inline float AverageFitness(const GeneticAlgorithm::SolutionVector& population);
extern inline float VarianceFitness(const GeneticAlgorithm::SolutionVector& population);
extern inline float StandardDeviation(const GeneticAlgorithm::SolutionVector& population);
extern inline float BestFitness(const GeneticAlgorithm::SolutionVector& population);
extern inline float WorseFitness(const GeneticAlgorithm::SolutionVector& population);
extern inline void LoggerPopulationFitness(const GeneticAlgorithm::SolutionVector& population);

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

inline float WorseFitness(const GeneticAlgorithm::SolutionVector& population)
{
    return (*(population.end() - 1))->fitness();
}