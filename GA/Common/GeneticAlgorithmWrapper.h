#pragma once

#include "GeneticAlgorithm.h"

class GeneticAlgorithmWrapper : public GeneticAlgorithm
{
    std::string time_output_file_;
public:
    using GeneticAlgorithm::GeneticAlgorithm;
    GeneticAlgorithmWrapper() : GeneticAlgorithm() {}
    GeneticAlgorithmWrapper(GeneticAlgorithm::SolutionComparator compare) : GeneticAlgorithm(compare) {}

    void Loop();
    inline std::string& set_time_output_file(const std::string &file) { return time_output_file_ = file; }
    inline std::string& time_output_file() { return time_output_file_; }
};

