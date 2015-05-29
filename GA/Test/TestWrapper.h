#pragma once

#include <string>
#include <sstream>

#include "GeneticAlgorithm.h"

class SolverInterface
{
protected:
    std::string time_file_;
public:
    virtual void SolveExactSolution() = 0;
    virtual GeneticAlgorithm::SolutionVector& SolveGeneticAlgorithm() = 0;
    virtual GeneticAlgorithm& ga_manager() = 0;
    virtual std::string statistic_file() const = 0;
    virtual std::string default_time_file() const = 0;
    virtual std::string test_file() const = 0;
    virtual std::string name() const = 0;
    virtual std::string& set_generation_statistic_file(const std::string &file) = 0;
    virtual bool ReadNextTestCase(std::fstream &fs) = 0;
    virtual std::string problem_size() const = 0;

    virtual std::string time_file() const { return time_file_; };
    virtual std::string& set_time_file(std::string &file) { return time_file_ = file; }
};

class TestWrapper
{
protected:
    SolverInterface *solver_;

    void SolveDynamicProgramming();
    float SolveGeneticAlgorithm();
public:
    TestWrapper(SolverInterface *solver) : solver_(solver) {}
    virtual ~TestWrapper() { delete solver_; }

    void Solve();
};

