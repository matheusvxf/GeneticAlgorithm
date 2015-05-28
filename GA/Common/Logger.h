#pragma once

#include <fstream>

#include "GeneticAlgorithm.h"
#include "StatisticSolution.h"

class Logger
{
    std::fstream fs_;
public:
    Logger(const std::string &file) { open(file); }
    Logger();
    ~Logger();

    inline void create(const std::string& file) { open(file, std::fstream::out); close(); }
    inline void open(const std::string& file) { open(file, std::fstream::out); }
    inline void open(const std::string& file, int mode) { fs_.open(file, mode); }
    inline void close() { fs_.close(); }
    inline std::fstream& fstream() { return fs_; }
    inline void LogPopulationFitness(const GeneticAlgorithm::SolutionVector& population);
};

inline void Logger::LogPopulationFitness(const GeneticAlgorithm::SolutionVector& population)
{
    float avr, sdv, best, worse;
    std::fstream &fs = fstream();
    avr = AverageFitness(population);
    best = BestFitness(population);
    worse = WorseFitness(population);
    sdv = StandardDeviation(population);
    fs << best << " " << worse << " " << avr << " " << sdv << std::endl;
}
