#pragma once

#include "GeneticAlgorithm.h"

class GeneticAlgorithmWrapper : public GeneticAlgorithm
{
    std::string time_output_file_;
    std::string statistic_output_file_;
    std::string generation_statistic_output_file_;
public:
    using GeneticAlgorithm::GeneticAlgorithm;
    GeneticAlgorithmWrapper() : GeneticAlgorithm(),
        statistic_output_file_(kStatisticFile) {}
    GeneticAlgorithmWrapper(GeneticAlgorithm::SolutionComparator compare) : GeneticAlgorithm(compare) {}

    virtual void prepare();
    void Selection();
    void GenPopulation();
    GeneticAlgorithm::SolutionVector& Run();
    inline std::string& set_time_output_file(const std::string &file) { return time_output_file_ = file; }
    inline std::string& time_output_file() { return time_output_file_; }
    inline std::string& set_statistic_output_file(const std::string &file) { return statistic_output_file_ = file; }
    inline std::string& statistic_output_file() { return statistic_output_file_; }
    inline std::string& set_generation_statistic_output_file(const std::string &file) { return generation_statistic_output_file_ = file; }
    inline std::string& generation_statistic_output_file() { return generation_statistic_output_file_; }
};

