#pragma once

#include "GeneticAlgorithm.h"

class GeneticAlgorithmWrapper : public GeneticAlgorithm
{
    std::string generation_statistic_output_file_;
public:
    using GeneticAlgorithm::GeneticAlgorithm;
    GeneticAlgorithmWrapper() : GeneticAlgorithm() {}
    GeneticAlgorithmWrapper(GeneticAlgorithm::SolutionComparator compare) : GeneticAlgorithm(compare) {}

    virtual void prepare();
    void Selection();
    void GenPopulation();
    inline std::string& set_generation_statistic_output_file(const std::string &file) { return generation_statistic_output_file_ = file; }
    inline std::string& generation_statistic_output_file() { return generation_statistic_output_file_; }
};

